#include "stdafx.h"
#include "Board.h"
#include "ObjectPacman.h"

Board::Board()
{//initialize start board

	//Create dynamic array 
	mpBoardObjects = new Objects *[BOARDHEIGHT]; //column
	for (int i = 0; i < BOARDHEIGHT; ++i)
		mpBoardObjects[i] = new Objects[BOARDWIDTH]; //
	
	//initialize start map
	Point startPacmanPosition{ 0,0 };
	Point startGoust1Position{ 0,0 };
	Point startGoust2Position{ 0,0 };
	InitStartBoard(startPacmanPosition, startGoust1Position, startGoust2Position);
	
	//create pacman and chosts
	pacman.StartInitialize(startPacmanPosition);
	ghost1.StartInitialize(startGoust1Position);
	ghost2.StartInitialize(startGoust2Position);
};

void Board::InitStartBoard(Point &startPacmanPosition, Point &startGhost1Position, Point &startGhost2POsition)
{
	//location objects on board does not fall under the logic of the loop, creating map "manualy"
	//line by line

	//first line in wall
	for (int j = 0; BOARDHEIGHT; ++j)
		mpBoardObjects[0][j] = WALL; 

	//second line
	mpBoardObjects[1][0] = WALL;
	for (int j = 1; j < 9; ++j)
		mpBoardObjects[1][j] = TREASURE;
	mpBoardObjects[1][9] = WALL;
	for (int j = 10; j < BOARDWIDTH - 1;++j)
		mpBoardObjects[1][j] = TREASURE;
	mpBoardObjects[1][BOARDHEIGHT - 1] = WALL;

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
				startGhost1Position = { 7,j };
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
				startPacmanPosition={ 15,j };
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
	}

	delete[] mpBoardObjects;
};

	//void NewLevelGenerate() {}; //method for generate new labirint on board in future. Now method body is empty
void Draw(HDC &hDC, HWND &hWnd)
{
	HDC hdc = hDC;

};
	//void SetPacman(Point NewBoxPoint) {/*todo*/}; //set new pacman location
	//void SetGhost(int GoustNumber, Point NewBoxPoint) {/*TODO*/}; //set new ghost position

	//Objects GetCurObject(Point CheckBoxPoint) {/*TODO*/}; //get object in the specified position
	
void Board::DrawWall(HDC &hDC, HWND &hWnd, Point CurBoxPosition)
{
	HDC hdc = hDC;
	HBRUSH hBr;
	HBRUSH hOldBr;
	hBr = CreateSolidBrush(YELLOW);
	hOldBr = (HBRUSH)SelectObject(hdc, hBr);

	int x = CurBoxPosition.x*BOXSIZE, y = CurBoxPosition.y*BOXSIZE;
	Rectangle(hdc, x, y, x + BOXSIZE, y + BOXSIZE);

	SelectObject(hdc, hOldBr);
	DeleteObject(hOldBr);
	ReleaseDC(hWnd, hdc);

};
	//void DrawWinner() {}; //draw winner-screen with congratulation
	//void DrawLoser() {}; //draw loser-screen with "Game over"