#include "stdafx.h"
#include "windowsx.h"
#include "Chess.h"
#include "Resources.h"
#include "Paint_Client.h"
#include "Process_Mouse_Click.h"
#include "Com_Wrapper.h"
#include "Tile.h"
#include "Chess_Piece.h"
#include "Chess_Piece_Type.h"
#include "Button.h"
#include "Scene.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 100

HWND Main_Window_Handle;
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
Com_Wrapper Com_Wrapper_Object; // Initialize the COM library.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void				Update_Positions();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CHESS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESS));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0)) // Message loop to dispatch system messages to the program. Messages are handled by WndProc.
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (Buttons != nullptr)
	{
		delete[] Buttons;
		Buttons = nullptr;
	}

	return static_cast<int>(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHESS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CHESS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	Main_Window_Handle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr); // Create the main window.

	if (!Main_Window_Handle)
	{
		return FALSE;
	}

	ShowWindow(Main_Window_Handle, 3);

	Create_Resources();
	Create_Tiles();
	Create_Chess_Piece_Types();
	Create_Chess_Pieces();

	Load_Scene(0);

	UpdateWindow(Main_Window_Handle);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Handles system messages.
{
	switch (message)
	{
	case WM_COMMAND:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_PAINT:
	{
		if (Main_Window_Handle != nullptr)
		{
			Paint_Client();
		}

		break;
	}
	case WM_SIZE:
	{
		if (Main_Window_Handle != nullptr)
		{
			Update_Positions();
		}

		break;
	}
	case WM_DISPLAYCHANGE:
	{
		if (Main_Window_Handle != nullptr)
		{
			Update_Positions();
		}

		break;
	}
	case WM_LBUTTONUP:
	{
		int X = GET_X_LPARAM(lParam);
		int Y = GET_Y_LPARAM(lParam);

		Process_Mouse_Click(X, Y);

		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}

	return 0;
}

void Update_Positions() // Updates positions of objects to keep their positions relative to the window.
{
	Create_Resources();
	Update_Tile_Positions();
	Update_Chess_Piece_Images();

	InvalidateRect(Main_Window_Handle, nullptr, FALSE); // Request the window to be re-rendered.
}