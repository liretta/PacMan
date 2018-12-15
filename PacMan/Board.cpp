#include "stdafx.h"
#include "Board.h"
#include "ObjectPacman.h"
#include "cstdlib"
#include "ctime"


Board::Board()
{//initialize start board

	//Create dynamic array 
	mpBoardObjects = new Objects *[BOARDHEIGHT] {}; //column
	for (int i = 0; i < BOARDHEIGHT; ++i)
		mpBoardObjects[i] = new Objects[BOARDWIDTH]{}; //
	
	//initialize start map
	Point startPacmanPosition{ 0,0 };
	Point startGoust1Position{ 0,0 };
	Point startGoust2Position{ 0,0 };
	InitStartBoard(startPacmanPosition, startGoust1Position, startGoust2Position);
	
	//create pacman and chosts
	pacman.StartInitialize(startPacmanPosition);
	ghost1.StartInitialize(startGoust1Position);
	ghost2.StartInitialize(startGoust2Position);
	mpGameOn = true;
	mpGamerStatus = START;
};

void Board::InitStartBoard(Point &startPacmanPosition, Point &startGhost1Position, Point &startGhost2POsition)
{
	mCurTreasureCount = TREASURECOUNTSTART;
	//location objects on board does not fall under the logic of the loop, creating map "manualy"
	//line by line

	//first line in wall
	for (int j = 0; j<BOARDWIDTH; ++j)
		mpBoardObjects[0][j] = WALL; 

	//second line
	mpBoardObjects[1][0] = WALL;
	for (int j = 1; j < 9; ++j)
		mpBoardObjects[1][j] = TREASURE;
	mpBoardObjects[1][9] = WALL;
	for (int j = 10; j < BOARDWIDTH - 1;++j)
		mpBoardObjects[1][j] = TREASURE;
	mpBoardObjects[1][BOARDWIDTH - 1] = WALL;

	//third line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (1 == j || 4 == j || 8 == j || 10 == j || 14 == j || 17 == j)
			mpBoardObjects[2][j] = TREASURE;
		else
			mpBoardObjects[2][j] = WALL;
	}

	//FOURTH LINE
	mpBoardObjects[3][0] = WALL;
	for (int j = 1; j < BOARDWIDTH - 1; ++j)
		mpBoardObjects[3][j] = TREASURE;
	mpBoardObjects[3][BOARDWIDTH - 1] = WALL;

	//fifth line
	for (int j = 0; j < BOARDWIDTH;++j)
	{
		if (1 == j || 4 == j || 6 == j || 12 == j || 14 == j || 17 == j)
			mpBoardObjects[4][j] = TREASURE;
		else
			mpBoardObjects[4][j] = WALL;
	}

	//sixth line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (j == 0 || j == 5 || j == 9 || j == 13 || j == 18)
			mpBoardObjects[5][j] = WALL;
		else
			mpBoardObjects[5][j] = TREASURE;
	}

	//seventh line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (j == 4 || j == 14)
			mpBoardObjects[6][j] = TREASURE;
		else
			if (j == 8 || j == 10)
				mpBoardObjects[6][j] = EMPTY;
			else
				mpBoardObjects[6][j] = WALL;
	}

	//eighth line
	for (int j = 0; j < BOARDWIDTH;++j)
	{
		if (j == 3 || j == 5 || j == 13 || j == 15)
			mpBoardObjects[7][j] = WALL;
		else
			if (j == 9)
			{
				mpBoardObjects[7][j] = GHOST1;
				startGhost1Position = { j,7 };
			}
			else
				if (j == 4 || j == 14)
					mpBoardObjects[7][j] = TREASURE;
				else
					mpBoardObjects[7][j] = EMPTY;
	}

	//ninth line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (j == 4 || j == 14)
			mpBoardObjects[8][j] = TREASURE;
		else
			if (j == 6 || j == 12)
				mpBoardObjects[8][j] = EMPTY;
			else
				mpBoardObjects[8][j] = WALL;
	}

	//10 line
	mpBoardObjects[9][0] = STARTPOINT;
	for (int j = 1; j < 4; ++j)
		mpBoardObjects[9][j] = EMPTY;
	mpBoardObjects[9][4] = TREASURE;
	mpBoardObjects[9][5] = EMPTY;
	mpBoardObjects[9][6] = EMPTY;
	mpBoardObjects[9][7] = WALL;
	mpBoardObjects[9][8] = EMPTY;
	mpBoardObjects[9][9] = GHOST2;
	startGhost2POsition = { 9,9 };
	mpBoardObjects[9][10] = EMPTY;
	mpBoardObjects[9][11] = WALL;
	mpBoardObjects[9][12] = EMPTY;
	mpBoardObjects[9][13] = EMPTY;
	mpBoardObjects[9][14] = TREASURE;
	for (int j = 15; j < BOARDWIDTH - 2; ++j)
		mpBoardObjects[9][j] = EMPTY;
	mpBoardObjects[9][BOARDWIDTH - 1] = EXITPOINT;

	//11 line
	for (int j = 0; j < BOARDWIDTH;++j)
	{
		if (4 == j || 14 == j)
			mpBoardObjects[10][j] = TREASURE;
		else
			if (6 == j || 9 == j || 12 == j)
				mpBoardObjects[10][j] = EMPTY;
			else
				mpBoardObjects[10][j] = WALL;
	}

	//12 line
	for (int j = 0; j < BOARDWIDTH;++j)
	{
		if (3 == j || 5 == j || 13 == j || 15 == j)
			mpBoardObjects[11][j] = WALL;
		else
			if (4 == j || 14 == j)
				mpBoardObjects[11][j] = TREASURE;
			else
				mpBoardObjects[11][j] = EMPTY;
	}

	//13 line
	for (int j = 0; j < BOARDWIDTH;++j)
	{
		if (4 == j || 14 == j)
			mpBoardObjects[12][j] = TREASURE;
		else
			if (6 == j || 12 == j)
				mpBoardObjects[12][j] = EMPTY;
			else
				mpBoardObjects[12][j] = WALL;
	}

	//14 line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (0 == j || 9 == j || BOARDWIDTH - 1 == j)
			mpBoardObjects[13][j] = WALL;
		else
			mpBoardObjects[13][j] = TREASURE;
	}

	//15 line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (1 == j || 4 == j || 8 == j || 10 == j || 14 == j || 17 == j)
			mpBoardObjects[14][j] = TREASURE;
		else
			mpBoardObjects[14][j] = WALL;
	}

	//16 line
	for (int j = 0; j < BOARDWIDTH;++j)
	{
		if (0 == j || 3 == j || 15 == j || BOARDWIDTH - 1 == j)
			mpBoardObjects[15][j] = WALL;
		else
			if (9 == j)
			{
				mpBoardObjects[15][j] = PACMAN;
				startPacmanPosition={ j,15 };
			}
			else
				mpBoardObjects[15][j] = TREASURE;
	}

	//17 line
	for (int j = 0;j < BOARDWIDTH;++j)
	{
		if (2 == j || 4 == j || 6 == j || 12 == j || 14 == j || 16 == j)
			mpBoardObjects[16][j] = TREASURE;
		else
			mpBoardObjects[16][j] = WALL;
	}

	//18 line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (0 == j || 5 == j || 9 == j || 13 == j || BOARDWIDTH - 1 == j)
			mpBoardObjects[17][j] = WALL;
		else
			mpBoardObjects[17][j] = TREASURE;
	}

	//19 line
	for (int j = 0; j < BOARDWIDTH; ++j)
	{
		if (1 == j || 8 == j || 10 == j || 17 == j)
			mpBoardObjects[18][j] = TREASURE;
		else
			mpBoardObjects[18][j] = WALL;
	}

	//20 line
	mpBoardObjects[19][0] = WALL;
	for (int j = 1; j < BOARDWIDTH - 1;++j)
		mpBoardObjects[19][j] = TREASURE;
	mpBoardObjects[19][BOARDWIDTH - 1] = WALL;

	//last line
	for (int j = 0; j < BOARDWIDTH;++j)
		mpBoardObjects[20][j] = WALL;
}


