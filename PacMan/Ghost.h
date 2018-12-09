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
	Point GetCurBox() {};
	PointTopLeft GetCurCoordinate() {};
	//void Draw(const Point drawBoxCoordinate) {};
	void Draw(HDC &hDC, HWND &hWnd);
	//void Move() {};
};
