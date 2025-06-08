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

	void AbstractHex::reset(){//fill_board already fills the board with dots so reset only calls fill_board
		fill_board();
	}

	void AbstractHex::setSize(int row, int col){

		if(row != col){
	
			cout << "Board should be a square. Row and column must be the same." << endl;
		
			return;
	
		}else if(row < 6){
	
			cout << "Board must be larger than 5x5." << endl;
		
			return;
	
		}
	
		size=row;
	
		reset();

	}
	
	Cell AbstractHex::lastMove(){
	
		Cell last; //last move represented by a Cell
		
		try{
		
			if(last_letter == 0 || last_num<size || last_num>size || (last_letter-65)<size || (last_letter-65)>size){ // last_letter is empty or they have garbage values
			
				Error error; // Error is the custom exception class of SENA_HEX
				throw(error); // throws an exception
			
			}
			
			last.setCol(this->last_letter); // last Cell has the values of the class' last moves
			last.setRow(this->last_num);
			
		}catch(exception &except){ // Error class is derived from exception class and it overrides the function what()
		
			cerr << except.what() << endl; // Prints the error message
			cerr << "There is no last move." << endl;
		
		}
	
	}

	bool AbstractHex::isEnd(){

		if(x_win() == 1 || o_win() == 1)	return true; //If x or o won, returns true

	}

	inline int AbstractHex::width(){ //width is the same as size
		return size;
	}

	inline int AbstractHex::height(){ //height is the same as size
		return size;
	}

	int AbstractHex::marked(){	return mark;}

}
