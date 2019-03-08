#include "stdafx.h"
#include "Tile.h"
#include "Team.h"
#include "Chess_Piece.h"
#include "Chess.h"
#include "Computer.h"
#include "Scene.h"
#include "Chess_Piece_Type.h"
#include "Engine.h"
#include "Game.h"

Tile *Tile_Clicked;
bool Game_Over{ false };
bool Display_Win_Lose_Message{ false };
bool Display_Draw_Message{ false };

void Process_Action(int X, int Y)
{
	if (Scene == 1) // Play Computer
	{
		// Calculate which tile was clicked.

		int Horizontal_Tile;
		int Vertical_Tile;
		float Tile_Float{ (static_cast<float>(X) - Tiles[0].This_Tile.left) / 90.0F };
		int Tile_Int{ (X - static_cast<int>(Tiles[0].This_Tile.left)) / 90 };

		if (Tile_Float > Tile_Int)
		{
			Horizontal_Tile = Tile_Int + 1;
		}
		else
		{
			Horizontal_Tile = Tile_Int;
		}

		Tile_Float = (static_cast<float>(Y) - Tiles[0].This_Tile.top) / 90.0F;
		Tile_Int = (Y - static_cast<int>(Tiles[0].This_Tile.top)) / 90;

		if (Tile_Float > Tile_Int)
		{
			Vertical_Tile = Tile_Int + 1;
		}
		else
		{
			Vertical_Tile = Tile_Int;
		}

		Tile *New_Tile_Clicked{ &Tiles[(((Vertical_Tile - 1) * 8) + Horizontal_Tile) - 1] };

		if (Tile_Clicked == nullptr)
		{
			if (New_Tile_Clicked->This_Chess_Piece != nullptr)
			{
				if (New_Tile_Clicked->This_Chess_Piece->Team == 1) // Select a chess piece.
				{
					Tile_Clicked = New_Tile_Clicked;
					Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(true);
				}
			}
		}
		else
		{
			if (New_Tile_Clicked->Available_Move) // Move the chess piece.
			{
				Tile_Clicked->This_Chess_Piece->Move_Chess_Piece(New_Tile_Clicked);
				Tile_Clicked = nullptr;

				if (Team_Turn == 0)
				{
					Team_Turn = 1;
				}
				else
				{
					Team_Turn = 0;

					Make_Move(); // Let the computer make a random move.
				}
			}
			else
			{
				if (New_Tile_Clicked->This_Chess_Piece != nullptr)
				{
					if (New_Tile_Clicked == Tile_Clicked) // Unselect chess piece.
					{
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
						Tile_Clicked = nullptr;
					}
					else  if (New_Tile_Clicked->This_Chess_Piece->Team == Team_Turn) // Change selected chess piece.
					{
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
						Tile_Clicked = New_Tile_Clicked;
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(true);
					}
					else // Unselect chess piece.
					{
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
						Tile_Clicked = nullptr;
					}
				}
				else // Unselect chess piece.
				{
					Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
					Tile_Clicked = nullptr;
				}
			}
		}
	}
	else if (Scene == 2) // Play Local.
	{
		// Calculate which tile was clicked.

		int Horizontal_Tile;
		int Vertical_Tile;
		float Tile_Float{ (static_cast<float>(X) - Tiles[0].This_Tile.left) / 90.0F };
		int Tile_Int{ (X - static_cast<int>(Tiles[0].This_Tile.left)) / 90 };

		if (Tile_Float > Tile_Int)
		{
			Horizontal_Tile = Tile_Int + 1;
		}
		else
		{
			Horizontal_Tile = Tile_Int;
		}

		Tile_Float = (static_cast<float>(Y) - Tiles[0].This_Tile.top) / 90.0F;
		Tile_Int = (Y - static_cast<int>(Tiles[0].This_Tile.top)) / 90;

		if (Tile_Float > Tile_Int)
		{
			Vertical_Tile = Tile_Int + 1;
		}
		else
		{
			Vertical_Tile = Tile_Int;
		}

		Tile *New_Tile_Clicked{ &Tiles[(((Vertical_Tile - 1) * 8) + Horizontal_Tile) - 1] };

		if (Tile_Clicked == nullptr)
		{
			if (New_Tile_Clicked->This_Chess_Piece != nullptr)
			{
				if (New_Tile_Clicked->This_Chess_Piece->Team == Team_Turn) // Select chess piece.
				{
					Tile_Clicked = New_Tile_Clicked;
					Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(true);
				}
			}
		}
		else
		{
			if (New_Tile_Clicked->Available_Move) // Move chess piece.
			{
				Tile_Clicked->This_Chess_Piece->Move_Chess_Piece(New_Tile_Clicked);
				Tile_Clicked = nullptr;

				if (Team_Turn == 0)
				{
					Team_Turn = 1;
				}
				else
				{
					Team_Turn = 0;
				}
			}
			else
			{
				if (New_Tile_Clicked->This_Chess_Piece != nullptr)
				{
					if (New_Tile_Clicked == Tile_Clicked) // Unselect chess piece.
					{
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
						Tile_Clicked = nullptr;
					}
					else  if (New_Tile_Clicked->This_Chess_Piece->Team == Team_Turn) // Change selected chess piece.
					{
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
						Tile_Clicked = New_Tile_Clicked;
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(true);
					}
					else // Unselect chess piece.
					{
						Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
						Tile_Clicked = nullptr;
					}
				}
				else // Unselect chess piece.
				{
					Tile_Clicked->This_Chess_Piece->Toggle_Available_Moves(false);
					Tile_Clicked = nullptr;
				}
			}
		}
	}
}

