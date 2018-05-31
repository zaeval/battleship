#ifndef DESTROYER_H
#define DESTROYER_H

#include "Ship.h"

class Destroyer:Ship
{
public:
	Destroyer(Position * position, ROTATE_TYPE rotate);
	virtual ~Destroyer();
};

#endif