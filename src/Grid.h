/*
 * Grid.h
 *
 *  Created on: Feb 9, 2019
 *      Author: student
 */

#ifndef GRID_H_
#define GRID_H_

#include <vector>

#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

class Ant;
class Doodlebug;

class Grid {
private:
	Organism ***grid;

	int side_length;

	std::vector<Ant*> ants;
	std::vector<Doodlebug*> doodlebugs;

public:
	Grid(): Grid(20){};
	explicit Grid(int n);

	Organism *getCellOccupant(int r, int c);

	bool addOrg(int r, int c, Organism *org); //added because we will need to keep track of all orgs in grid
	bool removeOrg(int r, int c);
	bool removeOrg(Organism *org);

	void clearBoard();

	bool moveOrganism(int r, int c, Organism *o);

    void tick();

	void printGrid();

	virtual ~Grid();
};

#endif /* GRID_H_ */
