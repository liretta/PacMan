#pragma once
#include "stdafx.h"
#include "GameObject.h"
//#include "Defines.h"

class ObjectGhost: public GameObject
{
private:

public:
	ObjectGhost();
	~ObjectGhost();
	void StartInitialize(Point StartBoxPosition);
	//void Draw(const Point drawBoxCoordinate) {};
	void Draw(HDC hDC, HWND hWnd);
	bool Move(Objects NextObject, Point& NewBoxPosition, bool &GameStatus, GamerStatus &gamer, HWND hWnd); //return true if position could be changed, Return false if ghost can't move
	
};
