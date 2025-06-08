#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "AbstractHex.h"
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"

/*
 Contains the definitions of the functions
 */

using namespace std;
using namespace SENA_HEX;

namespace SENA_HEX{

	HexVector::HexVector(int row, int col){
		size=col;
		hexCells.resize(size*size);
	}

	HexVector::HexVector(int row){
		size=row;
		hexCells.resize(size*size);
	}

	HexVector::HexVector(){
		size=6;
		hexCells.resize(size*size);
	}
	
	Cell HexVector::operator()(int num, char letter){
	
		try{
			if(num<size || num>size || (letter-65)<size || (letter-65)>size){ // Given values are either greater or less than the provided size so there is not a Cell of the given indexes
			
				Error error; // Error is the custom exception class of SENA_HEX
				throw(error); // throws an exception
			}
	
			return hexCells[num][letter-65]; // returns the Cell at the given indexes
		
		}catch(exception &except){ // Error class is derived from exception class and it overrides the function what()
		
			cerr << except.what() << endl; // Prints the error message
			cerr << "There is no Cell for the indexes provided." << endl;
		}
	}
	
	bool HexVector::operator==(HexVector & o){ // returns true if the sizes of the two boards are the same and they have exactly the same contents at the same indexes
	
		if(size != o.size)	return false;
		
		for(int i=0; i<size; i++){
		
			for(int j=0; j<size; j++)	if(hexCells[i][j].getCont() != o.hexCells[i][j].getCont())	return false; 
		
		}	
		
		return true;
	
	}
	
	
	
	int HexVector::numberOfMoves(){
	
		int num=0;
		
		for(int i=0; i<=size; i++){

			for(int j=0; j<=size; j++){

					if(hexCells[i][j].getCont() != dot)		++num; // Every cell has dot at the beginning as default. If there's a move made, cell content will change

			}

		}
		
		return num;
	
	}

	void HexVector::writeToFile(int player, int computer, string input, char last_letter, int last_num){ //player is 1 for user1, 2 for user2
															//computer is 1 for computer vs user, 0 for user vs user
		string filepath;
		int i=5;
		while(input[i] != '\0'){

			filepath[i-5] = input[i];
			i++;

		}

		ofstream fp;
		fp.open(filepath.c_str());

		if(!fp)		cerr << endl << "File could not be opened" << endl << endl;
		else{

			fp << size << " " <<  player << " " << computer << " ";
	
			for(int i=0; i<=size; i++){

				for(int j=0; j<=size; j++){

					if(hexCells[i][j].getCont() == x)		fp << 'x';
					else if(hexCells[i][j].getCont() == o)		fp << 'o';
					else if(hexCells[i][j].getCont() == dot)	fp << '.';

				}

			}

			fp.close();

		}
	
		if(computer == 0)	user_vs_user();
		else if(computer == 1)	user_vs_computer(last_letter,last_num);

	}

	void HexVector::readFromFile(string input){

		string filepath;
		char cell, last_letter;
		int i=5, size, player, computer, last_num;
		while(input[i] != '\0'){

			filepath[i-5] = input[i];
			i++;

		}

		ifstream fp;
		fp.open(filepath.c_str());

		if(!fp)		cerr << endl << "File does not exist" << endl << endl;
		else{

			fp >> size >> player >> computer;
	
			for(int i=0; i<=size; i++){

				for(int j=0; j<=size; j++){

					fp >> cell;

					if(cell == 'x')		hexCells[i][j].setCont(x);
					else if(cell == 'o')	hexCells[i][j].setCont(o);
					else if(cell == '.')	hexCells[i][j].setCont(dot);
				}

			}

			fp.close();

			if(computer == 1)	user_vs_computer(last_letter, last_num);
			else if(computer == 0)	user_vs_user();

		}

	}

