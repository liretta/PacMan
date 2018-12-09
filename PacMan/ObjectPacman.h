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
	Point GetCurBox() {};
	PointTopLeft GetCurCoordinate() {};
	//void Draw(const Point drawBoxCoordinate) {};
	void Draw(HDC &hDC, HWND &hWnd);
	//void Move() {};
	//void Turn(){}; //posible, function must take key-code
};

