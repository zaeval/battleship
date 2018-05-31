#ifndef CBATTLESHIPMAP_H
#define CBATTLESHIPMAP_H

#include "Pane.h"
#include "Define.h"
class CBattleShipMap : Pane
{
public:
	CBattleShipMap(int m_PosX,int m_PosY,char name[]);
	~CBattleShipMap();

	void	Draw();

	void	SetData(IN const Position * position,IN const char data);
	char	GetData(IN const Position * position);
protected:
	char	m_mapData[MAP_SIZE][MAP_SIZE];
	char	m_name[12];
};

#endif