#include "Destroyer.h"


Destroyer::Destroyer(Position *position, ROTATE_TYPE rotate)
	:Ship(2, "DESTROYER", position, 2, SHIP_TYPE::DESTROYER,
		rotate)
{
}
Destroyer::~Destroyer()
{
}
