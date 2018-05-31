#ifndef INPUTPANE_H
#define INPUTPANE_H

#include "Pane.h"
#include "Define.h"

class InputPane
	:public Pane
{
public:
	InputPane(int x,int y,int width,int height);
	~InputPane();

	virtual void Draw();
};
#endif