Board::~Board() 
{
	if (mpBoardObjects != 0)
	{
		for (int i = 0; i < BOARDHEIGHT;++i)
			delete [] mpBoardObjects[i];

		delete[] mpBoardObjects;
	}
};

	//void NewLevelGenerate() {}; //method for generate new labirint on board in future. Now method body is empty
void Board::Draw(HDC hDC, HWND hWnd)
{
	HDC hdc = hDC;
	//TODO: check winner/lose
	//

	for(int i =0; i<BOARDHEIGHT; ++i)
		for (int j = 0; j < BOARDWIDTH; ++j)
		{
			switch (mpBoardObjects[i][j])
			{
			case WALL:
			{
				DrawWall(hdc, hWnd, { j, i });
			}
			break;
			case EMPTY:
				break;
			case PACMAN:
				pacman.Draw(hdc, hWnd);
				break;
			case GHOST1:
				ghost1.Draw(hdc, hWnd);
				break;
			case GHOST1TREASURE:
				ghost1.Draw(hdc, hWnd);
				break;
			case GHOST2:
				ghost2.Draw(hdc, hWnd);
				break;
			case GHOST2TREASURE:
				ghost2.Draw(hdc, hWnd);
				break;
			case TREASURE:
				DrawTreasure(hdc, hWnd, { j, i});
				break;
			case STARTPOINT:
				DrawStartPoint(hdc, hWnd, { j, i });
				break;
			case EXITPOINT:
				DrawExitPoint(hdc, hWnd, { j,i });
				break;
			default:
				break;
			}
		}

};

