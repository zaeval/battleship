#ifndef PLAYER_H
#define PLAYER_H

#include "Define.h"
#include <vector>

using namespace std;

class CBattleShipMap;
class Ship;

class Player
{
public:
	Player();
	~Player();
	HIT_RESULT			Attack(
							IN const Position *const position, 
							IN Player * defender
						);

	void				Init(int pos_X, int pos_Y, char name[]);

	void				Render();

	void				SetHitResult(
							IN const Position *const position,
							IN const char hitResult
						);

	void				SetupShips(IN const vector<Ship *> *const ships);
	
	CBattleShipMap *	GetMap();

protected:
	CBattleShipMap *	m_map;

};
#endif
