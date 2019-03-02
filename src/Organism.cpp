/*
 * Organism.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */

#include <cstdlib>
#include "Organism.h"
bool amAnt = false;

/**
 * Default consturctot
 */
Organism::Organism() {

}

/**
 *	Consturctor for an organism
 * @param b if the organism is an ant
 */
Organism::Organism(bool b) {
	amAnt = b;

}

/**
 * ir the Organism is prey
 * @return
 */
bool Organism::isPrey()
{
	return amAnt;
}

/**
 * detertmains the next place to move if following the default move instuctions
 * those instuction being, find an empty spot and move to it, if there is more than one
 * chose randomly
 * @return the position to move to
 */
Organism::Pos Organism::whereToMove() {
	bool status = true;
	clearNeighbors();
	Pos nextPostion;
	nextPostion.c = col;
	nextPostion.r = row;
	int optionCount = findNeighbors();
	direction options[optionCount];
	for (int i = 0, written = 0; i < 4; ++i) {//writes to which grid spaces are move options
		if(neighbors[i].isValid && neighbors[i].org == 0 ){
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
	if(optionCount == 0){
		if(optionCount > 1){//if more than one option will randomly select an option
			nextPostion = gridPosGivenMoveOption(options[rand()%optionCount]);
		}else{//there is only one move option so it will move there
			nextPostion = gridPosGivenMoveOption(options[0]);

		}


	}else{
		status = false;//no move options, return false
	}
	if(!status){//if you can't move anywhere, move to where you are
		nextPostion.r = row;
		nextPostion.c = col;
	}

	return nextPostion;

}


/**
 * produces a grid position from a move option
 * @param o the direction that the organism wants to move
 * @return the Pos stuct which contains the grid postion
 */
Organism::Pos Organism::gridPosGivenMoveOption(Organism::direction o) {
	Pos postion;

	if(o == Up) {//the space above you
		postion.r = row - 1;
		postion.c = col;
	} else if(o == Right) {// the space to your right
		postion.r = row;
		postion.c = col + 1;
	} else if(o == Down) {// the space below you
		postion.r = row + 1;
		postion.c = col;
	} else {// the space to your left
		postion.r = row;
		postion.c = col - 1;
	}
	return postion;
}


/**
 * clears the array of neighbors
 */
void Organism::clearNeighbors() {
	for (int i = 0; i < 4; ++i) {//cleans the moveOptions array
		neighbors[i].org = nullptr;
		neighbors[i].isValid = false;
	}
}

/**
 * Destructor for an organism
 */
Organism::~Organism() {

}

/**
 * getter for row
 * @return the row that the organism is in
 */
int Organism::getRow() const {
	return row;
}

/**
 * getter for col
 * @return returns the column that the organism is in
 */
int Organism::getCol() const {
	return col;
}