//pass result of checkCurObject to pacman's move-function
void Board::MovePacman(HWND hWnd)
{
	//check, what object there is in nex box on pacman's road
	Point CurPacman = pacman.GetCurBox();
	Direction CurDirect = pacman.GetCurDirection();

	//we didn't check situation, when CurDirection == 0 (start or exit point)
	//becouse pacman never been there: if next pacman position is start or end he can: finish game, move to start position+1 or exit-position-1
	//start and exit points are working like portal, not like a general box on board

	//found object in next pacman's box
	Point CheckNewBox{ 0,0 };
	switch (CurDirect)
	{
	case LEFT:
	{
		CheckNewBox.x = CurPacman.x-1;
		CheckNewBox.y = CurPacman.y;
	}
		break;
	case RIGHT:
	{
		CheckNewBox.x = CurPacman.x + 1;
		CheckNewBox.y = CurPacman.y;
	}
		break;
	case UP:
	{
		CheckNewBox.x = CurPacman.x;
		CheckNewBox.y = CurPacman.y-1;
	}
		break;
	case DOWN:
	{
		CheckNewBox.x = CurPacman.x;
		CheckNewBox.y = CurPacman.y+1;
	}
		break;
	default:
		break;
	}
	Objects NewObject = GetCurObject(CheckNewBox);
	//pass next object and it's box-coordinate to pacman-move-function

	if (pacman.Move(NewObject, CheckNewBox, mCurTreasureCount, mpGameOn, mpGamerStatus, hWnd)) ////change value in privios and new positions of pacman
	{//if in current position priviosly was treasure, retun in cur position value "treasure"
		//else in current position will be empty box
		mpBoardObjects[CurPacman.y][CurPacman.x] = EMPTY;

		if (NewObject == STARTPOINT || NewObject == EXITPOINT)
		{
			Point NewPacmanPoint = pacman.GetCurBox();
			mpBoardObjects[NewPacmanPoint.y][NewPacmanPoint.x] = PACMAN;
		}
		else
		{
			mpBoardObjects[CheckNewBox.y][CheckNewBox.x] = PACMAN;
		}
	}
	//UpdateWindow(hWnd);
};
	//void SetPacman(Point NewBoxPoint) {/*todo*/}; //set new pacman location
	//void SetGhost(int GoustNumber, Point NewBoxPoint) {/*TODO*/}; //set new ghost position

