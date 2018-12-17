#include "stdafx.h"
#include "Board.h"
#include "ObjectPacman.h"
#include "cstdlib"
#include "ctime"

//   COMMENTS:
//
//        Game board is a table 19X20
//		  each box on the table has size BOXSIZE in pixel (look #define) 
//		  game board emplemented as two-demensional dynamic array
//		  Pay attention: in Array first demensional (i-loop) is COLUMNS on board, second demensional (j-loop) is LINES on board
//

//   FUNCTION: Board()
//
//   PURPOSE: create object "board"
//
//   COMMENTS:
//		Create dynamic array with values of each box on game board
//      called Start initialize function for board and game-objects: ghosts & pacman 
//		changed gameStatus in "START"
//
Board::Board()
{
	//Create dynamic array 
	mpBoardObjects = new Objects *[BOARDHEIGHT] {}; //column
	for (int i = 0; i < BOARDHEIGHT; ++i)
		mpBoardObjects[i] = new Objects[BOARDWIDTH]{}; //line
	
	//initialize start map
	Point startPacmanPosition{ 0,0 };
	Point startGoust1Position{ 0,0 };
	Point startGoust2Position{ 0,0 };
	InitStartBoard(startPacmanPosition, startGoust1Position, startGoust2Position);
	
	//initialize pacman and chosts
	pacman.StartInitialize(startPacmanPosition);
	ghost1.StartInitialize(startGoust1Position);
	ghost2.StartInitialize(startGoust2Position);
	mpGamerStatus = START;
};


Board::~Board()
{
	if (mpBoardObjects != nullptr)
	{
		for (int i = 0; i < BOARDHEIGHT;++i)
			delete[] mpBoardObjects[i];

		delete[] mpBoardObjects;
	}
	mpBoardObjects = nullptr;
};


