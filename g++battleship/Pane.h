#pragma once
#include <curses.h>
class Pane
{
public:
	Pane(int x, int y, int width,int height);
	virtual ~Pane();
	virtual void Draw();
	WINDOW * GetWindow();
protected:
	int		m_width, m_height;
	int		m_x, m_y;
	WINDOW* m_pWindow;
};

