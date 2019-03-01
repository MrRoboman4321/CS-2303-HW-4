/*
 * Doodlebug.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: student
 */

#include <cstdlib>
#include "Doodlebug.h"

Doodlebug::Doodlebug() {
	// TODO Auto-generated constructor stub

}
bool Doodlebug::move()
{
	Organism::Pos nextPos;
	bool status = true;
	clearNeighbors();
	Organism* prey[4];
	int preyCount = 0;
	if(findNeighbors() > 0){
		for (int i = 0, j = 0; i < 4; ++i) {
			if(neighbors[i] != 0 && neighbors[i]->isPrey()){
				prey[j] = neighbors[i];
				j++;
				preyCount++;
			}
		}
	}
	if(preyCount > 0){

		int preyChoice = rand() % preyCount;//takes care of the condition if there is one prey, x%1 == 0
		nextPos.c = prey[preyChoice]->getCol();
		nextPos.r = prey[preyChoice]->getRow();
		bool hasEaten = eat(prey[1], myGrid);
		if(hasEaten){
			stepsSinceLastFood = 0;
		}else{
			stepsSinceLastFood++;
		}


	}else{
		nextPos = Organism::whereToMove();
	}

	if(nextPos.r != row || nextPos.c != col){
		status = myGrid->setCellOccupant(nextPos.r, nextPos.c, this) &&
		         myGrid->setCellOccupant(row, col, 0);
	}

	if(status){
		row = nextPos.r;
		col = nextPos.c;
	}
	stepsSinceLastBreed++;



	return status;
}

bool Doodlebug::breed()
{
	bool status = true;
	if(stepsSinceLastBreed >= 3){
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
			Doodlebug* babyDoodlebug = new Doodlebug(newDoodlebugPos.r, newDoodlebugPos.c, myGrid);
			status = myGrid->addOrg(newDoodlebugPos.r, newDoodlebugPos.c, babyDoodlebug, babyDoodlebug->isPrey());

			if(status){
				row = newDoodlebugPos.r;
				col = newDoodlebugPos.c;
			}
		}else{
			status = false;//no move options, return false
		}
	}
	if(status){
		stepsSinceLastBreed = 0;
	}
	return status;
}
bool Doodlebug::eat(Organism* org, Grid* grid)
{
	bool status = true;
	status = grid->removeOrg(org->getRow(), org->getCol(), org);
	return status;
}

bool Doodlebug::isStarving() {
	if(stepsSinceLastFood > 3){
		return true;
	}else{
		return false;
	}
}

bool Doodlebug::isPrey() {
	return false;
}

Doodlebug::~Doodlebug() {
	// TODO Auto-generated destructor stub
}

