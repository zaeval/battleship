#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Define.h"
#include <vector>
#include <curses.h>

using namespace std;

class Player;
class Ship;

class GameManager
{
public:
	GameManager();
	~GameManager();
	void		Init(
					IN const GAME_MODE mode,
					IN const int aircraft_Num,
					IN const int battle_Ship_Num,
					IN const int cruiser_Num,
					IN const int destroyer_Num
				);
	void		AddTurn();
	Position*	AttackByInput(IN WINDOW * const window);
	GAME_MODE	GetGameMode();
	SHIPS *		GetShips();
	int			GetTurn();
	bool		isDeadShip(IN const SHIP_TYPE);
	void		Render();
	void		SetGameMode(IN const GAME_MODE gamemode);
	Player *	GetInstance(IN const INSTANCE_TYPE instance_Type);
	bool		CheckCollision(
					 IN const int x,
					 IN const int y,
					 IN const ROTATE_TYPE rotate,
					 IN const int size
				);
protected:
	Player *	m_Attacker;
	Player *	m_Defender;
	GAME_MODE	m_GameMode;
	SHIPS *		m_Ships;
	int m_Turn;
};

#endif