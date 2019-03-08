#include "stdafx.h"
#include "Button.h"
#include "Tile.h"
#include "Chess.h"
#include "Game.h"
#include "time.h"

int Scene{ 0 };

void Load_Scene(int ID)
{
	Delete_All_Buttons();

	Scene = ID;

	if (Scene != 0)
	{
		Initialise_Game();
		Create_Button(0, const_cast<wchar_t*>(L"Main Menu"), static_cast<int>(Tiles[0].This_Tile.left) - 355, static_cast<int>(Tiles[0].This_Tile.top) - 1); // Create Main Menu button.

		if (Scene == 1)
		{
			srand(static_cast<int>(time(nullptr))); // Initialise random number generator for computer to make random moves.
		}
	}
	else
	{
		RECT Client_Rect;
		GetClientRect(Main_Window_Handle, &Client_Rect);

		Create_Button(1, const_cast<wchar_t*>(L"Play Computer"), (Client_Rect.right / 2) - 100, (Client_Rect.bottom / 2) - 55); // Create Play Computer button.
		Create_Dynamically_Positioned_Button(2, const_cast<wchar_t*>(L"Play Local")); // Create Play Local button and automatically position it relative to Play Computer button.
	}
}