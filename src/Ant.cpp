/*
 * Ant.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: student
 */

#include <cstdlib>
#include "Ant.h"

Ant::Ant()
:Organism(true)
{

}
Ant::Ant(int r, int c, Grid* grid)
:Organism(true)
{
	row = r;
	col = c;
	myGrid = grid;
}

bool Ant::move()
{
	bool status = true;
	clearNeighbors();
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
		Pos nextPostion;
		if(optionCount > 1){//if more than one option will randomly select an option
			nextPostion = gridPosGivenMoveOption(options[rand()%optionCount]);
		}else{//there is only one move option so it will move there
			nextPostion = gridPosGivenMoveOption(options[0]);

		}
		status = myGrid->setCellOccupant(nextPostion.r, nextPostion.c, this) &&
				myGrid->setCellOccupant(this->row, this->col, 0);
		if(status){
			row = nextPostion.r;
			col = nextPostion.c;
		}
	}else{
		status = false;//no move options, return false
	}
	if(status){
		stepsSinceLastBreed++;
	}

	return status;
}

bool Ant::breed()
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
			Pos newAntPos;
			if(optionCount > 1){//if more than one option will randomly select an option
				newAntPos = gridPosGivenMoveOption(birthOptions[rand()%optionCount]);
			}else{//there is only one move option so the new ant will be put there
				newAntPos = gridPosGivenMoveOption(birthOptions[0]);

			}
			Ant* babyAnt = new Ant(newAntPos.r, newAntPos.c, myGrid);
			status = myGrid->setCellOccupant(newAntPos.r, newAntPos.c, babyAnt);
			//TODO: revisit once it is figured out how running sim
			if(status){
				row = newAntPos.r;
				col = newAntPos.c;
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

Ant::Pos Ant::gridPosGivenMoveOption(Organism::direction o) {
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

bool Ant::isPrey() {
	return true;
}

Ant::~Ant() {
	myGrid = 0;//mygrid points to the master grid, do not want to free!!!!!

}