void Board::MoveGost1(HWND hWnd) //silly shost - always move in random direction
{
	//check, what object there is in nex box on pacman's road
	Point CurGhostBox = ghost1.GetCurBox();
	Direction CurDirect = ghost1.GetCurDirection();
	
	//we didn't check situation, when CurDirection == 0 (start or exit point)
	//becouse pacman never been there: if next pacman position is start or end he can: finish game, move to start position+1 or exit-position-1
	//start and exit points are working like portal, not like a general box on board

	//found object in next pacman's box
	Point CheckNewBox{ 0,0 };
	switch (CurDirect)
	{
	case LEFT:
	{
		CheckNewBox.x = CurGhostBox.x - 1;
		CheckNewBox.y = CurGhostBox.y;
	}
	break;
	case RIGHT:
	{
		CheckNewBox.x = CurGhostBox.x + 1;
		CheckNewBox.y = CurGhostBox.y;
	}
	break;
	case UP:
	{
		CheckNewBox.x = CurGhostBox.x;
		CheckNewBox.y = CurGhostBox.y - 1;
	}
	break;
	case DOWN:
	{
		CheckNewBox.x = CurGhostBox.x;
		CheckNewBox.y = CurGhostBox.y + 1;
	}
	break;
	default:
		break;
	}
	Objects NewObject = GetCurObject(CheckNewBox);
	//pass next object and it's box-coordinate to pacman-move-function

	if (ghost1.Move(NewObject, CheckNewBox, mpGameOn, mpGamerStatus, hWnd)) //change value in privios and in the new positions of ghost
	{
		//if in current position priviosly was treasure, retun in cur position value "treasure"
		//else in current position will be empty box
		mpBoardObjects[CurGhostBox.y][CurGhostBox.x] = (GetCurObject(CurGhostBox) == GHOST1TREASURE) ? TREASURE : EMPTY;
		
		if (NewObject == STARTPOINT || NewObject == EXITPOINT)
		{
			Point NewChostPoint = ghost1.GetCurBox();
			mpBoardObjects[NewChostPoint.y][NewChostPoint.x] = GHOST1;
		}
		else
		{
			mpBoardObjects[CheckNewBox.y][CheckNewBox.x] = NewObject == TREASURE ? GHOST1TREASURE : GHOST1;
		}

		//new box:
		//if in new box treasure - newBox value will be treasure+chost
		//else - new box value will be just ghost
		//mpBoardObjects[CheckNewBox.y][CheckNewBox.x] = NewObject == TREASURE ? GHOST1TREASURE : GHOST1;
	}
	else
	{
		//ghost1 is a silly ghost - he always move in random direction
		//so, if he can move in current direction, we need to change direction in to random one
		//and ghost can't move back
		Direction newDirection = CurDirect;
		while (newDirection == CurDirect)
		{
			newDirection = static_cast<Direction>(rand() % 4);
			ghost1.SetNewDirection(newDirection);
		}

		//Direction newDirection = static_cast<Direction>(rand() % 4);
		//ghost1.SetNewDirection(newDirection);
	}


};

