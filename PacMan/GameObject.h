#pragma once
#include "stdafx.h"

class GameObject
{
protected:
	Point mpCurBox;//location objects on board 
	PointTopLeft mpCurPoint; //current coordinate in pixel
	Direction mpCurDirection; //object's current direction

public:
	GameObject() {};
	virtual ~GameObject() {};
	virtual void StartInitialize(Point StartBoxPosition) {};
	Direction GetCurDirection() { return mpCurDirection;};
	Point GetCurBox() { return mpCurBox; };
	PointTopLeft GetCurCoordinate() { return mpCurPoint; };
	void SetNewDirection(const Direction NewDirection) { mpCurDirection = NewDirection; };
	virtual void Draw(HDC hDC)=0;
};