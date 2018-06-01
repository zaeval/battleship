#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Ship.h"
class BattleShip : Ship
{
public:
	BattleShip(Position * position,ROTATE_TYPE rotate);
	virtual ~BattleShip();
};

#endif