void Board::MoveGost2(HWND hWnd) //angree ghost - trying to catch pacman
{
	//ATTENTION!! Now ghost2 also move in random direction
	//check, what object there is in nex box on pacman's road
	Point CurGhostBox = ghost2.GetCurBox();
	Direction CurDirect = ghost2.GetCurDirection();

	//we didn't check situation, when CurDirection == 0 (start or exit point)
	//becouse pacman never been there: if next pacman position is start or end he can: finish game, move to start position+1 or exit-position-1
	//start and exit points are working like portal, not like a general box on board

	//found object in next pacman's box
	Point CheckNewBox{ 0,0 };
	switch (CurDirect)
	{
	case LEFT:
	{
		CheckNewBox.x = CurGhostBox.x - 1;
		CheckNewBox.y = CurGhostBox.y;
	}
	break;
	case RIGHT:
	{
		CheckNewBox.x = CurGhostBox.x + 1;
		CheckNewBox.y = CurGhostBox.y;
	}
	break;
	case UP:
	{
		CheckNewBox.x = CurGhostBox.x;
		CheckNewBox.y = CurGhostBox.y - 1;
	}
	break;
	case DOWN:
	{
		CheckNewBox.x = CurGhostBox.x;
		CheckNewBox.y = CurGhostBox.y + 1;
	}
	break;
	default:
		break;
	}
	Objects NewObject = GetCurObject(CheckNewBox);
	//pass next object and it's box-coordinate to pacman-move-function

	if (ghost2.Move(NewObject, CheckNewBox, mpGameOn, mpGamerStatus, hWnd)) //change value in privios and in the new positions of ghost
	{
		//if in current position priviosly was treasure, retun in cur position value "treasure"
		//else in current position will be empty box
		mpBoardObjects[CurGhostBox.y][CurGhostBox.x] = (GetCurObject(CurGhostBox) == GHOST2TREASURE) ? TREASURE : EMPTY;

		if (NewObject == STARTPOINT || NewObject == EXITPOINT)
		{
			Point NewChostPoint = ghost2.GetCurBox();
			mpBoardObjects[NewChostPoint.y][NewChostPoint.x] = GHOST2;
		}
		else
		{
			mpBoardObjects[CheckNewBox.y][CheckNewBox.x] = NewObject == TREASURE ? GHOST2TREASURE : GHOST2;
		}

		//new box:
		//if in new box treasure - newBox value will be treasure+chost
		//else - new box value will be just ghost
	}
			//if we cant move - looking for new direction
		//TODO: !!!!here must be function for looking optimal way from ghost to pacman
		Direction newDirection = static_cast<Direction>(rand() % 4);
		ghost2.SetNewDirection(newDirection);
	
};

Objects Board::GetCurObject(Point CheckBoxPoint)
{
	int j = CheckBoxPoint.x, i = CheckBoxPoint.y;
	return mpBoardObjects[i][j];
}; //get object in the specified position
	
void Board::DrawWall(HDC hDC, HWND hWnd, Point CurBoxPosition)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(BLUE);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x = CurBoxPosition.x*BOXSIZE, 
		y = CurBoxPosition.y*BOXSIZE,
		x2 = x + BOXSIZE,
		y2 = y + BOXSIZE;

	Rectangle(hdc, x, y, x2, y2);

	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
	//DeleteObject(hOldBr);
	//ReleaseDC(hWnd, hdc);

};

void Board::DrawTreasure(HDC hDC, HWND hWnd, Point CurBoxPosition)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(WHITE);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x = CurBoxPosition.x*BOXSIZE+BOXSIZE/2, y = CurBoxPosition.y*BOXSIZE+ BOXSIZE/2;
	Ellipse(hdc, x-5, y-5, x + 5, y + 5);

	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
	//DeleteObject(hOldBr);
	//ReleaseDC(hWnd, hdc);
};

void Board::DrawStartPoint(HDC hDC, HWND hWnd, Point CurBoxPosition)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(GREEN);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	HPEN hPen;
	HBRUSH hOldPen;
	hPen = CreatePen(PS_SOLID, 3, LIGHTGREEN);
	hOldPen = (HBRUSH)SelectObject(hdc, hPen);
	
	int x = CurBoxPosition.x*BOXSIZE, y = CurBoxPosition.y*BOXSIZE;
	Rectangle(hdc, x, y, x + BOXSIZE, y + BOXSIZE);

	SelectObject(hdc, hOldBr);
	SelectObject(hdc, hOldPen);
	DeleteObject(hBr);
	DeleteObject(hPen);

	//ReleaseDC(hWnd, hdc);
};

