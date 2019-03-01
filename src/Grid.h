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
	Organism ***grid;

	int side_length;

public:
	Grid(): Grid(20){};
	explicit Grid(int n);

	bool setCellOccupant(int r, int c, Organism *o);
	Organism *getCellOccupant(int r, int c);

	bool addOrg(int r, int c, Organism* org, bool isAnt);//added because we will need to keep track of all orgs in grid
	bool removeOrg(int r, int c, Organism* org);


	bool moveOrganism(int r, int c, Organism *o);


	void printGrid();

	virtual ~Grid();
};

#endif /* GRID_H_ */
