/*
 * Grid.h
 *
 *  Created on: Feb 9, 2019
 *      Author: student
 */

#ifndef GRID_H_
#define GRID_H_

#include "Organism.h"

class Grid {
private:
	Organism **grid;

public:
	Grid();
	Grid(int nSquaresOnASide);

	bool setCellOccupant(int r, int c, Organism* g);
	Organism *getCellOccupant(int r, int c);

	bool moveOrganism(Organism *g, int r, int c);

	void printGird();

	virtual ~Grid();
};

#endif /* GRID_H_ */
