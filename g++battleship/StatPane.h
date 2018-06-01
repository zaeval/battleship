#ifndef STATEPANE_H
#define STATEPANE_H

#include "Pane.h"
#include "Define.h"

class StatPane : public Pane
{
public:
	StatPane(int x, int y, int width,int height);
	~StatPane();
	
	virtual void Draw();
};
#endif