	int HexVector::x_win(){ //Finds an x where letter is 'a', checks every possible way it can go to

		int num = 0, letter = 0;

		while(letter != size){

			if(num != size && hexCells[num][letter].getCont() != 'x')	++num;
			else if(hexCells[++num][--letter].getCont() == 'x'){

				check[num][letter].setCont(x);		// If it finds an x on the way, it adds the location to the check array as 'x'
				++num;
				--letter;

			}else if(hexCells[++num][letter].getCont() == 'x'){

				check[num][letter].setCont(x);
				++num;

			}else if(hexCells[num][++letter].getCont() == 'x'){

				check[num][letter].setCont(x);
				++letter;

			}else if(hexCells[num][--letter].getCont() == 'x'){

				check[num][letter].setCont(x);
				--letter;

			}else if(hexCells[--num][letter].getCont() == 'x'){

				check[num][letter].setCont(x);
				--num;

			}else if(hexCells[--num][++letter].getCont() == 'x'){

				check[num][letter].setCont(x);
				--num;
				++letter;

			}else if(letter != size)	return 0;
			else{

				check[num][letter].setCont(star); 	//If the way doesn't go to the very right, it marks the way back as '*'

			}

		}

		for(int i=0; i<=size; i++){

			for(int j=0; j<=size; j++){

				if(hexCells[i][j].getCont() == check[i][j].getCont())	hexCells[i][j].setCont(cx); // The locations of the connected path is turned to 'X' on the original array

			}

		}

		return 1;

	}

	int HexVector::o_win(){

		int num = 1, letter = 1;

		while(num != size){

			if(letter != size && hexCells[num][letter].getCont() != 'o')	++letter;
			else if(hexCells[++num][--letter].getCont() == 'o'){

				check[num][letter].setCont(o);
				++num;
				--letter;

			}else if(hexCells[++num][letter].getCont() == 'o'){

				check[num][letter].setCont(o);
				++num;

			}else if(hexCells[num][++letter].getCont() == 'o'){

				check[num][letter].setCont(o);
				++letter;

			}else if(hexCells[num][--letter].getCont() == 'o'){

				check[num][letter].setCont(o);
				--letter;

			}else if(hexCells[--num][letter].getCont() == 'o'){

				check[num][letter].setCont(o);
				--num;

			}else if(hexCells[--num][++letter].getCont() == 'o'){

				check[num][letter].setCont(o);
				--num;
				++letter;

			}else if(num != size)	return 0;
			else{

				check[num][letter].setCont(star);

			}

		}

		for(int i=1; i<=size; i++){

			for(int j=1; j<=size; j++){

				if(hexCells[i][j].getCont() == check[i][j].getCont())	hexCells[i][j].setCont(co);

			}

		}

		return 1;

	}

	void HexVector::add_move(char letter, int num, int player = 1){ //Adds the given move to the board

		if(player == 1)		hexCells[num-1][letter - 65].setCont(x); 	// When the capital letters' ascii code is decremented by 64,
		else			hexCells[num-1][letter - 65].setCont(o);	// it gives us the row number of that letter
		mark++;

	}

	void HexVector::play(){

		HexVector::print();
	
		int num_c, count=0;
		char letter_c;

		count++;

		if(count == 0){ 		// Computer will go to one of the available positions on its six sides

			if(hexCells[num_c-1][(letter_c - 65) + 1].getCont() != '.')	count += 2;
			else										letter_c++;

		}

		if(count == 1){

			if(hexCells[num_c][letter_c - 65].getCont() != '.')	count += 2;
			else											num_c++;

		}

		if(count == 2){

			if(hexCells[num_c - 2][(letter_c - 65) + 1].getCont() != '.')	count += 2;
			else{

				letter_c++;
				num_c--;

			}

		}

		if(count == 3){

			if(hexCells[num_c - 2][letter_c - 65].getCont() != '.')	count += 2;
			else										num_c--;

		}

		if(count == 4){

			if(hexCells[num_c-1][(letter_c - 65) - 1].getCont() != '.')	count = (count + 3) % 6;
			else											letter_c--;

		}

		if(count == 5){

			if(hexCells[num_c][(letter_c - 65) - 1].getCont() != '.'){

				if(hexCells[num_c - 2][(letter_c - 65) + 1].getCont() == '.'){

					letter_c++;
					num_c--;

				}

				count = -1;

			}
			else{

				letter_c--;
				num_c++;

			}

		}

		cout << "Computer: " << letter_c << " " << num_c << endl;

		add_move(letter_c, num_c);

	}

