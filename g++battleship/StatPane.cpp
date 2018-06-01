#include "StatPane.h"

StatPane::StatPane(int x,int y,int width,int height)
	:Pane(x,y,width,height)
{
	mvwprintw(m_pWindow, 0, 3, "< STATUS >");
}


StatPane::~StatPane()
{
}

void StatPane::Draw() {
	
	wattron(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::CYAN));
	mvwprintw(m_pWindow, 1, 2, "Turn : 00");

	mvwprintw(m_pWindow, 2, 2, "AIRCRAFT : AAAAA");
	mvwprintw(m_pWindow, 3, 2, "BATTLESHIP : BBBB");
	mvwprintw(m_pWindow, 4, 2, "CRUISER : CCC");
	mvwprintw(m_pWindow, 5, 2, "DESTROYER : DD DD");

	mvwprintw(m_pWindow, 0, 3, "< STATUS >");

	wattroff(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::CYAN));

	wrefresh(m_pWindow);
}
