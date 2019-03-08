#include "stdafx.h"
#include "Game.h"
#include "Chess_Piece.h"
#include "Tile.h"
#include "Team.h"
#include "Engine.h"

void Initialise_Game()
{
	// Reset all variables to start a fresh game.

	int Index_Modifer;

	for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 32; Chess_Piece_Count++)
	{
		Chess_Pieces[Chess_Piece_Count].Check = false;
		Chess_Pieces[Chess_Piece_Count].Captured = false;
		Chess_Pieces[Chess_Piece_Count].First_Move = true;

		if (Chess_Piece_Count < 16)
		{
			Index_Modifer = 0;
			Chess_Pieces[Chess_Piece_Count].Team = 0;

		}
		else
		{
			Index_Modifer = 32;
			Chess_Pieces[Chess_Piece_Count].Team = 1;
		}

		Chess_Pieces[Chess_Piece_Count].This_Tile = &Tiles[Chess_Piece_Count + Index_Modifer];
	}

	for (int Captured_Chess_Piece_Count{ 0 }; Captured_Chess_Piece_Count < 32; Captured_Chess_Piece_Count++)
	{
		Captured_Chess_Pieces[Captured_Chess_Piece_Count] = nullptr;
	}

	int Tile_Count{ 0 };

	for (int Vertical_Tile_Count = 0; Vertical_Tile_Count < 8; Vertical_Tile_Count++)
	{
		for (int Horizontal_Tile_Count = 0; Horizontal_Tile_Count < 8; Horizontal_Tile_Count++)
		{
			if (Tile_Count < 16)
			{
				Tiles[Tile_Count].This_Chess_Piece = &Chess_Pieces[Tile_Count];
			}
			else if (Tile_Count > 47)
			{
				Tiles[Tile_Count].This_Chess_Piece = &Chess_Pieces[Tile_Count - 32];
			}
			else
			{
				Tiles[Tile_Count].This_Chess_Piece = nullptr;
			}

			Tile_Count += 1;
		}
	}

	King_Tiles[0] = &Tiles[4];
	King_Tiles[1] = &Tiles[60];

	Team_Turn = 1;
	Game_Over = false;
}