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

	struct Pos{
		int r;
		int c;
	};
	Pos gridPosGivenMoveOption(moveOption o);
public:
	Ant();
	Ant(int r, int c);

	bool move(Grid* myGrid);
	bool breed(Grid* myGrid);

	 ~Ant();
};

#endif /* ANT_H_ */
