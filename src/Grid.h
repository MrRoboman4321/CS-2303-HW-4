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
	bool addOrg(int r, int c, Organism* org, bool isAnt);//added because we will need to keep track of all orgs in grid
	bool removeOrg(int r, int c, Organism* org);

	void printGrid();

	virtual ~Grid();
};

#endif /* GRID_H_ */
