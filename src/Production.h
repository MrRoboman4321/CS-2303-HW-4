/*
 * Production.h
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "Grid.h"

class Production {
private:
	Grid *grid;

	int gridSize = 20;
	int doodlebugs = 5;
	int ants = 100;
	int time_steps = 1000;
	int seed = 1;
	int pause = -1;
public:
	Production(int argc, char* argv[]);
	bool runProduction();
	virtual ~Production();
};

#endif /* PRODUCTION_H_ */
