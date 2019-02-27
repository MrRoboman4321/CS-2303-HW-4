/*
 * Doodlebug.h
 *
 *  Created on: Feb 10, 2019
 *      Author: student
 */

#ifndef DOODLEBUG_H_
#define DOODLEBUG_H_

#include "Grid.h"

#include "Organism.h"

class Doodlebug: public Organism {
private:
	Grid* mygrid;
    int stepsSinceLastFood = 0;

public:
	Doodlebug();
	Doodlebug(int r, int c, Grid* grid);
	bool move();
	bool breed();
	bool eat();
	bool isStarving();
	bool isPrey();

	virtual ~Doodlebug();
};

#endif /* DOODLEBUG_H_ */
