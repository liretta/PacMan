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
	mpCurPoint = { top, left, right, bottom };
	//int tempDirection = rand() % 4; //randrom direction for chost
	//mpCurDirection = (Direction) tempDirection;

	//TEST: direction 
	mpCurDirection = RIGHT;

};

ObjectGhost::~ObjectGhost() {};

void ObjectGhost::Draw(HDC hDC, HWND hWnd)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;

	hBr = CreateSolidBrush(RED);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);
	

	int x = mpCurBox.x*BOXSIZE, 
		y = mpCurBox.y*BOXSIZE,
		x_2= x+BOXSIZE,
		y_2 = y+BOXSIZE;

	Ellipse(hdc, x, y, x_2, y_2);

	//bottom square for legs
	Rectangle(hdc, x, y + BOXSIZE / 2, x + BOXSIZE, y + BOXSIZE);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	//small rectangles for legs
	int x1, y1;
	int x2, y2;
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
	DeleteObject(hBr);
	//ReleaseDC(hWnd, hdc);
};

//void Draw(const Point drawBoxCoordinate);

//try to move ghost: 1 step in the current direction 
//current direction is selected based on the position of pacman
//return true if position could be changed, Return false if ghost can't move
bool ObjectGhost::Move(Objects NextObject, Point& NewBoxPosition, bool &GameStatus, GamerStatus &gamer, HWND hWnd)
{
	//1. check, what object there are in next chost's position in current directions
	//2. in switch:
	//2.1 if threasure: assign new position to chost, in mpBoard assign new position as ghost+threasure 
	//3.2 if ghost1, ghost2, ghost+treasure -//- = ignore, update window withour change position
	//3.3 if start-point - check, if threasure !=0, new paxcam position = exitpoint-1
	//4.if wall - just update window
	//5.if pacman =draw loser
	switch (NextObject)
	{
	case EMPTY:
	{
		mpCurBox = NewBoxPosition;//location objects on board 
		mpCurPoint.top = NewBoxPosition.y*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = NewBoxPosition.x*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case TREASURE:
	{
		mpCurBox = NewBoxPosition;//location objects on board 
		mpCurPoint.top = NewBoxPosition.y*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = NewBoxPosition.x*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case GHOST1:
		return false;
	break;
	case GHOST2:
		//need destoy window or draw new game after press "OK" 
		return false;
	break;
	case WALL:
		return false;
	break;
	case GHOST1TREASURE:
		return false;
	break;
	case GHOST2TREASURE:
		return false;
	break;
	case STARTPOINT:
	{
		//pacman stay on same line, but moving to the another side of this line,
		mpCurBox.x = BOARDWIDTH - 2;
		mpCurPoint.top = mpCurBox.x*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = mpCurBox.y*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case EXITPOINT:
	{
		mpCurBox.x = 1; //pacman stay on same line, but moving to the another side of this line,
		mpCurPoint.top = mpCurBox.x*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = mpCurBox.y*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
	break;
	case PACMAN:
	{
		gamer = LOSER;
		GameStatus = false;
		MessageBox(hWnd, (LPCTSTR)L"OH, NO! YOU ARE DIED :( ", (LPCWSTR)L"Game over", MB_OK);
		return false;
	}
	default:
		break;
	}
	return false;
}

//void Turn(){}; //posible, function must take key-code



