/*
 * Doodlebug.cpp
 *
 *  Created on: Feb 10, 2019
 *      Author: student
 */

#include "Doodlebug.h"

Doodlebug::Doodlebug() {
	// TODO Auto-generated constructor stub

}
bool Doodlebug::move()
{
	bool status = true;
	return status;
}

bool Doodlebug::breed()
{
	bool status = true;
	return status;
}
bool Doodlebug::eat()
{
	bool status = true;
	return status;
}

bool Doodlebug::isStarving() {
	if(stepsSinceLastFood > 3){
		return true;
	}else{
		return false;
	}
}

bool Doodlebug::isPrey() {
	return false;
}

Doodlebug::~Doodlebug() {
	// TODO Auto-generated destructor stub
}

