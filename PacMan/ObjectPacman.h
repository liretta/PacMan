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
	PointTopLeft GetCurCoordinate() {};
	Point GetCurBox();
	//Direction GetCurDirection();
	//void Draw(const Point drawBoxCoordinate) {};
	void Draw(HDC hDC, HWND hWnd);
	void SetNewDirection(Direction newDirect);
	bool Move(Objects NextObject, Point& NewBoxPosition, unsigned int &mCurTreasureCount, bool &GameStatus, GamerStatus &gamer, HWND hWnd); //try to change pacman position. return true if position could be changed and we need to rewrite mpBoardObject. Return false if pacman can't move
	//void Turn(){}; //posible, function must take key-code
};

