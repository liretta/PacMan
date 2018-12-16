#pragma once
#include "stdafx.h"
#include "GameObject.h"

class ObjectGhost: public GameObject
{
private:

public:
	ObjectGhost();
	~ObjectGhost();
	void StartInitialize(Point StartBoxPosition);
	void Draw(HDC hDC);
	bool Move(Objects NextObject, Point& NewBoxPosition, bool &GameStatus, GamerStatus &gamer); //return true if position could be changed, Return false if ghost can't move
};
