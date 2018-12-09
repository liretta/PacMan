#pragma once
#include "stdafx.h"
#include "Defines.h"
#include "ObjectPacman.h"
#include "Ghost.h"

class ObjectPacman;
class ObjectChost;

//TODO: make friends with classes Pacman and Chost
class Board
{
private:
	Objects **mpBoardObjects; 
	ObjectPacman pacman;
	ObjectGhost ghost1;
	ObjectGhost ghost2;
	//here will objects ghosts
	unsigned int mCurTreasureCount; // current quontity of treasure
	void InitStartBoard(Point &startPacmanPosition, Point &startGhost1Position, Point &startGhost2POsition);
	//pass to function empty variable for save box-position of pacman & chosts. It need to create object "Pacman" & Chost 
	void DrawWall(HDC &hDC, HWND &hWnd, Point CurBoxPosition); //draw wall on board
	void DrawWinner(HDC &hDC, HWND &hWnd) {}; //draw winner-screen with congratulation
	void DrawLoser(HDC &hDC, HWND &hWnd) {}; //draw loser-screen with "Game over"
	

public:
	Board();
	~Board();
	void NewLevelGenerate() {}; //method for generate new labirint on board in future. Now method body is empty
	void Draw(HDC &hDC, HWND &hWnd);
	void SetPacman(Point NewBoxPoint) {}; //set new pacman location
	void SetGhost(int GoustNumber, Point NewBoxPoint) {}; //set new ghost position
	Objects GetCurObject(Point CheckBoxPoint) {}; //get object in the specified position
};

