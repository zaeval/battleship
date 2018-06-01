#include "GameManager.h"
#include "Player.h"
#include "Aircraft.h"
#include "BattleShip.h"
#include "Destroyer.h"
#include "Cruiser.h"
#include <cstdlib>
#include <ctime>

GameManager::GameManager()
{
	m_Attacker = NULL;
	m_Defender = NULL;
	m_Ships = NULL;
	m_GameMode = GAME_MODE::PLAY_INPUT;
	int m_Turn = 0;
}

GameManager::~GameManager()
{
	if (m_Attacker != NULL)
		delete m_Attacker;
	if (m_Defender != NULL)
		Player * m_Defender;
	if (m_Ships != NULL) {
		m_Ships->clear();
		delete m_Ships;
	}
}
bool GameManager::CheckCollision(
	 IN const int x,
	 IN const int y,
	 IN const ROTATE_TYPE rotate,
	 IN const int size
) {
	if (rotate == ROTATE_TYPE::HORIZONTAL && x+size > MAP_SIZE) {
		return true;
	}
	if (rotate == ROTATE_TYPE::VERTICAL && y+size > MAP_SIZE) {
		return true;
	}
	for (int si = 0; si < m_Ships->size(); ++si) {
		Position *check_Position = (*m_Ships)[si]->GetPosition();
		ROTATE_TYPE check_Rotate = (*m_Ships)[si]->GetRotate();
		int check_size = (*m_Ships)[si]->GetSize();

		if (check_Rotate == ROTATE_TYPE::HORIZONTAL) {
			if (rotate == ROTATE_TYPE::VERTICAL) {
				if (check_Position->x <= x
					&& x <= check_Position->x + check_size
					&& check_Position->y <= y + size
					&& check_Position->y >= y
					) {
					return true;
				}
			}
			else if (rotate == ROTATE_TYPE::HORIZONTAL) {
				if (((check_Position->x <= x + size) ||
					(check_Position->x + check_size >= x))
					&& check_Position->y ==y
					) {
					return true;
				}
			}
		}
		else if (check_Rotate == ROTATE_TYPE::VERTICAL) {
			if (rotate == ROTATE_TYPE::HORIZONTAL) {
				if (check_Position->y <= y
					&& y <= check_Position->y + check_size
					&& check_Position->x <= x + size
					&& check_Position->x >= x
					) {
					return true;
				}
			}
			else if (rotate == ROTATE_TYPE::VERTICAL) {
				if (((check_Position->y <= y + size )||
					(check_Position->y+check_size >= y))
					&& check_Position->x == x
					) {
					return true;
				}
			}
		}
	}
	return false;
}
void GameManager::Init(
	IN const GAME_MODE mode,
	IN const int aircraft_Num,
	IN const int battle_Ship_Num,
	IN const int cruiser_Num,
	IN const int destroyer_Num
) {
	m_GameMode = mode;
	m_Attacker = new Player();
	m_Defender = new Player();
	m_Turn = 0;

	const int TOTAL_SHIP_NUM = aircraft_Num + battle_Ship_Num + cruiser_Num + destroyer_Num;

	m_Ships = new SHIPS();
	m_Ships->reserve(TOTAL_SHIP_NUM);

	srand(time(NULL));
	for (int ai = 0; ai < aircraft_Num; ++ai) {
		int rotate_Rand = rand() % 2;
		int x_Rand = rand() % MAP_SIZE;
		int y_Rand = rand() % MAP_SIZE;
		ROTATE_TYPE rotate;
		if (rotate_Rand == 0)
			rotate = ROTATE_TYPE::HORIZONTAL;
		else
			rotate = ROTATE_TYPE::VERTICAL;

		if (!CheckCollision(x_Rand, y_Rand, rotate, (int)SHIP_SIZE::AIRCRAFT)) {
			Position * position = new Position();
			position->x = x_Rand;
			position->y = y_Rand;
			m_Ships->push_back((Ship*)new Aircraft(position, rotate));
		}
		else {
			--ai;
		}
	}
	for (int bi = 0; bi < battle_Ship_Num; ++bi) {
		int rotate_Rand = rand() % 2;
		int x_Rand = rand() % MAP_SIZE;
		int y_Rand = rand() % MAP_SIZE;
		ROTATE_TYPE rotate;
		if (rotate_Rand == 0)
			rotate = ROTATE_TYPE::HORIZONTAL;
		else
			rotate = ROTATE_TYPE::VERTICAL;

		if (!CheckCollision(x_Rand, y_Rand, rotate, (int)SHIP_SIZE::BATTLESHIP)) {
			Position * position = new Position();
			position->x = x_Rand;
			position->y = y_Rand;
			m_Ships->push_back((Ship*)new BattleShip(position, rotate));
		}
		else {
			--bi;
		}
	}
	for (int ci = 0; ci < cruiser_Num; ++ci) {
		int rotate_Rand = rand() % 2;
		int x_Rand = rand() % MAP_SIZE;
		int y_Rand = rand() % MAP_SIZE;
		ROTATE_TYPE rotate;
		if (rotate_Rand == 0)
			rotate = ROTATE_TYPE::HORIZONTAL;
		else
			rotate = ROTATE_TYPE::VERTICAL;

		if (!CheckCollision(x_Rand, y_Rand, rotate, (int)SHIP_SIZE::CRUISER)) {
			Position * position = new Position();
			position->x = x_Rand;
			position->y = y_Rand;
			m_Ships->push_back((Ship*)new Cruiser(position, rotate));
		}
		else {
			--ci;
		}
	}
	for (int di = 0; di < destroyer_Num; ++di) {
		int rotate_Rand = rand() % 2;
		int x_Rand = rand() % MAP_SIZE;
		int y_Rand = rand() % MAP_SIZE;
		ROTATE_TYPE rotate;
		if (rotate_Rand == 0)
			rotate = ROTATE_TYPE::HORIZONTAL;
		else
			rotate = ROTATE_TYPE::VERTICAL;

		if (!CheckCollision(x_Rand, y_Rand, rotate, (int)SHIP_SIZE::DESTROYER)) {
			Position * position = new Position();
			position->x = x_Rand;
			position->y = y_Rand;
			m_Ships->push_back((Ship*)new Destroyer(position, rotate));
		}
		else {
			--di;
		}
	}

	char attacker_Name[12] = "ATTACKER";

	m_Attacker->Init(ATTACKER_X, ATTACKER_Y, attacker_Name);

	char defender_Name[12] = "DEFENDER";
	m_Defender->Init(DEFENDER_X, DEFENDER_Y, defender_Name);
	m_Defender->SetupShips(m_Ships);

}
void GameManager::AddTurn() {
	++m_Turn;
}
Position * GameManager::AttackByInput(IN WINDOW * const window) {
	char input[3] = { 0, };
	int i = 0;
	int ch = 0;
	nodelay(stdscr, TRUE);

	while (true) {
		if ((ch = mvwgetch(window,2,10+i)) != ERR) {

			switch (ch) {
			case '\b':
			case 127:
			case 8:
			case KEY_BACKSPACE:
				if (i > 0) {
					--i;
					mvwprintw(window, 2, 10 + i, "  ");
				}
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				if (i < 2) {
					input[i] = ch;
					mvwprintw(window, 2, 10 + i, "%c", ch);
					wrefresh(window);

					i++;
				}
				else {
					mvwprintw(window, 3, 2, "can't not more than 2");
					mvwprintw(window, 2, 10 + i, " ");
					i--;
					wrefresh(window);


				}
				break;
			case '\n':
				mvwprintw(window, 2, 10, "  ");

				if (i == 2) {
					if (input[0] >= 'A'
						&& input[0] <= 'Z'
						&& input[1] >= '1'
						&& input[1] <= '9'
						) {
						Position *position = new Position();
						position->y = input[0] - 'A';
						position->x = input[1] - '1';
						return position;
					}
					else {
						mvwprintw(window, 3, 2, "input Error!! (ex A3)");
						wrefresh(window);
						i = 0;


					}
				}
				else {
					mvwprintw(window, 3, 2, "input Error!! (ex A3)");
					wrefresh(window);
					i = 0;

				}
			}


		}
	}
}
GAME_MODE GameManager::GetGameMode() {
	return m_GameMode;
}
SHIPS * GameManager::GetShips() {
	return m_Ships;
}
int GameManager::GetTurn() {
	return m_Turn;
}
bool GameManager::isDeadShip(IN const SHIP_TYPE ship_Type) {
	for (SHIPS::iterator iter = m_Ships->begin(); iter != m_Ships->end(); ++iter) {
		if((*iter)->GetType() == ship_Type && (*iter)->GetHp() >0){
			return false;
		}
	}
	return true;
}
void GameManager::Render() {
	m_Attacker->Render();
	m_Defender->Render();
}
void GameManager::SetGameMode(IN const GAME_MODE gamemode) {
	m_GameMode = gamemode;
}
Player * GameManager::GetInstance(IN const INSTANCE_TYPE instance_Type) {
	if (instance_Type == INSTANCE_TYPE::ATTACKER) {
		return m_Attacker;
	}
	else if (instance_Type == INSTANCE_TYPE::DEFENDER) {
		return m_Defender;
	}
}
