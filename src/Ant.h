/*
 * Ant.h
 *
 *  Created on: Feb 10, 2019
 *      Author: student
 */

#ifndef ANT_H_
#define ANT_H_

#include "Grid.h"

#include "Organism.h"

class Ant: public Organism {
private:
	Grid* myGrid;
	struct Pos{
		int r;
		int c;
	};
	Pos gridPosGivenMoveOption(direction o);
public:
	Ant();
	Ant(int r, int c, Grid* grid);

	bool move();
	bool breed();

	 ~Ant();
};

#endif /* ANT_H_ */
