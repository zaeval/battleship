#include "BattleShip.h"

BattleShip::BattleShip(Position *position,ROTATE_TYPE rotate)
	:Ship(4,"BATTLESHIP",position,4,SHIP_TYPE::BATTLESHIP,
		rotate)
{
}

BattleShip::~BattleShip()
{
}
