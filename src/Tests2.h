/*
 * Tests2.h
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */

#ifndef TESTS2_H_
#define TESTS2_H_

#include "Grid.h"

class Tests2 {
private:
	Grid *grid;
public:
	Tests2();
	bool doTests();
	bool gridTest();
	bool antsMoveTest();
	bool antsBreedTest();
	bool antsDieTest();
	bool doodleMoveTest();
	bool doodleBreedTest();
	bool doodleEatTest();
	bool doodleDietest();

	bool gridAddTest();
	bool gridMoveTest();
	bool gridRemoveTest();

	virtual ~Tests2();
};

#endif /* TESTS2_H_ */
