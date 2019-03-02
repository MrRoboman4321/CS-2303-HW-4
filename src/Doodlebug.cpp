/*
 * Doodlebug.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: student
 */

#include <cstdlib>
#include "Doodlebug.h"
/**
 * Default constuctor
 */
Doodlebug::Doodlebug()
:Organism(false){
	stepsTillStarve = 3;
	stepsTillBreed = 8;
}
/**
 * Constructor that takes in the grid pointer and the postion on the grid
 * @param r the row number
 * @param c the column number
 * @param grid pointer to the grid that the org is on
 */
Doodlebug::Doodlebug(int r, int c, Grid* grid)
: Organism(false) {
	row = r;
	col = c;
	myGrid = grid;
	stepsTillStarve = 3;
	stepsTillBreed = 8;
}
/**
 * Operates the Doodlebug simulation for one tick
 */
void Doodlebug::tick() {//TODO do we want to put this here?
	move();



	breed();
	starve();

}


/**
 * removes the doodlebug from the grid if it is starving
 */
void Doodlebug::starve() {
	if(isStarving()){//if you are starving, tell the grid to remove you from the grid
		myGrid->removeOrg(row, col);
	}
}


/**
 * moves the doodlebug, will first try to find an ant and eat it, and then move into it's spot
 * if there is no ant, it falls back on organism's where to move method
 * @return returns true if it was able to move, false otherwise
 */
bool Doodlebug::move()
{
	Organism::Pos nextPos;
	bool status = true;
	clearNeighbors();
	Organism* prey[4];//set up for move
	int preyCount = 0;
	bool hasEaten = false;
	if(findNeighbors() > 0){
		for (int i = 0, j = 0; i < 4; ++i) {
			if(neighbors[i] != 0 && neighbors[i]->isPrey()){// if you find prey in the neighbors, keep track of them
				prey[j] = neighbors[i];
				j++;
				preyCount++;
			}
		}
	}
	if(preyCount > 0){
		//if there are prey, chose one and eat it
		int preyChoice = rand() % preyCount;//takes care of the condition if there is one prey, x%1 == 0
		nextPos.c = prey[preyChoice]->getCol();
		nextPos.r = prey[preyChoice]->getRow();
		 hasEaten= eat(prey[preyChoice], myGrid);
		//updates steosSinceLastFood



	}else{//falls back on organism whereToMOve
		nextPos = Organism::whereToMove();
	}
	//moves the doodlebug if it is different positions
	if(nextPos.r != row || nextPos.c != col){
		status = myGrid->moveOrganism(nextPos.r, nextPos.c, this);
	}
	//updates position
	if(status){
		row = nextPos.r;
		col = nextPos.c;
	}
	stepsSinceLastBreed++;

	if(hasEaten){
		stepsSinceLastFood = 0;
	}else{
		stepsSinceLastFood++;
	}

	return status;
}


/**
 * if the doodlebug has taken enough steps, it will spawn another doodlebug
 * @return true if doodlebug was spawned, false otherwise
 */
bool Doodlebug::breed()
{
	bool status = false;
	if(stepsSinceLastBreed >= stepsTillBreed && !isStarving()){
		clearNeighbors();
		int optionCount = findNeighbors();
		direction birthOptions[optionCount];
		for (int i = 0, written = 0; i < 4; ++i) {//writes to which grid spaces are move options
			if(neighbors[i] == 0){
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
			Pos newDoodlebugPos;
			if(optionCount > 1){//if more than one option will randomly select an option
				newDoodlebugPos = gridPosGivenMoveOption(birthOptions[rand()%optionCount]);
			}else{//there is only one move option so the new ant will be put there
				newDoodlebugPos = gridPosGivenMoveOption(birthOptions[0]);

			}
			//birth the ant
			Doodlebug* babyDoodlebug = new Doodlebug(newDoodlebugPos.r, newDoodlebugPos.c, myGrid);
			status = myGrid->addOrg(newDoodlebugPos.r, newDoodlebugPos.c, babyDoodlebug);


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
 * Doodlebug will remove an organism from the grid, does not check if the org is an ant
 * @param org the organism that is going to be removed
 * @param grid the grid that the organism is on
 * @return true if the organism was removed
 */
bool Doodlebug::eat(Organism* org, Grid* grid)
{
	bool status = true;
	status = grid->removeOrg(org->getRow(), org->getCol());
	return status;
}


/**
 * figure out whether the doodlebug is starving
 * @return true of the doodlebug is starving, false otherwise
 */
bool Doodlebug::isStarving() {
	if(stepsSinceLastFood > stepsTillStarve){
		return true;
	}else{
		return false;
	}
}


/**
 * finds the neighbors and puts pointers to the organisms in the neighbors array
 * @return the number of non null neighbors
 */
int Doodlebug::findNeighbors() {
	//first element is pointer to what is above, goes around clockwise from there
	int neighborCount = 0;
	if(myGrid->getCellOccupant(this->row - 1, this->col) != nullptr && this->row - 1 > 0 &&
	this->row -1 < myGrid.getSideLenght()){
		neighborCount++;
		neighbors[0] = myGrid->getCellOccupant(this->row - 1, this->col);
	}else{
		neighbors[0] = (Organism*)0x100;
	}
	if(myGrid->getCellOccupant(this->row, this->col + 1) != nullptr && this->col + 1 > 0 &&
	   this->col + 1 < myGrid.getSideLenght()) {
		neighborCount++;
		neighbors[1] = myGrid->getCellOccupant(this->row, this->col + 1);
	} else{
		neighbors[1] = (Organism*)0x10000000;
	}
	if(myGrid->getCellOccupant(this->row + 1, this->col) != nullptr && this->row + 1 > 0 &&
	   this->row +1 < myGrid.getSideLenght()){
		neighborCount++;
		neighbors[2] = myGrid->getCellOccupant(this->row + 1, this->col);
	}else{
		neighbors[2] = (Organism*)0x100;
	}
	if(myGrid->getCellOccupant(this->row, this->col - 1) != nullptr && this->col - 1 > 0 &&
	   this->col -1 < myGrid.getSideLenght()){
		neighborCount++;
		neighbors[3] = myGrid->getCellOccupant(this->row, this->col - 1);
	}else{
		neighbors[0] = (Organism*)0x100;
	}
	return neighborCount;
}

/**
 * determain if the doodlebug is prey
 * @return false
 */
bool Doodlebug::isPrey() {
	return false;
}


/**
 * destructor for doodlebug
 */
Doodlebug::~Doodlebug() {
	//myGrid = 0;//mygrid points to the master grid, do not want to free!!!!!


}