	bool HexVector::compare(){

		int marked1=0, marked2=0;
	
		for(int i=0; i<size; i++){
	
			for(int j=0; j<size; j++){
		
				if(hexCells[i][j].getCont() == 'x')	++marked1;
				if(game[i][j].getCont() == 'x')	++marked2;
		
			}
	
		}
	
		if(marked1 > marked2)	return true;
		else			return false;

	}

	void HexVector::playGame(){

		size = 1;

		do{

			cout << "What do you want the board size to be? (ex: 10)" << endl;
			cin >> size;

			if(size < 6)	cerr << "Board size should be between greater than 5. " << endl;

		}while(size < 6);
	
		HexVector hexCells(size);	//Sets the size of board

		fill_board();		//Fills the board with dots

		do{

			cout << "Is this a two player game or a user vs. computer game?" << endl;
			cout << "Enter 1 for two players and 0 for user vs. computer" << endl;
			cin >> player;

			if(player != 1 && player != 0)	cerr << "You should enter 1 or 0" << endl;

		}while(player != 1 && player != 0);

		if(player == 0)			user_vs_computer('A', 1);
		else if(player == 1)		user_vs_user();

	}

	void HexVector::user_vs_user(){

		string input;
		char letter;
		int num;

		for(int i = 0; i < size; i++){

			for(int j = 0; j < size; j++){

				check[i][j].setCont(star);
				check[i][j].setRow(i);
				check[i][j].setCol(j+65);

		    }

		}

	
		if(player == 1){
	
			HexVector::print();

			do{
				input.clear();
			
				cout << "Player 1: ";
				getline(cin, input);

				if(input.length() == 3){
					letter = input[0];
					num = input[2] - 48;
				}else if(input.length() == 4){
					letter = input[0];
					num = (input[2] - 48)*10 + (input[3] - 48);
				}else if(input[1] == 'A')	HexVector::writeToFile(1, 0, input, 'A', 1);
				else if(input[1] == 'O')	HexVector::readFromFile(input);

				if(hexCells[num-1][letter - 65].getCont() != '.')	cerr << "Invalid move. Enter another move. " << endl;

			}while(hexCells[num-1][letter - 65].getCont() != '.');

			add_move(letter, num);

			if(x_win() == 1)		cout << endl << "Congratulations Player 1, you won!" << endl;
		
			HexVector::print();

			do{			
				input.clear();

				cout << "Player 2: ";
				getline(cin, input);

				if(input.length() == 3){
					letter = input[0];
					num = input[2] - 48;
				}else if(input.length() == 4){
					letter = input[0];
					num = (input[2] - 48)*10 + (input[3] - 48);
				}else if(input[1] == 'A')	writeToFile(2, 0, input, 'A', 1);
				else if(input[1] == 'O')	readFromFile(input);

				if(hexCells[num-1][letter - 65].getCont() != '.')	cerr << "Invalid move. Enter another move. " << endl;

			}while(hexCells[num-1][letter - 65].getCont() != '.');

			add_move(letter, num, 2);

			if(o_win() == 1)	cout << endl << "Congratulations Player 2, you won!" << endl;
	
		}else if(player == 2){
	
			print();

			do{			
				input.clear();

				cout << "Player 2: ";
				getline(cin, input);

				if(input.length() == 3){
					letter = input[0];
					num = input[2] - 48;
				}else if(input.length() == 4){
					letter = input[0];
					num = (input[2] - 48)*10 + (input[3] - 48);
				}else if(input[1] == 'A')	writeToFile(2, 0, input, 'A', 1);
				else if(input[1] == 'O')	readFromFile(input);

				if(hexCells[num-1][letter - 65].getCont() != '.')	cerr << "Invalid move. Enter another move. " << endl;

			}while(hexCells[num-1][letter - 65].getCont() != '.');

			add_move(letter, num, 2);

			if(o_win() == 1)	cout << endl << "Congratulations Player 2, you won!" << endl;
	
		}
	
		cin.ignore();

		while(x_win() == 0 && o_win() == 0){ //The game will go on until a player wins the game since
												//there can't be a tie in a hex game
			HexVector::print();

			do{
				input.clear();
			
				cout << "Player 1: ";
				getline(cin, input);

				if(input.length() == 3){
					letter = input[0];
					num = input[2] - 48;
				}else if(input.length() == 4){
					letter = input[0];
					num = (input[2] - 48)*10 + (input[3] - 48);
				}else if(input[1] == 'A')	writeToFile(1, 0, input, 'A', 1);
				else if(input[1] == 'O')	readFromFile(input);

				if(hexCells[num-1][letter - 65].getCont() != dot)	cerr << "Invalid move. Enter another move. " << endl;

			}while(hexCells[num-1][letter - 65].getCont() != '.');

			HexVector::add_move(letter, num);

			if(x_win() == 1)		cout << endl << "Congratulations Player 1, you won!" << endl;
			else{

				HexVector::print();

				do{
					input.clear();

					cout << "Player 2: ";
					getline(cin, input);

					if(input.length() == 3){
						letter = input[0];
						num = input[2] - 48;
					}else if(input.length() == 4){
						letter = input[0];
						num = (input[2] - 48)*10 + (input[3] - 48);
					}else if(input[1] == 'A')	writeToFile(2, 0, input, 'A', 1);
					else if(input[1] == 'O')	readFromFile(input);

					if(hexCells[num-1][letter - 65].getCont() != '.')	cerr << "Invalid move. Enter another move. " << endl;

				}while(hexCells[num-1][letter - 65].getCont() != '.');

				HexVector::add_move(letter, num, 2);

				if(o_win() == 1)	cout << endl << "Congratulations Player 2, you won!" << endl;

			}

		}

		HexVector::print(); //Prints the final board

	}