// FUNCTION: InitStartBoard(Point &startPacmanPosition, Point &startGhost1Position, Point &startGhost2POsition)
//
//   PURPOSE: initialize map start level 
//
//   COMMENTS:
//		location objects on board does not fall under the logic of the loop, so creating map "manualy"
//		line by line		
//		
//
void Board::InitStartBoard(Point &startPacmanPosition, Point &startGhost1Position, Point &startGhost2POsition)
{
	mCurTreasureCount = TREASURECOUNTSTART;
	

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
	mpBoardObjects[9][9] = EMPTY;
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
		if (9 == j)
		{
			mpBoardObjects[11][j] = GHOST2;
			startGhost2POsition = { j,11 };
		}
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
				startPacmanPosition = { j,15 };
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


//   FUNCTION: NewLevelGenerate()
//
//   PURPOSE: initialize new map
//
//   COMMENTS:
//		pay attention! Now this function just initialize the same start board!
//		but in future we can use this function to initialize map for new level after finished firts one
//
void Board::NewLevelGenerate()
{
	Point startPacmanPosition{ 0,0 };
	Point startGoust1Position{ 0,0 };
	Point startGoust2Position{ 0,0 };
	InitStartBoard(startPacmanPosition, startGoust1Position, startGoust2Position);

	//initialize pacman and chosts
	pacman.StartInitialize(startPacmanPosition);
	ghost1.StartInitialize(startGoust1Position);
	ghost2.StartInitialize(startGoust2Position);
	mpGamerStatus = START;
	mpGameOn = false;

}

//   FUNCTION: StartGame()
//
//   PURPOSE: change game and gamer status to START
//
//   COMMENTS:
//		after finished first game and when player pess "PLAY" again, we use this funtion for changed all triggers to start position
//
void Board::StartGame()
{
	mpGameOn = true;
	mpGamerStatus = START;
}

// FUNCTION: Draw(HDC hDC)
//
//   PURPOSE: drawing all game object to the game board
//
//   COMMENTS:
//		pass through all elements of the array MpBoardObject
//		and callednessesary draw funtion by current objects
//		example, if current element on board-array is WALL, call Wall.Draw;
//
void Board::Draw(HDC hDC, HWND hWnd)
{
	HDC hdc = hDC;
	
	for(int i =0; i<BOARDHEIGHT; ++i)
		for (int j = 0; j < BOARDWIDTH; ++j)
		{
			switch (mpBoardObjects[i][j])
			{
			case WALL:
			{
				DrawWall(hdc, { j, i });
			}
			break;
			case EMPTY:
				DrawEmpty(hdc, { j,i });
				break;
			case PACMAN:
				pacman.Draw(hdc);
				break;
			case GHOST1:
				ghost1.Draw(hdc);
				break;
			case GHOST1TREASURE:
				ghost1.Draw(hdc);
				break;
			case GHOST2:
				ghost2.Draw(hdc);
				break;
			case GHOST2TREASURE:
				ghost2.Draw(hdc);
				break;
			case TREASURE:
				DrawTreasure(hdc, { j, i});
				break;
			case STARTPOINT:
				DrawStartPoint(hdc, { j, i });
				break;
			case EXITPOINT:
				DrawExitPoint(hdc, { j,i });
				break;
			default:
				break;
			}
		}
};


// FUNCTION: MovePacman(HWND hWnd)
//
//   PURPOSE: looking for next Pacman position, check object in next position and assigned new values to priviosli and next box
//
//   COMMENTS:
//		1.check, what object there is in next box on pacman's road.
//		we didn't check situation, when CurDirection == 0 (start or exit point)
//		becouse pacman never been there: if next pacman position is start or end he can: finish game, move to start position+1 or exit-position-1
//		start and exit points are working like portal, not like a general box on board
//		
//		2.pass result of checkCurObject to pacman's move-function
//		3.if funchion Move pacman retunt "true", we can move pacman and assign new value to elements on game board
//
//
void Board::MovePacman()
{
	//check, what object there is in nex box on pacman's road
	Point CurPacman = pacman.GetCurBox();
	Direction CurDirect = pacman.GetCurDirection();
	
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

	if (pacman.Move(NewObject, CheckNewBox, mCurTreasureCount, mpGameOn, mpGamerStatus)) //change value in privios and new positions of pacman
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
};
	

// FUNCTION: MoveGhost1(HWND hWnd)
//
//   PURPOSE: looking for next Ghost1 position, check object in next position and assigned new values to priviosli and next box
//
//   COMMENTS:
//		this ghost changed direction only if thay can't move on
//		1.check, what object there is in next box on chost's road.
//		we didn't check situation, when CurDirection == 0 (start or exit point)
//		becouse ghost never been there: if next ghost position is start or end he move to start position+1 or exit-position-1
//		start and exit points are working like portal, not like a general box on board
//		
//		2.pass result of checkCurObject to Ghosts move-function
//		3.if funchion Move ghost returned "true", we can move ghost and assign new value to elements on game board
//
void Board::MoveGhost1() 
{
	Point CurGhostBox = ghost1.GetCurBox();
	Direction CurDirect = ghost1.GetCurDirection();
	
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
	if (ghost1.Move(NewObject, CheckNewBox, mpGameOn, mpGamerStatus)) //change value in privios and in the new positions of ghost
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
	}
	else
	{
		//if he can move in current direction, we need to change direction in to random one
		Direction newDirection = CurDirect;
		while (newDirection == CurDirect)
		{
			newDirection = static_cast<Direction>(rand() % 4);
			
		}
		ghost1.SetNewDirection(newDirection);
	}
};


