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

	struct Pos{
		int r;
		int c;
	};
	enum direction{
		Up,
		Right,
		Down,
		Left
	};
	int stepsSinceLastBreed = 0;
	int row = 0;
	int stepsTillBreed;
	int col = 0;

	Organism* neighbors[4];
	void clearNeighbors();
	virtual int findNeighbors() = 0;
	Pos gridPosGivenMoveOption(direction o);
public:
	int getRow() const;

	int getCol() const;

	Organism();
	Organism(bool b);

	bool isPrey();

	Pos whereToMove();

	virtual bool move() = 0;
	virtual bool breed();

	virtual void tick();

	void setAmAnt(bool b);

	virtual ~Organism();
};

#endif /* ORGANISM_H_ */
