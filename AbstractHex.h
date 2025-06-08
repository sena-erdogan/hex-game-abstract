/*
 * 	This is the header file for the library of hex game
 * 	Contains the declarations of the functions used in the program
 *
 */
 
 #include<vector>
 #include<fstream>
 #include<exception>
 
 using namespace std;

#ifndef ABSTRACTHEX_H
#define ABSTRACTHEX_H

namespace SENA_HEX{

	enum Content{x = 'x', cx = 'X', co = 'O', o = 'o', dot = '.', star = '*'}; //cx is capital x, co is capital o
	static int mark;
	
	class Error : public exception{ // Error is derived from the exception class
	public:
		const char * what() const throw(){	return "Exception called.";}	//what() function of exception is overridden
	};
	
	class Cell{
	public:
		void setCol(char letter){	col = letter;}
		char getCol(){			return col;}
		void setRow(int num){		row = num;}
		int getRow(){			return row;}
		void setCont(Content tempCont){	cont = tempCont;}
		Content getCont(){		return cont;}
	private:
		char col; // column
		int row;
		Content cont;
	};

	class AbstractHex{
	public:		
		virtual void playGame() = 0;
		virtual void writeToFile(int player, int computer, std::string input, char last_letter, int last_num) = 0;
		virtual void readFromFile(std::string input) = 0;
		int width();
		int height();
		virtual void print() = 0;
		virtual void fill_board() = 0;
		virtual int x_win() = 0;
		virtual int o_win() = 0;
		virtual void add_move(char letter, int num, int player) = 0;
		virtual void play() = 0;
		virtual void play(char letter, int num) = 0;
		static int marked();
		virtual bool compare() = 0;
		virtual void user_vs_user() = 0;
		virtual void user_vs_computer(char last_letter,char last_num) = 0;
		void reset();
		void setSize(int row, int col);
		int getSize(){return size;}
		bool isEnd();
		virtual int numberOfMoves() = 0;
		void setPlayer(int play){	player = play;}
		void setLastNum(int num){	last_num = num;}
		void setLastLetter(char letter){last_letter = letter;}
		virtual Cell operator()(int num, char letter) = 0;
		Cell lastMove();
	protected:
		int size, player, last_num;
		char last_letter;

	};

}

#endif
