#include "Aircraft.h"


Aircraft::Aircraft(Position * position, ROTATE_TYPE rotate)
	:Ship(5, "AIRCRAFT", position, 5, 
		SHIP_TYPE::AIRCRAFT,
		rotate)
{
}


Aircraft::~Aircraft()
{
}