void Test_Check(int Team)
{
	bool Check{ false };

	int Index_Offset{ 16 };

	if (Team == 1)
	{
		Index_Offset = 0;
	}

	for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 16; Chess_Piece_Count++) // Test all possible moves for all chess pieces to see if the King is in check.
	{
		if (!(Chess_Pieces[Index_Offset + Chess_Piece_Count].Captured))
		{
			bool *Available_Moves{ Chess_Pieces[Index_Offset + Chess_Piece_Count].Get_Available_Moves() };

			for (int Tile_Count{ 0 }; Tile_Count < 64; Tile_Count++)
			{
				if (Tiles[Tile_Count].This_Chess_Piece != nullptr)
				{
					if (Tiles[Tile_Count].This_Chess_Piece->Type->ID == 5)
					{
						if (Available_Moves[Tile_Count])
						{
							Tiles[Tile_Count].This_Chess_Piece->Check = true;

							Check = true;

							break;
						}
					}
				}
			}

			delete[] Available_Moves;

			if (Check)
			{
				break;
			}
		}
	}

	if (!(Check))
	{
		King_Tiles[Team]->This_Chess_Piece->Check = false;
	}
}

void Test_Check()
{
	bool Check[2]{ false };

	for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 32; Chess_Piece_Count++) // Test all possible moves for all chess pieces to see if either of the Kings are in check.
	{
		if (!(Chess_Pieces[Chess_Piece_Count].Captured))
		{
			bool *Available_Moves{ Chess_Pieces[Chess_Piece_Count].Get_Available_Moves() };

			for (int Tile_Count{ 0 }; Tile_Count < 64; Tile_Count++)
			{
				if (Tiles[Tile_Count].This_Chess_Piece != nullptr)
				{
					if (Tiles[Tile_Count].This_Chess_Piece->Type->ID == 5)
					{
						if (Available_Moves[Tile_Count])
						{
							Tiles[Tile_Count].This_Chess_Piece->Check = true;
							Check[Tiles[Tile_Count].This_Chess_Piece->Team] = true;

							break;
						}
					}
				}
			}

			delete[] Available_Moves;

			if (Check[0] || Check[1])
			{
				break;
			}
		}
	}

	for (int King_Count{ 0 }; King_Count < 2; King_Count++)
	{
		if (!(Check[King_Count]))
		{
			King_Tiles[King_Count]->This_Chess_Piece->Check = false;
		}
		else
		{
			break;
		}
	}
}

void Test_Checkmate_And_Stalemate(int Team)
{
	if (King_Tiles[Team]->This_Chess_Piece->Check)
	{
		int Index_Offset{ 0 };
		bool Any_Available_Moves{ false };

		if (Team == 1)
		{
			Index_Offset = 16;
		}

		// Toggle all available moves on. If there aren't any, end game.

		for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 16; Chess_Piece_Count++)
		{
			if (!(Chess_Pieces[Chess_Piece_Count + Index_Offset].Captured))
			{
				Chess_Pieces[Chess_Piece_Count + Index_Offset].Toggle_Available_Moves(true);
			}
		}

		for (int Tile_Count{ 0 }; Tile_Count < 64; Tile_Count++)
		{
			if (Tiles[Tile_Count].Available_Move)
			{
				Any_Available_Moves = true;
				break;
			}
		}

		for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 16; Chess_Piece_Count++)
		{
			if (!(Chess_Pieces[Chess_Piece_Count + Index_Offset].Captured))
			{
				Chess_Pieces[Chess_Piece_Count + Index_Offset].Toggle_Available_Moves(false);
			}
		}

		if (!(Any_Available_Moves))
		{
			Game_Over = true;
			Display_Win_Lose_Message = true;
		}
	}
	else
	{
		Test_Stalemate(Team);
	}
}

void Test_Stalemate(int Team)
{
	int Index_Offset{ 0 };
	bool Any_Available_Moves{ false };

	if (Team == 1)
	{
		Index_Offset = 16;
	}

	// Toggle all available moves on. If there aren't any, end game.

	for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 16; Chess_Piece_Count++)
	{
		if (!(Chess_Pieces[Chess_Piece_Count + Index_Offset].Captured))
		{
			Chess_Pieces[Chess_Piece_Count + Index_Offset].Toggle_Available_Moves(true);
		}
	}

	for (int Tile_Count{ 0 }; Tile_Count < 64; Tile_Count++)
	{
		if (Tiles[Tile_Count].Available_Move)
		{
			Any_Available_Moves = true;
			break;
		}
	}

	for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 16; Chess_Piece_Count++)
	{
		if (!(Chess_Pieces[Chess_Piece_Count + Index_Offset].Captured))
		{
			Chess_Pieces[Chess_Piece_Count + Index_Offset].Toggle_Available_Moves(false);
		}
	}

	if (!(Any_Available_Moves))
	{
		Game_Over = true;
		Display_Draw_Message = true;
	}
}