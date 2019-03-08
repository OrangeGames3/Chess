#include "stdafx.h"
#include "Computer.h"
#include "Chess_Piece.h"
#include "Tile.h"
#include "Team.h"

void Add_Chess_Piece_To_Array(Chess_Piece**&, int&, int&);
void Add_Tile_Index_To_Array(int*&, int&, int&);

void Make_Move()
{
	Chess_Piece **Chess_Pieces_With_Available_Moves{ nullptr };
	int Size_Of_Array{ 0 };

	for (int Count{ 0 }; Count < 16; Count++) // Generate array containing all chess pieces that have available moves.
	{
		if (!(Chess_Pieces[Count].Captured))
		{
			bool Any_Available_Moves{ false };

			Chess_Pieces[Count].Toggle_Available_Moves(true, &Any_Available_Moves);

			if (Any_Available_Moves)
			{
				Add_Chess_Piece_To_Array(Chess_Pieces_With_Available_Moves, Size_Of_Array, Count);
			}

			Chess_Pieces[Count].Toggle_Available_Moves(false);
		}
	}

	if (Size_Of_Array > 0)
	{
		int Random_Chess_Piece{ 0 };

		if (Size_Of_Array > 1) // Choose a random chess piece.
		{
			Random_Chess_Piece = rand() % Size_Of_Array;
		}

		Chess_Pieces_With_Available_Moves[Random_Chess_Piece]->Toggle_Available_Moves(true);

		int Number_Of_Available_Moves{ 0 };
		int *Tile_Indexes{ nullptr };

		for (int Count{ 0 }; Count < 64; Count++)
		{
			if (Tiles[Count].Available_Move == true)
			{
				Add_Tile_Index_To_Array(Tile_Indexes, Number_Of_Available_Moves, Count);
			}
		}

		if (Number_Of_Available_Moves > 0)
		{
			int Random_Move{ rand() % Number_Of_Available_Moves };

			Chess_Pieces_With_Available_Moves[Random_Chess_Piece]->Move_Chess_Piece(&Tiles[Tile_Indexes[Random_Move]]); // Make a random move chosen from the random chess piece.

			Team_Turn = 1;
		}

		if (Tile_Indexes != nullptr)
		{
			delete[] Tile_Indexes;
		}
	}

	if (Chess_Pieces_With_Available_Moves != nullptr)
	{
		delete[] Chess_Pieces_With_Available_Moves;
	}
}

void Add_Chess_Piece_To_Array(Chess_Piece **&Chess_Pieces_With_Available_Moves, int &Size_Of_Array, int &Count)
{
	Chess_Piece **Chess_Pieces_With_Available_Moves_Buffer{ nullptr };

	if (Chess_Pieces_With_Available_Moves != nullptr)
	{
		Chess_Pieces_With_Available_Moves_Buffer = new Chess_Piece*[Size_Of_Array]; // Create buffer to store existing chess piece pointers.

		for (int Count2{ 0 }; Count2 < Size_Of_Array; Count2++) // Fill buffer.
		{
			Chess_Pieces_With_Available_Moves_Buffer[Count2] = Chess_Pieces_With_Available_Moves[Count2];
		}

		delete[] Chess_Pieces_With_Available_Moves;
	}

	Chess_Pieces_With_Available_Moves = new Chess_Piece*[Size_Of_Array + 1]; // Create new array with 1 extra index.
	Size_Of_Array += 1;

	if (Chess_Pieces_With_Available_Moves_Buffer != nullptr)
	{
		for (int Count3{ 0 }; Count3 < Size_Of_Array - 1; Count3++) // Fill new array with buffer.
		{
			Chess_Pieces_With_Available_Moves[Count3] = Chess_Pieces_With_Available_Moves_Buffer[Count3];
		}

		delete[] Chess_Pieces_With_Available_Moves_Buffer;
	}

	Chess_Pieces_With_Available_Moves[Size_Of_Array - 1] = &Chess_Pieces[Count]; // Add the new chess piece to the end of the array.
}

void Add_Tile_Index_To_Array(int *&Tile_Indexes, int &Size_Of_Array, int &Tile_Index)
{
	int *Tile_Indexes_Buffer{ nullptr };

	if (Tile_Indexes != nullptr)
	{
		Tile_Indexes_Buffer = new int[Size_Of_Array]; // Create buffer to store existing chess piece pointers.

		for (int Count2{ 0 }; Count2 < Size_Of_Array; Count2++) // Fill buffer.
		{
			Tile_Indexes_Buffer[Count2] = Tile_Indexes[Count2];
		}

		delete[] Tile_Indexes;
	}

	Tile_Indexes = new int[Size_Of_Array + 1]; // Create new array with 1 extra index.
	Size_Of_Array += 1;

	if (Tile_Indexes_Buffer != nullptr)
	{
		for (int Count3{ 0 }; Count3 < Size_Of_Array - 1; Count3++) // Fill new array with buffer.
		{
			Tile_Indexes[Count3] = Tile_Indexes_Buffer[Count3];
		}

		delete[] Tile_Indexes_Buffer;
	}

	Tile_Indexes[Size_Of_Array - 1] = Tile_Index; // Add the new chess piece to the end of the array.
}