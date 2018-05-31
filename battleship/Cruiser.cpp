#include "Cruiser.h"


Cruiser::Cruiser(Position *position, ROTATE_TYPE rotate)
	:Ship(3, "CRUISER", position, 3, SHIP_TYPE::CRUISER,
		rotate)
{
}
Cruiser::~Cruiser()
{
}
