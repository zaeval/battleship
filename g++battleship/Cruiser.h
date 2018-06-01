#ifndef CRUISER_H
#define CRUISER_H

#include "Ship.h"
class Cruiser:Ship
{
public:
	Cruiser(Position * position, ROTATE_TYPE rotate);
	virtual ~Cruiser();
};
#endif
