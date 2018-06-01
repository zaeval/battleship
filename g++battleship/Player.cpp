#include "Player.h"
#include "CBattleShipMap.h"
#include "Ship.h"

Player::Player()
{
	m_map = NULL;
}

Player::~Player()
{
	if (m_map!= NULL) {
		delete m_map;
	}
}

void Player::Init(int pos_X, int pos_Y, char name[]) {
	m_map = new CBattleShipMap(pos_X, pos_Y, name);
}

HIT_RESULT Player::Attack(IN const Position *const position
	,IN Player * defender) {
	char data = defender->GetMap()->GetData(position);
	char myData = m_map->GetData(position);
	if (
		(char)HIT_RESULT::HIT == myData
		|| (char)HIT_RESULT::MISS == myData
		) {
		return HIT_RESULT::ALREADY_ATTACK;
	}
	else if (
		(char)SHIP_TYPE::AIRCRAFT == data
		||(char)SHIP_TYPE::BATTLESHIP == data
		||(char)SHIP_TYPE::CRUISER == data
		||(char)SHIP_TYPE::DESTROYER == data) {
		return HIT_RESULT::HIT;
	}
	
	else {
		return HIT_RESULT::MISS;
	}
}

void Player::Render() {
	m_map->Draw();
}

CBattleShipMap * Player::GetMap() {
	return m_map;
}

void Player::SetupShips(IN const vector<Ship *> *const ships) {
	for (int i = 0; i < ships->size(); ++i) {
		int x = (*ships)[i]->GetPosition()->x;
		int y = (*ships)[i]->GetPosition()->y;
		int size = (*ships)[i]->GetSize();
		char name = (*ships)[i]->GetName()[0];
		ROTATE_TYPE rotate = (*ships)[i]->GetRotate();

		if(rotate == ROTATE_TYPE::HORIZONTAL){
			for (int sx = x; sx < x+size; ++sx) {
				Position * temp = new Position();
				temp->x = sx;
				temp->y = y;
				m_map->SetData(temp, name);
				delete temp;
			}
		}
		else if (rotate == ROTATE_TYPE::VERTICAL) {
			for (int sy = y; sy < y+size; ++sy) {
				Position * temp = new Position();
				temp->x = x;
				temp->y = sy;
				m_map->SetData(temp, name);
				delete temp;
			}
		}
	}
}

void Player::SetHitResult(IN const Position *const position,
	IN const char hitResult) {
	m_map->SetData(position, hitResult);
}
