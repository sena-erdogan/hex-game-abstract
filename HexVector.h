/*
 * 	This is the header file for the library of hex game
 * 	Contains the declarations of the functions used in the program
 *
 */
 
 #include<vector>
 #include<fstream>
 #include "AbstractHex.h"

#ifndef HEXVECTOR_H
#define HEXVECTOR_H

namespace SENA_HEX{
	class HexVector : public AbstractHex{
	public:
		HexVector(int row, int col);
		HexVector(int row);
		HexVector();
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
		bool operator==(HexVector & o);
		Cell operator()(int num, char letter);
	private:
		std::vector<std::vector<Cell> > hexCells;
		std::vector<std::vector<Cell> > check;
		std::vector<std::vector<Cell> > game;

	};
}

#endif