// FUNCTION: MoveGhost2(HWND hWnd)
//
//   PURPOSE: looking for next Ghost2 position, check object in next position and assigned new values to priviosli and next box
//
//   COMMENTS:
//		ATTENTION!! Now ghost2 also move as ghost 1. But we need two different function in future
//		if we needed angree ghost on nest lvl
//		1.check, what object there is in next box on chost's road.
//		we didn't check situation, when CurDirection == 0 (start or exit point)
//		becouse ghost never been there: if next ghost position is start or end he move to start position+1 or exit-position-1
//		start and exit points are working like portal, not like a general box on board
//		
//		2.pass result of checkCurObject to Ghosts move-function
//		3.if funchion Move ghost returned "true", we can move ghost and assign new value to elements on game board
//
void Board::MoveGhost2() 
{
	//check, what object there is in nex box on pacman's road
	Point CurGhostBox = ghost2.GetCurBox();
	Direction CurDirect = ghost2.GetCurDirection();

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

	if (ghost2.Move(NewObject, CheckNewBox, mpGameOn, mpGamerStatus)) //change value in privios and in the new positions of ghost
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
	}
	else
	{
	
		Direction newDirection = CurDirect;
		while (newDirection == CurDirect)
		{
			newDirection = static_cast<Direction>(rand() % 4);

		}
		ghost2.SetNewDirection(newDirection);
	}
};


// FUNCTION: GetCurObject(Point CheckBoxPoint)
//
//   PURPOSE: return object in the specified position
//
//   COMMENTS:
//		in board-array x position is COLUMN! So we return [y][x], not [x][y] element
//
Objects Board::GetCurObject (Point CheckBoxPoint) const
{
	return mpBoardObjects[CheckBoxPoint.y][CheckBoxPoint.x];
}; 
	
// FUNCTION: DrawWall(HDC hDC, Point CurBoxPosition)
//
//   PURPOSE: draw wall on game board
//
//   COMMENTS:
//		Wall - is blue box with defined size BOXSIZE 
//
void Board::DrawWall(HDC hDC, Point CurBoxPosition)
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
};


// FUNCTION: DrawTreasure(HDC hDC, Point CurBoxPosition)
//
//   PURPOSE: draw treasure on game board
//
//   COMMENTS:
//		Treasure - is simple white point in center of  BOXSIZE 
//
void Board::DrawTreasure(HDC hDC, Point CurBoxPosition)
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
};


// FUNCTION: DrawEmpty(HDC hDC, Point CurBoxPosition)
//
//   PURPOSE: draw empry box on game board
//
//   COMMENTS:
//		empty box - is black rectangle with BOXSIZE 
//
void Board::DrawEmpty(HDC hDC, Point CurBoxPosition)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(BLACK);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x = CurBoxPosition.x*BOXSIZE,
		y = CurBoxPosition.y*BOXSIZE,
		x2 = x + BOXSIZE,
		y2 = y + BOXSIZE;

	Rectangle(hdc, x, y, x2, y2);

	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
};


// FUNCTION: DrawStartPoint(HDC hDC, Point CurBoxPosition)
//
//   PURPOSE: draw StartPoint on game board
//
//   COMMENTS:
//		StartPoint - is green rectangle with constant size - BOXSIZE 
//
void Board::DrawStartPoint(HDC hDC, Point CurBoxPosition)
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
};


// FUNCTION: DrawExitPoint(HDC hDC, Point CurBoxPosition)
//
//   PURPOSE: draw ExitPoint on game board
//
//   COMMENTS:
//		ExitPoint - is green rectangle with white arrow in center and with constant size - BOXSIZE 
//
void Board::DrawExitPoint(HDC hDC, Point CurBoxPosition)
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
};


// FUNCTION: DrawFinal(HDC hDC, HWND hWnd)
//
//   PURPOSE: draw final message
//
//   COMMENTS:
//		if game not started, will be called function for draw start-screen
//		if game is over, will be displayed MessageBox with congratulate or loser-screen
//
void Board::DrawFinal(HDC hDC, HWND hWnd)
{
	
	if (mpGamerStatus == WINNER)
	{
		DrawWinner(hDC, hWnd);
	}
	else
		if (mpGamerStatus == LOSER)
		{
			DrawLoser(hDC, hWnd);
		}
		else 
			DrawStart(hDC, hWnd);
};


