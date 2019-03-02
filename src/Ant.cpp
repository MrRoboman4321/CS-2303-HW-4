/*
 * Ant.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: student
 */

#include <cstdlib>
#include "Ant.h"

/**
 * Default constuctor for ant
 */
Ant::Ant()
:Organism(true)
{
	stepsTillBreed = 3;

}

/**
 * Constuctor that takes in the grid and the grid position of the ant
 * @param r the row that the ant is in
 * @param c the column that the ant is in
 * @param grid the grid where the ant exists
 */
Ant::Ant(int r, int c, Grid* grid)
:Organism(true)
{
	row = r;
	col = c;
	myGrid = grid;
	stepsTillBreed = 3;
}

/**
 * Operates the Ant simulation for one tick
 */
void Ant::tick() {//TODO do we want to put this here?
	move();

	breed();
}


/**
 * moves the ant in accordance with the organism whereToMove function
 * @return true if the ant moved, false otherwise
 */
bool Ant::move()
{
	bool status = false;

	Organism::Pos nextPostion = Organism::whereToMove();
	if(nextPostion.r != row || nextPostion.c != col){
		status = myGrid->moveOrganism(nextPostion.r, nextPostion.c, this);
	}

	if(status){
		row = nextPostion.r;
		col = nextPostion.c;
	}
	stepsSinceLastBreed++;


	return status;
}


/**
 * if the ant has taken enough steps and there is space around the ant, a new ant will spawn
 * @return true if a ant has been spawned
 */
bool Ant::breed()
{
	bool status = false;
	if(stepsSinceLastBreed >= stepsTillBreed){
		clearNeighbors();
		int optionCount = findNeighbors();
		direction birthOptions[optionCount];
		for (int i = 0, written = 0; i < 4; ++i) {//writes to which grid spaces are move options
			if(neighbors[i].isValid && neighbors[i].org == nullptr){
				if(i == 0){
					birthOptions[written] = Up;
					written++;
				} else if(i == 1){
					birthOptions[written] = Right;
					written++;
				} else if(i == 2){
					birthOptions[written] = Down;
					written++;
				} else if(i == 3){
					birthOptions[written] = Left;
					written++;
				}
			}
		}
		if(optionCount != 0){
			Pos newAntPos;
			if(optionCount > 1){//if more than one option will randomly select an option
				newAntPos = gridPosGivenMoveOption(birthOptions[rand()%optionCount]);
			}else{//there is only one move option so the new ant will be put there
				newAntPos = gridPosGivenMoveOption(birthOptions[0]);

			}
			//birth the ant
			Ant* babyAnt = new Ant(newAntPos.r, newAntPos.c, myGrid);
			status = myGrid->addOrg(newAntPos.r, newAntPos.c, babyAnt);

		}else{
			status = false;//no move options, return false
		}
	}
	if(status){
		stepsSinceLastBreed = 0;
	}
	return status;
}


/**
 * find out if the ant is prey, it is
 * @return true
 */
bool Ant::isPrey() {
	return true;
}


/**
 * finds the neighbors and puts pointers to the organisms in the neighbors array
 * @return the number of non null neighbors
 */
int Ant::findNeighbors() {
	//first element is pointer to what is above, goes around clockwise from there
	int neighborCount = 0;
	if(myGrid->getCellOccupant(this->row - 1, this->col) != nullptr && this->row - 1 > 0 &&
	   this->row -1 < myGrid->getSideLength()){
		neighborCount++;
		neighbors[0].isValid = true;
		neighbors[0].org = myGrid->getCellOccupant(this->row - 1, this->col);
	}else{
		neighbors[0].isValid = false;
	}
	if(myGrid->getCellOccupant(this->row, this->col + 1) != nullptr && this->col + 1 > 0 &&
	   this->col + 1 < myGrid->getSideLength()) {
		neighborCount++;
		neighbors[1].isValid = true;
		neighbors[1].org = myGrid->getCellOccupant(this->row, this->col + 1);
	} else{
		neighbors[1].isValid = false;;
	}
	if(myGrid->getCellOccupant(this->row + 1, this->col) != nullptr && this->row + 1 > 0 &&
	   this->row +1 < myGrid->getSideLength()){
		neighborCount++;
		neighbors[2].isValid = true;
		neighbors[2].org = myGrid->getCellOccupant(this->row + 1, this->col);
	}else{
		neighbors[2].isValid = false;
	}
	if(myGrid->getCellOccupant(this->row, this->col - 1) != nullptr && this->col - 1 > 0 &&
	   this->col -1 < myGrid->getSideLength()){
		neighborCount++;
		neighbors[3].isValid = true;
		neighbors[3].org = myGrid->getCellOccupant(this->row, this->col - 1);
	}else{
		neighbors[3].isValid = false;
	}
	return neighborCount;
}

/**
 * destructor for the ant
 */
Ant::~Ant() {
	//myGrid = nullptr;//mygrid points to the master grid, do not want to free!!!!!
    //TODO: Free all children spawned from breeding
}

