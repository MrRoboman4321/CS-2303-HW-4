/*
 * Organism.h
 *
 *  Created on: Feb 7, 2019
 *      Author: student
 */


#ifndef ORGANISM_H_
#define ORGANISM_H_




class Organism {
protected:

	enum moveOption{
		up,
		right,
		down,
		left
	};
    int stepsSinceLastBreed = 0;
    int row = 0;
    int col = 0;

	int neighbors[4];
	virtual void clearNeighbors();
	 int findNeighbors();

public:
	Organism();
	Organism(bool b);

	bool isPrey();

	virtual bool move() = 0;
	virtual bool breed() = 0;

	void setAmAnt(bool b);
	virtual void clearNeighbors();
	virtual int findNeighbors();
	virtual ~Organism();
};

#endif /* ORGANISM_H_ */
