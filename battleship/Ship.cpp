#include "Ship.h"
#define DEAD 0

using namespace std;
Ship::Ship(int hp,
	string name,
	Position *position,
	int size,
	SHIP_TYPE type,
	ROTATE_TYPE rotate
)
{
	this->m_Hp = hp;
	this->m_Name = name;
	this->m_Position = position;
	this->m_Size = size;
	this->m_Type = type;
	this->m_Rotate = rotate;
}


Ship::~Ship()
{
	delete m_Position;
}

std::string Ship::GetName() {
	return m_Name;
}

Position * Ship::GetPosition() {
	return m_Position;
}

int Ship::GetSize() {
	return m_Size;
}

SHIP_TYPE Ship::GetType() {
	return m_Type;
}

int Ship::GetHp() {
	return m_Hp;
}

HIT_RESULT Ship::HitCheck(IN const Position *const position) {
	
	if (m_Rotate == ROTATE_TYPE::HORIZONTAL) {
		if (position->x >= m_Position->x &&
			position->x <= m_Position->x + m_Size &&
			position->y == m_Position ->y
			) {
			if (m_Hp == DEAD) {
				return HIT_RESULT::ALREADY_ATTACK;
			}
			--m_Hp;
			if (m_Hp == DEAD) {
				return HIT_RESULT::DESTROY;
			}
			return HIT_RESULT::HIT;
		}
		else {
			return HIT_RESULT::MISS;
		}
	}
	else if (m_Rotate == ROTATE_TYPE::VERTICAL) {
		if (position->y >= m_Position->y &&
			position->y <= m_Position->y + m_Size &&
			position->x == m_Position->x
			) {
			if (m_Hp == DEAD) {
				return HIT_RESULT::ALREADY_ATTACK;
			}
			--m_Hp;
			if (m_Hp == DEAD) {
				return HIT_RESULT::DESTROY;
			}
			return HIT_RESULT::HIT;
		}
		else {
			return HIT_RESULT::MISS;
		}
	}

}

void Ship::SetPosition(IN const Position *const position) {
	this->m_Position->x = position->x;
	this->m_Position->y = position->y;
}

ROTATE_TYPE Ship::GetRotate() {
	return m_Rotate;
}