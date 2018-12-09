#include "stdafx.h"
#include "Defines.h"
#include "ObjectPacman.h"
#include "GameObject.h"

ObjectPacman::ObjectPacman()
{};

void ObjectPacman::StartInitialize(Point startBoxPosition)
{
	mpCurBox = startBoxPosition;
	int top = startBoxPosition.y*BOXSIZE;
	int left = startBoxPosition.x*BOXSIZE;
	int right = left + BOXSIZE;
	int bottom = top + BOXSIZE;
	mpCurPOint = { top, left, right, bottom };
	mpCurDirection = UP;

};


ObjectPacman::~ObjectPacman() {};

void ObjectPacman::Draw(HDC &hDC, HWND &hWnd)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;

	hBr = CreateSolidBrush(YELLOW);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x = mpCurBox.x, y = mpCurBox.y;
	
	Ellipse(hdc, x, y, x + BOXSIZE, y + BOXSIZE);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	//poligon - pacman's mouth 
	//central point
	int x1 = x + BOXSIZE / 2;
	int y1 = y + BOXSIZE / 2;
	int x2, y2; //upper bound of pacman's mouth
	int x3, y3; //loweer border of pacman's mouth

	switch (mpCurDirection)
	{
	case LEFT:
	{
		x2 = x;
		y2 = y;
		x3 = x2;
		y3 = y + BOXSIZE;
	}
		break;
	case RIGHT:
	{
		x2 = x + BOXSIZE;
		y2 = y;
		x3 = x2;
		y3 = y + BOXSIZE;
	}
		break;
	case UP:
	{
		x2 = x;
		y2 = y;
		x3 = x2+BOXSIZE;
		y3 = y;	
	}
		break;
	case DOWN:
	{
		x2 = x;
		y2 = y+BOXSIZE;
		x3 = x+BOXSIZE;
		y3 = y2;
	}
		break;
	default:
		break;
	}

	POINT poly[3] = { { x1, y1 },{ x2,y2 },{ x3,y3 } };

	hBr = CreateSolidBrush(BLACK);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);
	Polygon(hdc, poly, 3);

	SelectObject(hdc, hOldBr);
	DeleteObject(hOldBr);
	ReleaseDC(hWnd, hdc);
};

//Point GetCurBox();
//PointTopLeft GetCurCoordinate();
//void Draw(const Point drawBoxCoordinate);
//void Move();
//void Turn(){}; //posible, function must take key-code



