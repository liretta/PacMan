#pragma once
#include "stdafx.h"
#include "GameObject.h"

class ObjectPacman : public GameObject
{
private:

public:
	ObjectPacman();
	~ObjectPacman();
	void StartInitialize(Point StartBoxPosition);
	void Draw(HDC hDC);
	void SetNewDirection(Direction newDirect);
	bool Move(Objects NextObject, Point& NewBoxPosition, unsigned int &mCurTreasureCount, bool &GameStatus, GamerStatus &gamer); //try to change pacman position. return true if position could be changed and we need to rewrite mpBoardObject. Return false if pacman can't move
};

