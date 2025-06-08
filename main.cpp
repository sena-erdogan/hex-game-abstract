/*
 * Contains just the main function of the program
 * Takes the board size from the user
 * Asks if they will play the game with a friend or by themselves and calls the functions accordingly
 *
 */

#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include "AbstractHex.h"
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"

using namespace std;
using namespace SENA_HEX;

int main(void){

	HexVector game1;
	game1.playGame();
	HexVector game2;
	game2.playGame();
	HexArray1D game3;
	game3.playGame();
	deque<deque<Cell> > game4;
	vector<vector<Cell> > game5;

}

/*bool isValid(AbstractHex **ptr){
	
	int size = (*ptr)->getSize();
	
	for(int i=0; i<size; i++){
		
		for(int j; j<size; j++){
			
			if(ptr[i][j].getCont() != dot || ptr[i][j].getCont() != star || ptr[i][j].getCont() != x || //ERROR
			ptr[i][j].getCont() != cx || ptr[i][j].getCont() != o || ptr[i][j].getCont() != co)	return false;
			
		}
		
	}
		
	return true;
	
}*/
