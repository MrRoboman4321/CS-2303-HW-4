/*
 * Tests2.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */

#include "Tests2.h"
#include "Grid.h"
#include "Ant.h"
#include "Doodlebug.h"
#include <iostream>


Tests2::Tests2() {
	// TODO Auto-generated constructor stub
	//initialize the grid

	grid = new Grid();
}

bool Tests2::doTests()
{
	bool results;
	//establish a grid
	bool ok1 = gridTest();
	//populate it with ants

	//see whether they move
	bool ok3 = antsMoveTest();
	//see whether they breed
	bool ok4 = antsBreedTest();
	//see whether they die?

	//populate with doodlebugs

	//see whether they move
	bool ok7 = doodleMoveTest();
	//see whether they breed
	bool ok8 = doodleBreedTest();
	//see whether they eat ants
	bool ok9 = doodleEatTest();
	//see whether they die
	bool ok10 = doodleDietest();


	bool ok12 = gridAddTest();
	bool ok13 = gridMoveTest();
	bool ok14 = gridRemoveTest();
	results = ok1 && ok3 && ok4 && ok7 && ok8 && ok9 && ok10 && ok12 && ok13 && ok14;

	delete grid;

	return results;
}
bool Tests2::gridTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	std::cout << "Running the grid test" << std::endl;
	if(grid->getCellOccupant(2, 3)!= nullptr)
	{
		std::cout << "Cell not initially empty" << std::endl;
		ok1 = false;
	}
	//std::cout << "second grid test" << std::endl;
	Ant* ant = new Ant(2,3,grid);
	grid->addOrg(2, 3, ant);
	if(!grid->getCellOccupant(2, 3)->isPrey())
	{
		std::cout << "Cell not set to ant" << std::endl;
		ok2 = false;
	}

	grid->clearBoard();
	//std::cout << "third grid test" << std::endl;
	result = ok1 && ok2;
	return result;
}


bool Tests2::antsMoveTest()
{

	std::cout << "Running the move ants test" << std::endl;
	Ant* ant = new Ant(3,3,grid);
	grid->addOrg(3,3, ant);
	ant->tick();
	bool result = grid->getCellOccupant(3,3) == nullptr;

	grid->clearBoard();

	return result;
}
bool Tests2::antsBreedTest()
{
	bool result = true;
	std::cout << "Running the breed ants test" << std::endl;
	Ant* ant = new Ant(3,3,grid);
	grid->addOrg(3,3, ant);
	ant->tick();
	ant->tick();
	ant->tick();
	ant->tick();
	ant->tick();
	int antCount = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			Organism* org = grid->getCellOccupant(i,j);
			if(org != nullptr && org->isPrey()){
				antCount++;
			}
		}
	}

	grid->clearBoard();

	return result;
}


bool Tests2::doodleMoveTest()
{

	std::cout << "Running the move doodlebugs test" << std::endl;
	Doodlebug* doodlebug = new Doodlebug(3,3,grid);
	grid->addOrg(3,3, doodlebug);
	doodlebug->tick();
	bool result = grid->getCellOccupant(3,3) == nullptr;

	grid->clearBoard();

	return result;
}
bool Tests2::doodleBreedTest()
{
	bool result = true;

	std::vector<Ant *> ants;

	std::cout << "Running the breed doodlebugs test" << std::endl;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 5; ++j) {
			Ant *ant = new Ant(i, j, grid);

			ants.push_back(ant);
			grid->addOrg(i,j, ant);
		}
	}
	Doodlebug* bug = new Doodlebug(5,5,grid);
	grid->addOrg(5,5, bug);
	int doodlebugCount = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			Organism* org = grid->getCellOccupant(i,j);
			if(org != nullptr && !org->isPrey()){
				doodlebugCount++;
			}
		}
	}

	grid->clearBoard();

	return doodlebugCount > 1;
}
bool Tests2::doodleEatTest()
{
	bool result = true;
	std::cout << "Running the eat ant test" << std::endl;
	Grid myGrid = Grid(6);
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 5; ++j) {
			grid->addOrg(i,j, new Ant(i,j,grid));
		}
	}
	Doodlebug* bug = new Doodlebug(5,5,grid);
	grid->addOrg(5,5, bug);
	bug->tick();
	bug->tick();
	bug->tick();
	result = !bug->isStarving();

	grid->clearBoard();

	return result;
}
bool Tests2::doodleDietest()
{
	bool result;
	Grid myGrid = Grid(6);
	std::cout << "Running the doodlebug dies test" << std::endl;
	Doodlebug* bug = new Doodlebug(5,5,grid);
	grid->addOrg(5,5, bug);
	bug->tick();
	bug->tick();
	bug->tick();
	bug->tick();
	int isNotDead = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if(grid->getCellOccupant(i,j) != nullptr){
				isNotDead++;
			}
		}
	}
	if(isNotDead > 0){
		result = false;
	}else{
		result = true;
	}

	grid->clearBoard();

	return result;
}

bool Tests2::gridAddTest() {
	Ant *ant = new Ant();

	grid->addOrg(5, 5, ant);

	bool result = grid->getCellOccupant(5, 5) == ant;

	grid->clearBoard();
	delete ant;

	return result;
}

bool Tests2::gridMoveTest() {
	Ant *ant = new Ant();

	grid->addOrg(5, 5, ant);
	grid->moveOrganism(10, 10, ant);

	bool result = grid->getCellOccupant(10, 10) == ant;

	grid->clearBoard();
	delete ant;

	return result;
}

bool Tests2::gridRemoveTest() {
	Ant *ant = new Ant();

	grid->addOrg(5, 5, ant);
	grid->removeOrg(5, 5);

	bool result = grid->getCellOccupant(5, 5) == nullptr;

	grid->clearBoard();

	return result;
}

Tests2::~Tests2() {
	// TODO Auto-generated destructor stub
}

