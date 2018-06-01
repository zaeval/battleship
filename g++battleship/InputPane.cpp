#include "InputPane.h"


InputPane::InputPane(int x,int y,int width,int height)
	:Pane(x,y,width,height)
{
	mvwprintw(m_pWindow, 0, 3, "< INPUT >");
}


InputPane::~InputPane()
{
}

void InputPane::Draw() {
	wattron(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::YELLOW));

	mvwprintw(m_pWindow, 1, 2, "Input position...(ex A3)");
	mvwprintw(m_pWindow, 2, 2, "Input : ");
	mvwprintw(m_pWindow, 3, 2, "  ");
	mvwprintw(m_pWindow, 0, 3, "< INPUT >");

	wattroff(m_pWindow, COLOR_PAIR(DEFAULT_PALETTE::YELLOW));

	wrefresh(m_pWindow);
}