void Board::DrawExitPoint(HDC hDC, HWND hWnd, Point CurBoxPosition)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(GREEN);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	HPEN hPen;
	HBRUSH hOldPen;
	hPen = CreatePen(PS_SOLID, 3, LIGHTGREEN);
	hOldPen = (HBRUSH)SelectObject(hdc, hPen);

	int x = CurBoxPosition.x*BOXSIZE, y = CurBoxPosition.y*BOXSIZE;
	Rectangle(hdc, x, y, x + BOXSIZE, y + BOXSIZE);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
		
	//arrow
	hPen = CreatePen(PS_SOLID, 3, WHITE);
	hOldPen = (HBRUSH)SelectObject(hdc, hPen);
	hBr = CreateSolidBrush(LIGHTGREEN);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x1, x2, x3, x4, x5, x6, x7;
	int y1, y2, y3, y4, y5, y6, y7;
	x1 = x;	 y1 = y + BOXSIZE / 4 + BOXSIZE / 8;
	x2 = x + BOXSIZE / 4 * 2;	y2 = y1;
	x3 = x2;  y3 = y + BOXSIZE / 4;
	x4 = x + BOXSIZE / 4 * 3;	y4 = y + BOXSIZE / 4 * 2;
	x5 = x2;	y5 = y + BOXSIZE / 4 * 3;
	x6 = x5;	y6 = y5 - BOXSIZE / 8;
	x7 = x;		y7 = y6;
	POINT poly[7] = { { x1, y1 },{ x2,y2 },{ x3,y3 },{ x4,y4 },{ x5, y5 },{ x6,y6 },{ x7, y7 } };
	Polygon(hdc, poly, 7);

	SelectObject(hdc, hOldBr);
	SelectObject(hdc, hOldPen);
	DeleteObject(hBr);
	DeleteObject(hPen);
	
	//ReleaseDC(hWnd, hdc);
};


void Board::DrawFinal(HDC hDC, HWND hWnd)
{
	if (mpGamerStatus == WINNER)
		DrawWinner(hDC, hWnd);
	else
		if (mpGamerStatus == LOSER)
			DrawLoser(hDC, hWnd);
		else
			DrawStart(hDC, hWnd);
};
//draw winner screan with congratulation, if player win
//now it is just message-box
void Board::DrawWinner(HDC hDC, HWND hWnd)
{
	MessageBox(hWnd, (LPCTSTR)L"CONGRATULATION!! YOU ARE WINNER", (LPCWSTR)L"Game over", MB_OK);
	//need destoy window or draw new game after press "OK"
}; 


//draw loser-screen with "Game over", if player lose
void Board::DrawLoser(HDC hDC, HWND hWnd)
{
	MessageBox(hWnd, (LPCTSTR)L"OH, NO! YOU ARE DIED :( ", (LPCWSTR)L"Game over", MB_OK);
	//need destoy window or draw new game after press "OK"
}; 

void Board::DrawStart(HDC hDc, HWND hWnd)
{
	MessageBox(hWnd, (LPCTSTR)L"Start screen ", (LPCWSTR)L"Start screen", MB_OK);
};

void Board::SetPacmanDirections(Direction NewDirect)
{
	pacman.SetNewDirection(NewDirect);
};



bool Board::IsGameOn() { return mpGameOn;  };

void Board::Move(HWND hWnd)
{
	MoveGost1(hWnd);
	MoveGost2(hWnd);
	MovePacman(hWnd);
	//MoveGhost1(hWnd);
	//MoveGhost2(hWnd);
	
}