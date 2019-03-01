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
}

bool Tests2::doTests()
{
	bool results;
	//establish a grid
	bool ok1 = gridTest();
	//populate it with ants
	bool ok2 = makeAntsTest();
	//see whether they move
	bool ok3 = antsMoveTest();
	//see whether they breed
	bool ok4 = antsBreedTest();
	//see whether they die?
	bool ok5 = antsDieTest();//maybe if they wander off?
	//populate with doodlebugs
	bool ok6 = makeDoodlesTest();
	//see whether they move
	bool ok7 = doodleMoveTest();
	//see whether they breed
	bool ok8 = doodleBreedTest();
	//see whether they eat ants
	bool ok9 = doodleEatTest();
	//see whether they die
	bool ok10 = doodleDietest();

	bool ok11 = gridTest();
	bool ok12 = gridAddTest();
	bool ok13 = gridMoveTest();
	bool ok14 = gridRemoveTest();
	results = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8 && ok9 && ok10 && ok11 && ok12 && ok13 && ok14;
	return results;
}
bool Tests2::gridTest()
{
	bool result = true;
	bool ok1 = true;
	bool ok2 = true;
	std::cout << "Running the grid test" << std::endl;
	Grid myGrid = Grid(8);
	if(myGrid.getCellOccupant(2, 3)!= nullptr)
	{
		std::cout << "Cell not initially empty" << std::endl;
		ok1 = false;
	}
	//std::cout << "second grid test" << std::endl;
	Ant* ant = new Ant(2,3,&myGrid);
	myGrid.addOrg(2, 3, ant);
	if(!myGrid.getCellOccupant(2, 3)->isPrey())
	{
		std::cout << "Cell not set to ant" << std::endl;
		ok2 = false;
	}
	//std::cout << "third grid test" << std::endl;
	myGrid.~Grid();
	result = ok1 && ok2;
	return result;
}


bool Tests2::antsMoveTest()
{

	std::cout << "Running the move ants test" << std::endl;
	Grid myGrid = Grid(6);
	Ant* ant = new Ant(3,3,&myGrid);
	myGrid.addOrg(3,3, ant);
	ant->tick();


	return myGrid.getCellOccupant(3,3) == nullptr;
}
bool Tests2::antsBreedTest()
{
	bool result = true;
	std::cout << "Running the breed ants test" << std::endl;
	Grid myGrid = Grid(6);
	Ant* ant = new Ant(3,3,&myGrid);
	myGrid.addOrg(3,3, ant);
	ant->tick();
	ant->tick();
	ant->tick();
	ant->tick();
	ant->tick();
	int antCount = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			Organism* org = myGrid.getCellOccupant(i,j);
			if(org != nullptr && org->isPrey()){
				antCount++;
			}
		}
	}
	return result;
}


bool Tests2::doodleMoveTest()
{

	std::cout << "Running the move doodlebugs test" << std::endl;
	Grid myGrid = Grid(6);
	Doodlebug* doodlebug = new Doodlebug(3,3,&myGrid);
	myGrid.addOrg(3,3, doodlebug);
	doodlebug->tick();


	return myGrid.getCellOccupant(3,3) == nullptr;
}
bool Tests2::doodleBreedTest()
{
	bool result = true;
	std::cout << "Running the breed doodlebugs test" << std::endl;
	Grid myGrid = Grid(6);
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 5; ++j) {
			myGrid.addOrg(i,j, new Ant(i,j,&myGrid));
		}
	}
	Doodlebug* bug = new Doodlebug(5,5,&myGrid);
	myGrid.addOrg(5,5, bug);
	int doodlebugCount = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			Organism* org = myGrid.getCellOccupant(i,j);
			if(org != nullptr && !org->isPrey()){
				doodlebugCount++;
			}
		}
	}

	return doodlebugCount > 1;
}
bool Tests2::doodleEatTest()
{
	bool result = true;
	std::cout << "Running the eat ant test" << std::endl;
	Grid myGrid = Grid(6);
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 5; ++j) {
			myGrid.addOrg(i,j, new Ant(i,j,&myGrid));
		}
	}
	Doodlebug* bug = new Doodlebug(5,5,&myGrid);
	myGrid.addOrg(5,5, bug);
	bug->tick();
	bug->tick();
	bug->tick();
	result = !bug->isStarving();

	return result;
}
bool Tests2::doodleDietest()
{
	bool result;
	Grid myGrid = Grid(6);

	Doodlebug* bug = new Doodlebug(5,5,&myGrid);
	myGrid.addOrg(5,5, bug);
	bug->tick();
	bug->tick();
	bug->tick();
	bug->tick();
	int isNotDead = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if(myGrid.getCellOccupant(i,j) != nullptr){
				isNotDead++;
			}
		}
	}
	if(isNotDead > 0){
		result = false;
	}else{
		result = true;
	}
	std::cout << "Running the doodlebug dies test" << std::endl;
	return result;
}

bool Tests2::gridAddTest() {
	Grid *grid = new Grid();
	Ant *ant = new Ant();

	grid->addOrg(5, 5, ant);

	bool result = grid->getCellOccupant(5, 5) == ant;

	delete grid;
	delete ant;

	return result;
}

bool Tests2::gridMoveTest() {
	Grid *grid = new Grid();
	Ant *ant = new Ant();

	grid->addOrg(5, 5, ant);
	grid->moveOrganism(10, 10, ant);

	bool result = grid->getCellOccupant(10, 10) == ant;

	delete grid;
	delete ant;

	return result;
}

bool Tests2::gridRemoveTest() {
	Grid *grid = new Grid();
	Ant *ant = new Ant();

	grid->addOrg(5, 5, ant);
	grid->removeOrg(5, 5);

	bool result = grid->getCellOccupant(5, 5) == nullptr;

	delete grid;
	delete ant;

	return result;
}

Tests2::~Tests2() {
	// TODO Auto-generated destructor stub
}

