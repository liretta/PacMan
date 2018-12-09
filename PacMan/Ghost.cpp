#include "stdafx.h"
#include "Defines.h"
#include "Ghost.h"
#include "GameObject.h"

ObjectGhost::ObjectGhost()
{};

void ObjectGhost::StartInitialize(Point startBoxPosition)
{
	mpCurBox = startBoxPosition;
	int top = startBoxPosition.y*BOXSIZE;
	int left = startBoxPosition.x*BOXSIZE;
	int right = left + BOXSIZE;
	int bottom = top + BOXSIZE;
	mpCurPOint = { top, left, right, bottom };
	int tempDirection = rand() % 4; //randrom direction for chost
	mpCurDirection = (Direction) tempDirection;

};

ObjectGhost::~ObjectGhost() {};

void ObjectGhost::Draw(HDC &hDC, HWND &hWnd)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;

	hBr = CreateSolidBrush(RED);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);
	

	int x = mpCurBox.x, y = mpCurBox.y;
	Ellipse(hdc, x, y, x + BOXSIZE, y + BOXSIZE);

	//bottom square for legs
	Rectangle(hdc, x, y + BOXSIZE / 2, x + BOXSIZE, y + BOXSIZE);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	//small rectangles for legs
	int x1, x2, y1, y2;
	hBr = CreateSolidBrush(BLACK);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	x1 = x + BOXSIZE / 5;
	y1 = y + BOXSIZE / 4 * 3;
	x2 = x1 + BOXSIZE / 5;
	y2 = y + BOXSIZE;
	Rectangle(hdc, x1, y1, x2, y2);

	x1 = x + BOXSIZE / 5 * 3;
	y1 = y + BOXSIZE / 4 * 3;
	x2 = x1 + BOXSIZE / 5;
	y2 = y + BOXSIZE;
	Rectangle(hdc, x1, y1, x2, y2);

	SelectObject(hdc, hOldBr);
	DeleteObject(hOldBr);
	ReleaseDC(hWnd, hdc);
};

//Point GetCurBox();
//PointTopLeft GetCurCoordinate();
//void Draw(const Point drawBoxCoordinate);
//void Move();
//void Turn(){}; //posible, function must take key-code



