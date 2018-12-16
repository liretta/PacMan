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
	ObjectGhost ghost1; //ghost, who changed direction only if thay can't move 
	ObjectGhost ghost2; //silly ghost, always move in random direction
	unsigned int mCurTreasureCount; // current quontity of treasure
	bool mpGameOn;
	GamerStatus mpGamerStatus; 
	void InitStartBoard(Point &startPacmanPosition, Point &startGhost1Position, Point &startGhost2POsition);
	//pass to function empty variable for save box-position of pacman & chosts. It need to create object "Pacman" & Chost 
	void DrawWall(HDC hDC, Point CurBoxPosition); //draw wall on board
	void DrawEmpty(HDC hDC, Point CurBoxPosition); //draw wall on board
	void DrawTreasure(HDC hDC, Point CurBoxPosition); // draw treasure on board
	void DrawStartPoint(HDC hDC, Point CurBoxPosition); //draw start point
	void DrawExitPoint(HDC hDC, Point CurBoxPosition);
	void DrawWinner(HDC hDC, HWND hWnd); //draw winner-screen with congratulation
	void DrawLoser(HDC hDC, HWND hWnd); //draw loser-screen with "Game over"
	void DrawStart(HDC hDc, HWND hWnd);
	void MovePacman();//pass result of checkCurObject to pacman's move-function
	void MoveGhost1(); //we need two different function for different logic 1st & 2nd ghost
	void MoveGhost2(); //we need two different function for different logic 1st & 2nd ghost
	

public:
	Board();
	~Board();
	void StartGame();
	bool IsGameOn();
	void NewLevelGenerate(); //method for generate new labirint on board in future. Now method body equals StartBoardInit+Constructor
	void Draw(HDC hDC, HWND hWnd);
	void DrawFinal(HDC hDC, HWND hWnd);
	void SetPacman(Point NewBoxPoint) {}; //set new pacman location
	void SetPacmanDirections(Direction NewDirect); //set new pacman direction after key-pressed
	void SetGhost(int GoustNumber, Point NewBoxPoint) {}; //set new ghost position
	Objects GetCurObject(Point CheckBoxPoint); //get object in the specified position
	void Move();//MOVE ALL
};