	void HexVector::user_vs_computer(char last_letter,char last_num){

		string input;
		char letter, letter_c = 'A'; 						// letter_c and num_c represents computer's position
		int num, num_c = size / 2, count = -1; 			//the computer will start from the very left of the board and
												//try to make its way to the very right. Count is used to determine the moves the computer will make
		for(int i = 0; i < size; i++){

			for(int j = 0; j < size; j++){

				check[i][j].setCont(star);
				check[i][j].setRow(i);
				check[i][j].setCol(j+65);

		    }

		}
	
		if(player == 0){
	
			HexVector::print();

			cout << "Computer: " << letter_c << " " << num_c << endl;

			add_move(letter_c, num_c);
	
		}else if(player == 1){
	
			letter_c = last_letter;
			num_c = last_num;
	
		}
	
		cin.ignore();

		while(x_win() == 0 && o_win() == 0){

			HexVector::print();

			do{
				input.clear();

				cout << "Your move: ";
				getline(cin, input);

				if(input.length() == 3){
					letter = input[0];
					num = input[2] - 48;
				}else if(input.length() == 4){
					letter = input[0];
					num = (input[2] - 48)*10 + (input[3] - 48);
				}else if(input[1] == 'A')	writeToFile(1, 1, input, letter_c, num_c);
				else if(input[1] == 'O')	readFromFile(input);

				if(hexCells[num-1][letter - 65].getCont() != '.')	cerr << "Invalid move. Enter another move." << endl;

			}while(hexCells[num-1][letter - 65].getCont() != '.'); // If that position is not marked by '.' or if it's greater then 'L',
																	// player should pick another move
			HexVector::add_move(letter, num, 2);

			if(o_win() == 1)	cout << endl << "Congratulations, you won!" << endl;
			else{

				play(last_letter, last_num);

				if(x_win() == 1)	cout << endl << "You lost..." << endl;

			}
		}
		print();
	}
	
	void HexVector::play(char letter, int num){

		add_move(letter, num, player);

	}

	void HexVector::fill_board(){

		for(int i = 0; i < size; i++){

			for(int j = 0; j < size; j++){

				hexCells[i][j].setCont(dot);
				hexCells[i][j].setRow(i);
				hexCells[i][j].setCol(j+65);

		    }

		}

	}

	void HexVector::print(){
	
		char letter = 'a';
		int num = 1;
		Cell temp;
	
		for(int i=0; i<size; i++){
	
			cout << letter;
			letter++;
	
		}

		for(int i = 0; i < size; i++){

			for(int k = 0; k < i; k++)	cout << " "; /* To make the board appear a diamond shape, there are blank spaces left before every row,
														equal to the row number*/
			for(int j = 0; j < size; j++){

				cout << hexCells[i][j].getCont() << " ";

		    }

			cout << endl;

		}

	}

}