// FUNCTION: DrawWinner(HDC hDC, HWND hWnd)
//
//   PURPOSE: displayed winner message and generate new level board
//
void Board::DrawWinner(HDC hDC, HWND hWnd)
{
	MessageBox(hWnd, (LPCTSTR)L"CONGRATULATION!! YOU ARE WINNER", (LPCWSTR)L"Game over", MB_OK);
	NewLevelGenerate();
	DrawStart(hDC, hWnd);
}; 


// FUNCTION: DrawLoser(HDC hDC, HWND hWnd)
//
//   PURPOSE: displayed loser screen and generate new level board
//
void Board::DrawLoser(HDC hDC, HWND hWnd)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(YELLOW);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	//draw word "YOU LOSE"
	//"Y"
	///////////////////////////////////////////
	int x = 3 * BOXSIZE, y = 3 * BOXSIZE,
		x2 = x + BOXSIZE,
		y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 5 * BOXSIZE; y = 3 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 4 * BOXSIZE; y = 5 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		y += BOXSIZE;
		y2 = y + BOXSIZE;
		Rectangle(hdc, x, y, x2, y2);
	}

	//"O"
	///////////////////////////////////////////
	x = 8 * BOXSIZE; y = 3 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 8 * BOXSIZE; y = 8 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x =  7* BOXSIZE; y = 4 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 4; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 9 * BOXSIZE; y = 4 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 4; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}


	//"U"
	///////////////////////////////////////////
	x = 11 * BOXSIZE; y = 3 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 5; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 13 * BOXSIZE; y = 3 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 5; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 12 * BOXSIZE; y = 8 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);


	//"L"
	///////////////////////////////////////////
	x = 2 * BOXSIZE; y = 11 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 5; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 3 * BOXSIZE; y = 15 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 4 * BOXSIZE; y = 15 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	//"O"
	///////////////////////////////////////////
	x = 7 * BOXSIZE; y = 11 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 7 * BOXSIZE; y = 15 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 6 * BOXSIZE; y = 12 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 8 * BOXSIZE; y = 12 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	//"S"
	///////////////////////////////////////////
	x = 10 * BOXSIZE; y = 11 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		x += BOXSIZE;
		x2 = x + BOXSIZE;
	}

	x = 10 * BOXSIZE; y = 15 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		x += BOXSIZE;
		x2 = x + BOXSIZE;
	}

	x = 10 * BOXSIZE; y = 12 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 11 * BOXSIZE; y = 13 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 12 * BOXSIZE; y = 14 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);
	
	//"E"
	///////////////////////////////////////////
	x = 15 * BOXSIZE; y = 11 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		x += BOXSIZE;
		x2 = x + BOXSIZE;
	}

	x = 15 * BOXSIZE; y = 12 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 15 * BOXSIZE; y = 13 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		x += BOXSIZE;
		x2 = x + BOXSIZE;
	}

	x = 15 * BOXSIZE; y = 14 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 15 * BOXSIZE; y = 15 * BOXSIZE;
	x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		x += BOXSIZE;
		x2 = x + BOXSIZE;
	}

	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
	
	NewLevelGenerate();	
}; 


