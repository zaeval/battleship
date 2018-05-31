#ifndef CBATTLESHIPAPP_H
#define CBATTLESHIPAPP_H
#include "CBattleShipMap.h"
#include <string>
#include "Define.h"
using namespace std;

class StatPane;
class InputPane;

class CBattleShipApp
{
public:
	CBattleShipApp();
	~CBattleShipApp();

	void			Play();

protected:
	void			Init();
	void			Render();
	void			Destroy();
	void			SetInputStatus(IN const string status);
	void			SetStatus(IN const string status,int,int,DEFAULT_PALETTE);


	StatPane *		m_pStatPane;
	InputPane *		m_pInputPane;
	
};

#endif