#include "CBattleShipApp.h"
#include "StatPane.h"
#include "InputPane.h"
#include "GameManager.h"
#include "Player.h"
#include "Ship.h"
#include <curses.h>

CBattleShipApp::CBattleShipApp()
{
	m_pStatPane = NULL;
	m_pInputPane = NULL;
}


CBattleShipApp::~CBattleShipApp()
{
}
void CBattleShipApp::Play() {
	Init();
	Render();
	
	GameManager *GM = new GameManager();
	GM->Init(GAME_MODE::PLAY_INPUT, 1, 1, 1, 2);
	GM->Render();
	while(true){
		Position *input = GM->AttackByInput(m_pInputPane->GetWindow());
		Player *attacker = GM->GetInstance(INSTANCE_TYPE::ATTACKER);
		Player *defender = GM->GetInstance(INSTANCE_TYPE::DEFENDER);
		
		HIT_RESULT hit_Result = attacker->Attack(input,defender);
		if (hit_Result == HIT_RESULT::ALREADY_ATTACK) {
			int x = input->x;
			int y = input->y;
			char pos[3] = { y + 'A',x + '1' };
			string pos_str(pos);
			SetInputStatus(pos_str + " Already Attack!");
		}
		else {
			GM->AddTurn();
			int turn = GM->GetTurn();
			char arr[3] = { turn / 10 + '0',turn % 10 + '0' };
			string str(arr);
			SetStatus("Turn : " + str, 2, 1, DEFAULT_PALETTE::CYAN);
			if (hit_Result == HIT_RESULT::HIT
				|| hit_Result == HIT_RESULT::DESTROY) {
				SHIPS * ships = GM->GetShips();
				for (SHIPS::iterator iter = ships->begin(); iter != ships->end(); ++iter) {
					HIT_RESULT ship_hit_result = (*iter)->HitCheck(input);
					if (ship_hit_result == HIT_RESULT::HIT) {
						int x = input->x;
						int y = input->y;

						char pos[3] = { y + 'A',x + '1' };
						string pos_str(pos);
						SetInputStatus(pos_str + " HIT!");
						attacker->SetHitResult(input, (char)HIT_RESULT::HIT);
						attacker->Render();
						break;
					}
					else if (ship_hit_result == HIT_RESULT::DESTROY) {
						string name = (*iter)->GetName();

						int x = (*iter)->GetPosition()->x;
						int y = (*iter)->GetPosition()->y;
						int size = (*iter)->GetSize();

						ROTATE_TYPE rotate = (*iter)->GetRotate();
						SHIP_TYPE type = (*iter)->GetType();
						string temp_str = "";
						for (int ti = 0; ti < size; ++ti) {
							temp_str += (char)type;
						}
						if(GM->isDeadShip(type))
							SetStatus(name + " : " + temp_str, 2,2 + ((int)type) - 'A', DEFAULT_PALETTE::RED);

						if (rotate == ROTATE_TYPE::VERTICAL) {
							int endY = y + size;
							for (; y < endY; ++y) {
								Position temp = { x,y };
								attacker->SetHitResult(&temp, name[0]);
								attacker->Render();
							}
						}
						else if (rotate == ROTATE_TYPE::HORIZONTAL) {
							int endX = x + size;
							for (; x < endX; ++x) {
								Position temp = { x,y };
								attacker->SetHitResult(&temp, name[0]);
								attacker->Render();
							}
						}

						SetInputStatus((name + "is Destroyed!"));
						
						break;
					}
					else if (ship_hit_result == HIT_RESULT::ALREADY_ATTACK) {
						int x = input->x;
						int y = input->y;
						char pos[3] = { y + 'A',x + '1' };
						string pos_str(pos);
						SetInputStatus(pos_str + " Already Attack!");
					}
				}
			}
			else if (hit_Result == HIT_RESULT::MISS) {
				int x = input->x;
				int y = input->y;
				char pos[3] = { y + 'A',x + '1' };
				string pos_str(pos);
				SetInputStatus(pos_str + " MISS!");
				attacker->SetHitResult(input, (char)HIT_RESULT::MISS);
				attacker->Render();
			}
		}
		int count = 0;
		for (int i = 0; i < GM->GetShips()->size(); ++i) {
			if ((*(GM->GetShips()))[i]->GetHp() == 0) {
				count++;
			}
		}
		if (count == GM->GetShips()->size())
			break;
	}
	SetInputStatus("<<GAME CLEAR>>");
	Destroy();
}
void CBattleShipApp::SetStatus(IN const string status,IN const int x,IN const int y,IN const DEFAULT_PALETTE color ) {
	char out[100] = { 0, };
	strncpy(out, status.c_str(), status.size());
	mvwprintw(m_pStatPane->GetWindow(), y, x, "                        ");

	wattron(m_pStatPane->GetWindow(), COLOR_PAIR(color));

	mvwprintw(m_pStatPane->GetWindow(), y, x, out);

	wattroff(m_pStatPane->GetWindow(), COLOR_PAIR(color));

	wrefresh(m_pStatPane->GetWindow());
}

void CBattleShipApp::SetInputStatus(IN const string status) {
	char out[100] = { 0, };
	strncpy(out, status.c_str(), status.size());
	mvwprintw(m_pInputPane->GetWindow(), 3, 2, "                       ");

	mvwprintw(m_pInputPane->GetWindow(), 3, 2, out);
	wrefresh(m_pInputPane->GetWindow());
}
void CBattleShipApp::Init() {
	initscr();
	start_color();
	cbreak();
	refresh();

	//컬러 세팅
	init_pair((short)DEFAULT_PALETTE::SEA,
		COLOR_GREEN ^ COLOR_BLUE, COLOR_BLUE);

	init_pair((short)DEFAULT_PALETTE::SELECT,
		COLOR_BLUE, COLOR_WHITE);

	init_pair((short)DEFAULT_PALETTE::GREEN,
		COLOR_GREEN, COLOR_BLACK);

	init_pair((short)DEFAULT_PALETTE::CYAN,
		COLOR_CYAN, COLOR_BLACK);

	init_pair((short)DEFAULT_PALETTE::YELLOW,
		COLOR_YELLOW, COLOR_BLACK);

	init_pair((short)DEFAULT_PALETTE::RED,
		COLOR_RED, COLOR_BLACK);

	m_pStatPane = new StatPane(30, 3, 30, 7);
	m_pInputPane = new InputPane(30, 15, 30, 5);

}
void CBattleShipApp::Render() {
	mvprintw(1, 1, "<< Battle Ship Game >>");

	m_pStatPane->Draw();
	m_pInputPane->Draw();

	refresh();
}
void CBattleShipApp::Destroy() {
	wgetch(m_pInputPane->GetWindow());
	if (m_pStatPane != NULL){
		delete m_pStatPane;
	}
	if (m_pInputPane != NULL) {
		delete m_pInputPane;
	}
	endwin();

}