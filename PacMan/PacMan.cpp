// PacMan.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "IncludedFiles.h"
#include "Defines.h"
#include "PacMan.h"
#include <memory>
#include <vld.h>
#include "time.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PACMAN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PACMAN));

    MSG msg;
	std::srand((unsigned int)time(0));

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PACMAN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(BGCOLOR);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PACMAN);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, /*WS_OVERLAPPEDWINDOW,*/ WS_MAXIMIZEBOX && WS_MINIMIZEBOX,
	   CW_USEDEFAULT, CW_USEDEFAULT, WINDOWIDTH, WINDOWHEIGHT, nullptr, nullptr, hInstance, nullptr);
  
   //defolt window 
   //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static ObjectPacman testPacman;
	//testPacman.StartInitialize({ 9,15 });
	//static ObjectGhost testGhost;
	//testGhost.StartInitialize({ 200,200 });
	static Board testBoard;
	HDC hMemDC;
	HDC hCompDC;
	HBITMAP hCompBmp;

    switch (message)
    {
	case WM_CREATE:
	{
		SetTimer(hWnd, 77, 130, NULL); //for release change 200 to 100
		//here will be initialize static start board 
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_PLAY:
				testBoard.StartGame();
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
				break;
            }
        }
		break;
    case WM_PAINT:
        {

		   //test code - try to paint boxses, figures etc.
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			if (testBoard.IsGameOn())
			{
				RECT rect;
				GetClientRect(hWnd, &rect);
				hCompDC = CreateCompatibleDC(hdc);
				hCompBmp = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
				SelectObject(hCompDC, hCompBmp);

				testBoard.Draw(hCompDC, hWnd);
				BitBlt(hdc, 0, 0, WINDOWIDTH, WINDOWHEIGHT, hCompDC, 0, 0, SRCCOPY);


				/*RECT rect;
				GetClientRect(hWnd, &rect);
				
				hCompDC = CreateCompatibleDC(hdc);
				hCompBmp = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
				SelectObject(hCompDC, hCompBmp);
				HBRUSH hBr;
				HBRUSH hOldBr;
				hBr = CreateSolidBrush(BLUE);
				hOldBr = (HBRUSH)SelectObject(hCompDC, hBr);
				

				int x = 100,
					y = 100,
					x2 = x + BOXSIZE,
					y2 = y + BOXSIZE;

				Rectangle(hCompDC, x, y, x2, y2);
				BitBlt(hdc, 0, 0, WINDOWIDTH, WINDOWHEIGHT, hCompDC, 0, 0, SRCCOPY);
				SelectObject(hdc, hOldBr);
				DeleteObject(hBr);*/

				
			}
			else
				testBoard.DrawFinal(hdc, hWnd); 

			//end of test code

            EndPaint(hWnd, &ps);
			//ReleaseDC(hWnd, hdc);
        }
        break;
	case WM_TIMER:
		if (LOWORD(wParam) == 77&&testBoard.IsGameOn())//maybe here must be checking, that board was creat? How? 
		{
			//TODO: change testBoard to release board
										
			testBoard.Move(hWnd);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_UP:
			testBoard.SetPacmanDirections(UP);
			break;
		case VK_DOWN:
			testBoard.SetPacmanDirections(DOWN);
				break;
		case VK_LEFT:
			testBoard.SetPacmanDirections(LEFT);
			break;
		case VK_RIGHT:
			testBoard.SetPacmanDirections(RIGHT);
			break;
		default:
			break;
		}
	}
		break;
	case WM_DESTROY:
		testBoard.~Board();
		//mem check
		//if (_CrtDumpMemoryLeaks())
		//MessageBox(hWnd, (LPCTSTR)L"MEMORY LEAKS!!", (LPCWSTR)L"Mem check", MB_OK);
		//else
		//MessageBox(hWnd, (LPCTSTR)L"MEMORY OK :-)", (LPCWSTR)L"Mem check", MB_OK);
		////KillTimer(hWnd, 77);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