// FUNCTION: DrawStart(HDC hDc, HWND hWnd)
//
//   PURPOSE: drawing start screen with casual letters "PACMAN"
//
void Board::DrawStart(HDC hDc, HWND hWnd)
{
	HDC hdc = hDc;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(YELLOW);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);
	
	//draw word "pacman"
	//"P"
	///////////////////////////////////////////
	int x = 1*BOXSIZE, y = 3*BOXSIZE,
		x2 = x + BOXSIZE,
		y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	for (int i = 4; i < 10; ++i)
	{
		y += BOXSIZE;
		y2 = y + BOXSIZE;
		Rectangle(hdc, x, y, x2, y2);
		
	}
	x += BOXSIZE;
	y = 3*BOXSIZE;
	x2 = x + BOXSIZE;
	y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);
	Rectangle(hdc, x2, y, x2+BOXSIZE, y2);
	x = 3 * BOXSIZE; y = 4 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);
	x = 3 * BOXSIZE; y = 5 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);
	x = 2 * BOXSIZE; y = 5 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	//"A"
	///////////////////////////////////////
	x = 4 * BOXSIZE; y = 4 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 4; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}
	
	x = 5 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 6 * BOXSIZE; y = 4 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 4; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}
	x = 5 * BOXSIZE; y = 6 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	//"C"
	//////////////////////////////////////
	x = 7 * BOXSIZE; y = 4 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 4; i < 9; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}
	x = 8 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);
	x = 8 * BOXSIZE; y = 9 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);
	x = 9 * BOXSIZE; y = 4 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);
	x = 9 * BOXSIZE; y = 8 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	//"M"
	/////////////////////////////
	x = 10 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 3; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 12 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 3; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 11 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 3; i < 6; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}
	//poligon - for M 
	int x1 = 10*BOXSIZE;
	int y1 = 3*BOXSIZE;
	x2 = 13*BOXSIZE;
	y2 = 3*BOXSIZE;
	int x3 = 11 * BOXSIZE + BOXSIZE / 2;
	int y3 = 6 * BOXSIZE;
	
	POINT poly[3] = { { x1, y1 },{ x2,y2 },{ x3,y3 } };
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	hBr = CreateSolidBrush(BLACK);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);
	Polygon(hdc, poly, 3);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	hBr = CreateSolidBrush(YELLOW);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	//"A"
	///////////////////////////////////////
	x = 13 * BOXSIZE; y = 4 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 4; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 14 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	x = 15 * BOXSIZE; y = 4 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 4; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}
	x = 14 * BOXSIZE; y = 6 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	Rectangle(hdc, x, y, x2, y2);

	//"N"
	//////////////////////
	x = 16 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 3; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 17 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 3; i < 9; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}

	x = 18 * BOXSIZE; y = 3 * BOXSIZE; x2 = x + BOXSIZE; y2 = y + BOXSIZE;
	for (int i = 3; i < 10; ++i)
	{
		Rectangle(hdc, x, y, x2, y2);
		y += BOXSIZE;
		y2 = y + BOXSIZE;
	}
	
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);

	hBr = CreateSolidBrush(BLACK);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	//poligon - for N 
	x1 = 16 * BOXSIZE+BOXSIZE/2;
	y1 = 3 * BOXSIZE;
	x2 = 18 * BOXSIZE+BOXSIZE/2;
	y2 = 9 * BOXSIZE;
	x3 = x2;// *BOXSIZE + BOXSIZE / 2;
	y3 = y1;// * BOXSIZE;

	POINT poly2[3] = { { x1, y1 },{ x2,y2 },{ x3,y3 } };
	Polygon(hdc, poly2, 3);

	//second poligon - for N 
	x1 = 16 * BOXSIZE + BOXSIZE / 2;
	y1 = 3 * BOXSIZE+BOXSIZE/2;
	x2 = 18 * BOXSIZE + BOXSIZE / 2;
	y2 = 9 * BOXSIZE+BOXSIZE;
	x3 = x1;// *BOXSIZE + BOXSIZE / 2;
	y3 = y2;// * BOXSIZE;

	POINT poly3[3] = { { x1, y1 },{ x2,y2 },{ x3,y3 } };
	Polygon(hdc, poly3, 3);
	SelectObject(hdc, hOldBr);
	DeleteObject(hBr);
};


// FUNCTION: SetPacmanDirections(Direction NewDirect)
//
//   PURPOSE: called funtion SetNweDirection from Pacman object
//
void Board::SetPacmanDirections(Direction NewDirect)
{
	pacman.SetNewDirection(NewDirect);
};


bool Board::IsGameOn() const { return mpGameOn;  };

// FUNCTION: Move()
//
//   PURPOSE: called all move-function for pacman and ghosts
//
void Board::Move()
{
	MovePacman();
	MoveGhost1();
	MoveGhost2();
}