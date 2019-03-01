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

class Grid;

class Doodlebug: public Organism {
private:
	Grid* myGrid;
    int stepsSinceLastFood = 0;
    int stepsTillStarve = 3;

public:
	Doodlebug();
	Doodlebug(int r, int c, Grid* grid);


	bool move();
	bool breed();
	bool eat(Organism* org, Grid* grid);
	bool isStarving();
	bool isPrey();
	int findNeighbors();
	void tick();
	void starve();

	virtual ~Doodlebug();
};

#endif /* DOODLEBUG_H_ */
