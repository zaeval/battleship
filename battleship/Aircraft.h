#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Ship.h"
class Aircraft:Ship
{
public:
	Aircraft(Position * position, ROTATE_TYPE rotate);
	virtual ~Aircraft();
};

#endif