#include "CBattleShipMap.h"


CBattleShipMap::CBattleShipMap(int m_PosX,int m_PosY,char name[])
	:Pane(m_PosX,m_PosY,MAP_SIZE+2,MAP_SIZE+2)
{
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			m_mapData[i][j] = '0';
		}
	}
	for (int i = 0; i < MAP_SIZE; ++i) {
		mvprintw(i + 1 + m_y, m_x - 1, "%c", 'A' + i);
		mvprintw(m_y + m_height, m_x + 1 + i, "%d", 1 + i);
	}

	mvwprintw(m_pWindow, 0, 2, name);
	for (int i = 0; i < 12; ++i) {
		m_name[i] = name[i];
	}
}

CBattleShipMap::~CBattleShipMap()
{
}

void CBattleShipMap::Draw() {
	wattron(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::GREEN));
	//¦¡ ¦¢ ¦£ ¦¤ ¦¥ ¦¦
	wborder(m_pWindow, '|', '|', '-', '-', '-', '-', '-', '-');
	wattron(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::SEA));

	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			if (m_mapData[i][j] != '0') {
				wattron(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::SELECT));
			}
			else {
				wattron(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::SEA));

			}
			mvwprintw(m_pWindow, i + 1, j + 1, "%c", m_mapData[i][j]);
			wattroff(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::SELECT));
		}
	}
	wattroff(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::SEA));

	wattron(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::GREEN));
	mvwprintw(m_pWindow, 0, 1, m_name);
	wattroff(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::GREEN));

	wrefresh(m_pWindow);

}

void CBattleShipMap::SetData(
	IN const Position * position, 
	IN const char data) {
	m_mapData[position->y][position->x] = data;
}

char CBattleShipMap::GetData(
	IN const Position * position
){
	return m_mapData[position->y][position->x];
}

