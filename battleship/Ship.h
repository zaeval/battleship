#ifndef SHIP_H
#define SHIP_H

#include "Define.h"
#include <string>

using namespace std;

class Ship
{
public:
	Ship(
		int hp,
		std::string name,
		Position *position,
		int size,
		SHIP_TYPE type,
		ROTATE_TYPE rotete
	);
	virtual ~Ship();

	string				GetName();
	Position *			GetPosition();
	int					GetSize();
	SHIP_TYPE			GetType();
	ROTATE_TYPE			GetRotate();

	HIT_RESULT			HitCheck(IN const Position *const position);

	int					GetHp();

	void				SetPosition(IN const Position *const position);

protected:
	int					m_Hp;
	string				m_Name;
	Position *			m_Position;
	int					m_Size;
	SHIP_TYPE			m_Type;
	ROTATE_TYPE			m_Rotate;
};

#endif