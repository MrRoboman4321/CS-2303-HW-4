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
Ant::Ant(int r, int c)
:Organism(true)
{
	row = r;
	col = c;
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
				options[written] = up;
				written++;
			} else if(i == 1){
				options[written] = right;
				written++;
			} else if(i == 2){
				options[written] = down;
				written++;
			} else if(i == 3){
				options[written] = left;
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
		status = myGrid->moveOrganism(this, nextPostion.r, nextPostion.c);
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
					birthOptions[written] = up;
					written++;
				} else if(i == 1){
					birthOptions[written] = right;
					written++;
				} else if(i == 2){
					birthOptions[written] = down;
					written++;
				} else if(i == 3){
					birthOptions[written] = left;
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

	if(o == up){
		postion.r = row - 1;
		postion.c = col;
	}else if(o == right){
		postion.r = row;
		postion.c = col + 1;
	}else if(o == down){
		postion.r = row + 1;
		postion.c = col;
	}else if(o == left){
		postion.r = row;
		postion.c = col - 1;
	}
	return postion;
}


Ant::~Ant() {
	// TODO Auto-generated destructor stub

}

