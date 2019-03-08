#include "stdafx.h"
#include "Process_Mouse_Click.h"
#include "Chess.h"
#include "Tile.h"
#include "Chess_Piece.h"
#include "Team.h"
#include "Chess_Piece_Type.h"
#include "Button.h"
#include "Engine.h"
#include "Scene.h"
#include "Game.h"

void Process_Mouse_Click(int X, int Y)
{
	if (Scene != 0) // If not on main menu.
	{
		if (X <= Tiles[63].This_Tile.right && X >= Tiles[0].This_Tile.left && Y <= Tiles[63].This_Tile.bottom && Y >= Tiles[0].This_Tile.top) // If the chess board was clicked.
		{
			Process_Action(X, Y);
		}
		else if (Tile_Clicked != nullptr) // Unselect chess piece.
		{
			Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
			Tile_Clicked = nullptr;
		}
	}

	for (int Count{ 0 }; Count < Size_Of_Button_Array; Count++) // Check if any buttons were pressed.
	{
		if (X >= Buttons[Count].X && X <= Buttons[Count].X + Buttons[Count].Width && Y >= Buttons[Count].Y && Y <= Buttons[Count].Y + Buttons[Count].Height)
		{
			Buttons[Count].Process_Button_Click();

			break;
		}
	}

	InvalidateRect(Main_Window_Handle, nullptr, FALSE);

	if (Display_Win_Lose_Message || Display_Draw_Message)
	{
		// Display game finished message to player.

		wchar_t* Message_Text{ nullptr };

		if (Display_Win_Lose_Message)
		{
			if (Scene == 1)
			{
				if (Team_Turn == 0)
				{
					Message_Text = const_cast<wchar_t*>(L"You Win!");
				}
			}
			else
			{
				if (Team_Turn == 0)
				{
					Message_Text = const_cast<wchar_t*>(L"White Wins!");
				}
				else
				{
					Message_Text = const_cast<wchar_t*>(L"Black Wins!");
				}
			}
		}
		else
		{
			Message_Text = const_cast<wchar_t*>(L"Draw!");
		}

		MessageBox(Main_Window_Handle, Message_Text, Message_Text, MB_OK | MB_ICONINFORMATION);

		Display_Win_Lose_Message = false;
		Display_Draw_Message = false;
	}
}