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
	mpCurPoint = { top, left, right, bottom };
	mpCurDirection = LEFT;//change to UP in release version

};


ObjectPacman::~ObjectPacman() {};

void ObjectPacman::Draw(HDC hDC, HWND hWnd)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;

	hBr = CreateSolidBrush(YELLOW);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x = mpCurBox.x*BOXSIZE, 
		y = mpCurBox.y*BOXSIZE,
		x2 = x+BOXSIZE,
		y2 = y+BOXSIZE;
	
	Ellipse(hdc, x, y, x2, y2);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	//poligon - pacman's mouth 
	//central point
	int x1 = x + BOXSIZE / 2;
	int y1 = y + BOXSIZE / 2;
	x2 = 0;
	y2 = 0;
	//int x2, y2; //upper bound of pacman's mouth
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
	DeleteObject(hBr);
	//ReleaseDC(hWnd, hdc);
};

Point ObjectPacman::GetCurBox()
{
	return mpCurBox;
};
//PointTopLeft GetCurCoordinate();
//void Draw(const Point drawBoxCoordinate);

//try to change pacman position - always 1 step in the direction of pacman
//return true if position could be changed and we need to rewrite mpBoardObject
//return false if pacman can't move
bool ObjectPacman::Move(Objects NextObject, Point& NewBoxPosition, unsigned int &mCurTreasureCount, bool &GameStatus, GamerStatus &gamer, HWND hWnd)
{
	//1. check, what object there are in next pacmen's position in current directions
	//2. in switch:
	//2.1 if threasure: treasure quontity --; assign new position to pacman
	//3.2 if ghost1, ghost2, ghost+treasure -//- = draw game over
	//3.3 if start-point - check, if threasure !=0, new paxcam position = exitpoint-1
	//if treasure == 0; draw winner
	//4.if wall - just update window.
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
		mCurTreasureCount = (mCurTreasureCount != 0) ? mCurTreasureCount-- : mCurTreasureCount;
		mpCurBox = NewBoxPosition;//location objects on board 
		mpCurPoint.top = NewBoxPosition.y*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = NewBoxPosition.x*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
		break;
	case GHOST1:
	{	
		//MessageBox(hWnd, (LPCTSTR)L"OH, NO! YOU ARE DIED :( ", (LPCWSTR)L"Game over", MB_OK);
		gamer = LOSER;
		GameStatus = false;
		//need destoy window or draw new game after press "OK" 
		return false;
	}
		break;
	case GHOST2:
	{
		gamer = LOSER;
		GameStatus = false;
		//MessageBox(hWnd, (LPCTSTR)L"OH, NO! YOU ARE DIED :( ", (LPCWSTR)L"Game over", MB_OK);
		//need destoy window or draw new game after press "OK" 
		return false;
	}
		break;
	case WALL:
		return false;
		break;
	case GHOST1TREASURE:
	{
		gamer = LOSER;
		GameStatus = false;
		//MessageBox(hWnd, (LPCTSTR)L"OH, NO! YOU ARE DIED :( ", (LPCWSTR)L"Game over", MB_OK);
		//need destoy window or draw new game after press "OK" 
		return false;
	}
		break;
	case GHOST2TREASURE:
	{
		gamer = LOSER;
		GameStatus = false;
		//MessageBox(hWnd, (LPCTSTR)L"OH, NO! YOU ARE DIED :( ", (LPCWSTR)L"Game over", MB_OK);
		//need destoy window or draw new game after press "OK" 
		return false;
	}
		break;
	case STARTPOINT:
	{
		mpCurBox.y = BOARDWIDTH - 2; //pacman stay on same line, but moving to the another side of this line,
		mpCurPoint.top = mpCurBox.y*BOXSIZE; //current coordinate in pixel
		mpCurPoint.left = mpCurBox.x*BOXSIZE;
		mpCurPoint.right = mpCurPoint.left + BOXSIZE;
		mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
		return true;
	}
		break;
	case EXITPOINT:
	{
		if (mCurTreasureCount == 0)
		{
			gamer = WINNER;
			GameStatus = false;
			//MessageBox(hWnd, (LPCTSTR)L"CONGRATULATION!! YOU ARE WINNER!", (LPCWSTR)L"Game over", MB_OK);
			//need destoy window or draw new game after press "OK" 
			return false;
		}
		else
		{
			mpCurBox.y = 1; //pacman stay on same line, but moving to the another side of this line,
			mpCurPoint.top = mpCurBox.y*BOXSIZE; //current coordinate in pixel
			mpCurPoint.left = mpCurBox.x*BOXSIZE;
			mpCurPoint.right = mpCurPoint.left + BOXSIZE;
			mpCurPoint.bottom = mpCurPoint.top + BOXSIZE;
			return true;
		}
	}
		break;
	default:
		break;
	}
	return false;
}
;
//void Turn(){}; //posible, function must take key-code

void ObjectPacman::SetNewDirection(Direction newDirect)
{
	mpCurDirection = newDirect;
};

