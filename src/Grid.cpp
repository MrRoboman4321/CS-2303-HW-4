/*
 * Grid.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: student
 */

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "Grid.h"

int n = 0; //this initial value will be changed when the program is invoked

Grid::Grid(int n) {
	side_length = n;

    grid = (Organism ***) calloc((size_t) n, sizeof(Organism **));

    for(int i = 0; i < n; i++) {
        grid[i] = (Organism **) calloc((size_t) n, sizeof(Organism *));
    }
}

bool Grid::addOrg(int r, int c, Organism *org) {
    if(grid[r][c] == nullptr) {
        return false;
    }

    grid[r][c] = org;

    if(org->isPrey()) {
    	ants.push_back((Ant *) org);
    } else {
    	doodlebugs.push_back((Doodlebug *) org);
    }
}

bool Grid::removeOrg(int r, int c) {
	if(grid[r][c] == nullptr) {
		return false;
	}

	if(grid[r][c]->isPrey()) {
		ants.erase(std::remove(ants.begin(), ants.end(), grid[r][c]), ants.end());
	} else {
		doodlebugs.erase(std::remove(doodlebugs.begin(), doodlebugs.end(), grid[r][c]), doodlebugs.end());
	}
}

Organism *Grid::getCellOccupant(int r, int c) {
	return grid[r][c];
}

bool Grid::moveOrganism(int r, int c, Organism *o) {
	//If the spot is already taken, the organism cannot move there
	if(grid[r][c] == nullptr) {
		return false;
	}

	//Search through all cells
	for(int i = 0; i < side_length; i++) {
		for(int j = 0; j < side_length; j++) {

			//If we find the cell where the organism is
			if(grid[i][j] == o) {

				//Remove it from its old spot
				grid[i][j] = nullptr;

				//Move to the new spot
				grid[r][c] = o;
			}
		}
	}
}

void Grid::tick() {
    for(int r = 0; r < side_length; r++) {
        for(int c = 0; c < side_length; c++) {
            if(grid[r][c]->isPrey()) {
                grid[r][c]->tick();
            }
        }
    }

    for(int r = 0; r < side_length; r++) {
        for(int c = 0; c < side_length; c++) {
            if(!grid[r][c]->isPrey()) {
                grid[r][c]->tick();
            }
        }
    }
}

void Grid::printGrid() {
	for(int r = 0; r < side_length; r++) {
		for(int c = 0; c < side_length; c++) {
			if(grid[r][c] != nullptr) {
				if(grid[r][c]->isPrey()) {
					printf("o");
				} else {
					printf("x");
				}
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

Grid::~Grid() {
	for(int i = 0; i < side_length; i++) {
		for(int j = 0; j < side_length; j++) {
			delete grid[i][j];
		}
		free(grid[i]);
	}

	for(Ant *ant : ants) {
		delete ant;
	}

	for(Doodlebug *doodlebug : doodlebugs) {
		delete doodlebug;
	}
}

