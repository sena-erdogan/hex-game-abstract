/*
 * 	This is the header file for the library of hex game
 * 	Contains the declarations of the functions used in the program
 *
 */
 
 #include<vector>
 #include<fstream>
 #include "AbstractHex.h"

#ifndef HEXARRAY1D_H
#define HEXARRAY1D_H

namespace SENA_HEX{

	class HexArray1D : public AbstractHex{
	public:
		HexArray1D(int row, int col);
		HexArray1D(int row);
		HexArray1D();
		HexArray1D(const HexArray1D & o);
		HexArray1D & operator=(const HexArray1D & o);
		~HexArray1D();
		void playGame();
		void writeToFile(int player, int computer, std::string input, char last_letter, int last_num);
		void readFromFile(std::string input);
		void print();
		void fill_board();
		int x_win();
		int o_win();
		void add_move(char letter, int num, int player);
		void play();
		void play(char letter, int num);
		bool compare();
		void user_vs_user();
		void user_vs_computer(char last_letter,char last_num);
		int numberOfMoves();
		Cell operator()(int num, char letter);
	private:
		Cell *hexCells;
		Cell *check;
		Cell *game;

	};

}

#endif
