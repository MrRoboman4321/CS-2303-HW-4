/*
 * Organism.h
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */

#ifndef ORGANISM_H_
#define ORGANISM_H_

class Organism {
private:
    int stepsSinceLastBreed = 0;
    int row = 0;
    int col = 0;

public:
	Organism();
	Organism(bool b);

	bool isPrey();

	virtual bool move() = 0;
	virtual bool breed() = 0;

	void setAmAnt(bool b);

	virtual ~Organism();
};

#endif /* ORGANISM_H_ */
