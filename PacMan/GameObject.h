#pragma once
#include "stdafx.h"

class GameObject
{
protected:
	Point mpCurBox;//location objects on board 
	PointTopLeft mpCurPOint; //current coordinate in pixel
	Direction mpCurDirection; //object's current direction

public:
	GameObject() {};
	virtual ~GameObject() {};
	virtual void StartInitialize(Point StartBoxPosition) {};
	//virtual Point GetCurBox() {};
	//virtual PointTopLeft GetCurCoordinate() {};
	//virtual void Draw(const Point drawBoxCoordinate) {};
	virtual void Draw(HDC &hDC, HWND &hWnd) {};
	virtual void Move() {};
};