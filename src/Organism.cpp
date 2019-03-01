/*
 * Organism.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */

#include <cstdlib>
#include "Organism.h"
bool amAnt = false;

Organism::Organism() {
	// TODO Auto-generated constructor stub

}
Organism::Organism(bool b) {
	amAnt = b;

}
bool Organism::isPrey()
{
	return amAnt;
}
void Organism::setAmAnt(bool b)
{
	amAnt = b;
}

Organism::Pos Organism::whereToMove() {
	//TODO: clean up this code
	bool status = true;
	clearNeighbors();
	Pos nextPostion;

	int optionCount = findNeighbors();
	direction options[optionCount];
	for (int i = 0, written = 0; i < 4; ++i) {//writes to which grid spaces are move options
		if(neighbors[i] == 0){
			if(i == 0){
				options[written] = Up;
				written++;
			} else if(i == 1){
				options[written] = Right;
				written++;
			} else if(i == 2){
				options[written] = Down;
				written++;
			} else if(i == 3){
				options[written] = Left;
				written++;
			}
		}
	}
	if(optionCount != 0){
		if(optionCount > 1){//if more than one option will randomly select an option
			nextPostion = gridPosGivenMoveOption(options[rand()%optionCount]);
		}else{//there is only one move option so it will move there
			nextPostion = gridPosGivenMoveOption(options[0]);

		}


	}else{
		status = false;//no move options, return false
	}
	if(!status){
		nextPostion.r = row;
		nextPostion.c = col;
	}

	return nextPostion;

}

Organism::Pos Organism::gridPosGivenMoveOption(Organism::direction o) {
	Pos postion;

	if(o == Up){
		postion.r = row - 1;
		postion.c = col;
	}else if(o == Right){
		postion.r = row;
		postion.c = col + 1;
	}else if(o == Down){
		postion.r = row + 1;
		postion.c = col;
	}else if(o == Left){
		postion.r = row;
		postion.c = col - 1;
	}
	return postion;
}

void Organism::clearNeighbors() {
	for (int i = 0; i < 4; ++i) {//cleans the moveOptions array
		neighbors[i] = 0;
	}
}

Organism::~Organism() {
	// TODO Auto-generated destructor stub
}

int Organism::getRow() const {
	return row;
}

int Organism::getCol() const {
	return col;
}

