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

/**
 * Constructs the Grid
 * @param n sidelength of the 2d grid
 */
Grid::Grid(int n) {
	side_length = n;

    grid = (Organism ***) calloc((size_t) n, sizeof(Organism **));

    for(int i = 0; i < n; i++) {
        grid[i] = (Organism **) calloc((size_t) n, sizeof(Organism *));
    }
}

/**
 * Adds a new organism to the grid, as well as the specific pointer lists.
 * @param r row to add at
 * @param c col to add at
 * @param org organism pointer to keep track of
 * @return whether the cell was empty. If false, no change to the grid was made.
 */
bool Grid::addOrg(int r, int c, Organism *org) {
    if(grid[r][c] != nullptr) {
        return false;
    }

    grid[r][c] = org;

    if(org->isPrey()) {
    	ants.push_back((Ant *) org);
    } else {
    	doodlebugs.push_back((Doodlebug *) org);
    }
}

/**
 * Removes an organism from the grid and vectors, and deconstructs the organism
 * @param r row to remove from
 * @param c col to remove from
 * @return whether or not there was an organism to erase
 */
bool Grid::removeOrg(int r, int c) {
	if(grid[r][c] == nullptr) {
		return false;
	}

	if(grid[r][c]->isPrey()) {
		ants.erase(std::remove(ants.begin(), ants.end(), grid[r][c]), ants.end());
	} else {
		doodlebugs.erase(std::remove(doodlebugs.begin(), doodlebugs.end(), grid[r][c]), doodlebugs.end());
	}

	delete grid[r][c];
	grid[r][c] = nullptr;
}

void Grid::clearBoard() {
	for(int r = 0; r < side_length; r++) {
		for(int c = 0; c < side_length; c++) {
			grid[r][c] = nullptr;
		}
	}

	ants.clear();
	doodlebugs.clear();
}

/**
 * Returns the organism pointed to at grid[r][c]
 * @param r row to get from
 * @param c col to get from
 * @return pointer to the organism. If there was no organism present, nullptr
 */
Organism *Grid::getCellOccupant(int r, int c) {
	if(r >= side_length || r < 0 || c >= side_length || c < 0) {
		return nullptr;
	}

	return grid[r][c];
}

/**
 * Moves an organism from wherever it is to grid[r][c]
 * @param r row to move to
 * @param c col to move to
 * @param o organism to move
 * @return whether or not the destination is empty.
 */
bool Grid::moveOrganism(int r, int c, Organism *o) {
	//If the spot is already taken, the organism cannot move there
	if(grid[r][c] != nullptr) {
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

int Grid::getSideLength() {
	return side_length;
}

/**
 * Updates the state of all organisms currently on the board.
 */
void Grid::tick() {
    for(Ant *ant : ants) {
    	ant->tick();
    }

    for(Doodlebug *doodlebug : doodlebugs) {
    	doodlebug->tick();
    }
}

/**
 * Outputs the grid in a human readable format
 */
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

/**
 * Destructs the grid. Frees the 2d array, then deletes all organisms stored.
 */
Grid::~Grid() {
//	for(int i = 0; i < side_length; i++) {
//		for(int j = 0; j < side_length; j++) {
//			if(grid[i][j] != nullptr) {
//				delete grid[i][j];
//			}
//		}
//		free(grid[i]);
//	}

//	for(Ant *ant : ants) {
//		delete ant;
//	}
//
//	for(Doodlebug *doodlebug : doodlebugs) {
//		delete doodlebug;
//	}

	ants.clear();
	doodlebugs.clear();
}

