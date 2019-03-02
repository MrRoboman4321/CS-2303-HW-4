/*
 * Production.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */

#include <string>
#include <time.h>
#include "Production.h"

Production::Production(int argc, char* argv[]) {
	switch(argc) {
		case 7:
			pause      = std::stoi(argv[6]);
		case 6:
			seed       = std::stoi(argv[5]);
		case 5:
			time_steps = std::stoi(argv[4]);
		case 4:
			ants       = std::stoi(argv[3]);
		case 3:
			doodlebugs = std::stoi(argv[2]);
		case 2:
		default:
			gridSize   = std::stoi(argv[1]);
	}

	if(seed == 0) {
		srand(time(NULL));
	} else {
		srand(seed);
	}
	grid = new Grid(gridSize);
}

bool Production::runProduction()
{
	int i = 0;

	bool result = true;
	while(i < time_steps)
	{
		grid->tick();
		if(pause > 0 && i % pause == 0) {
			grid->printGrid();
		}

		i++;
	}

	return result;
}

Production::~Production() {
	delete grid;
}

