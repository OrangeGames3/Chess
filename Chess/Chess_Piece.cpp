#include "stdafx.h"
#include "d2d1_1.h"
#include "Chess_Piece.h"
#include "Tile.h"
#include "Chess_Piece_Type.h"
#include "Team.h"
#include "Resources.h"
#include "Chess.h"
#include "Button.h"
#include "Engine.h"

Chess_Piece Chess_Pieces[32];
Chess_Piece *Captured_Chess_Pieces[32];

bool Loop_Condition(int, int);
void Loop_Increment(int&, int&);

void Create_Chess_Pieces()
{
	ID2D1Bitmap *Total_Chess_Piece_Images[]{ Chess_Piece_Images[5].This_Interface, Chess_Piece_Images[2].This_Interface, Chess_Piece_Images[0].This_Interface, Chess_Piece_Images[4].This_Interface, Chess_Piece_Images[1].This_Interface, Chess_Piece_Images[0].This_Interface, Chess_Piece_Images[2].This_Interface, Chess_Piece_Images[5].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface,Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[11].This_Interface, Chess_Piece_Images[7].This_Interface, Chess_Piece_Images[6].This_Interface, Chess_Piece_Images[10].This_Interface, Chess_Piece_Images[8].This_Interface, Chess_Piece_Images[6].This_Interface, Chess_Piece_Images[7].This_Interface, Chess_Piece_Images[11].This_Interface }; // Contains pointers to an image to be matched with each chess piece.

	for (int Chess_Piece_Count{ 0 }; Chess_Piece_Count < 32; Chess_Piece_Count++) // Initialise variables for all chess pieces.
	{
		Chess_Pieces[Chess_Piece_Count].Image = Total_Chess_Piece_Images[Chess_Piece_Count];
		Chess_Pieces[Chess_Piece_Count].ID = Chess_Piece_Count + 1;

		if (Chess_Piece_Count == 0 || Chess_Piece_Count == 7 || Chess_Piece_Count == 24 || Chess_Piece_Count == 31)
		{
			Chess_Pieces[Chess_Piece_Count].Type = &Chess_Piece_Types[0];
		}
		else if (Chess_Piece_Count == 1 || Chess_Piece_Count == 6 || Chess_Piece_Count == 25 || Chess_Piece_Count == 30)
		{
			Chess_Pieces[Chess_Piece_Count].Type = &Chess_Piece_Types[1];
		}
		else if (Chess_Piece_Count == 2 || Chess_Piece_Count == 5 || Chess_Piece_Count == 26 || Chess_Piece_Count == 29)
		{
			Chess_Pieces[Chess_Piece_Count].Type = &Chess_Piece_Types[2];
		}
		else if (Chess_Piece_Count == 3 || Chess_Piece_Count == 27)
		{
			Chess_Pieces[Chess_Piece_Count].Type = &Chess_Piece_Types[3];
		}
		else if (Chess_Piece_Count == 4 || Chess_Piece_Count == 28)
		{
			Chess_Pieces[Chess_Piece_Count].Type = &Chess_Piece_Types[4];
		}
		else
		{
			Chess_Pieces[Chess_Piece_Count].Type = &Chess_Piece_Types[5];
		}
	}
}

bool* Chess_Piece::Get_Available_Moves()
{
	int Loop_Range{ Type->Number_Of_Moves * 2 }; // Loop range is twice the number of moves to accommodate for both horizontal and vertical testing.
	int Capture_Loop_Range;
	int *Capture_Move_Offsets{ nullptr }; // Stores tile positions of possible moves relative to the chess piece's position.
	int *Move_Offsets{ new int[Loop_Range] }; // Stores tile positions of possible moves relative to the chess piece's position.
	bool *Available_Moves{ new bool[64]{ false } }; // Stores a true or false value for each tile, representing whether or not the tile is an available move for a chess piece.

	if (Team == 0)
	{
		for (int Count{ 0 }; Count < Loop_Range; Count++)
		{
			Move_Offsets[Count] = Type->Black_Move_Offsets[Count];
		}

	}
	else
	{
		for (int Count{ 0 }; Count < Loop_Range; Count++)
		{
			Move_Offsets[Count] = Type->White_Move_Offsets[Count];
		}
	}

	if (Type->Different_Capture_Moves)
	{
		Capture_Loop_Range = Type->Capture_Number_Of_Moves * 2; // Loop range is twice the number of moves to accommodate for both horizontal and vertical testing.
		Capture_Move_Offsets = new int[Capture_Loop_Range];

		if (Team == 0)
		{
			for (int Count{ 0 }; Count < Capture_Loop_Range; Count++)
			{
				Capture_Move_Offsets[Count] = Type->Black_Capture_Move_Offsets[Count];
			}
		}
		else
		{
			for (int Count{ 0 }; Count < Capture_Loop_Range; Count++)
			{
				Capture_Move_Offsets[Count] = Type->White_Capture_Move_Offsets[Count];
			}
		}
	}

	for (int Move_Offset_Count{ 0 }; Move_Offset_Count < Loop_Range; Move_Offset_Count = Move_Offset_Count + 2) // Loop to check the validity of each possible move for the chess piece. Increment by 2 because both the horizontal and vertical values for each move take 1 index each.
	{
		if (Type->Variable_Move_Distance || (Type->Variable_First_Move_Distance && First_Move)) // For Rook, Bishop, Queen and Pawn.
		{
			int Loop_Horizontal_Range{ Move_Offsets[Move_Offset_Count] };
			int Loop_Vertical_Range{ Move_Offsets[Move_Offset_Count + 1] };
			int Loop_Range_2;
			int Loop_Count;

			if (Loop_Horizontal_Range != 0)
			{
				Loop_Count = Loop_Horizontal_Range;
				Loop_Range_2 = Loop_Horizontal_Range * Type->Max_Variable_Move_Distance;
			}
			else
			{
				Loop_Count = Loop_Vertical_Range;
				Loop_Range_2 = Loop_Vertical_Range * Type->Max_Variable_Move_Distance;
			}

			for (Loop_Count; Loop_Condition(Loop_Count, Loop_Range_2); Loop_Increment(Loop_Count, Loop_Range_2)) // Loop through each move and increase the move distance each loop.
			{
				Move_Offsets[Move_Offset_Count] = Loop_Horizontal_Range;
				Move_Offsets[Move_Offset_Count + 1] = Loop_Vertical_Range;

				int Tile_Index = (This_Tile->ID - 1) + Move_Offsets[Move_Offset_Count] + (Move_Offsets[Move_Offset_Count + 1] * 8); // Calculate which tile the move offset refers to.

				// Calculate the horizontal tile.

				int Horizontal_Tile;
				int Vertical_Tile;
				int Chess_Piece_Horizontal_Tile;
				int Chess_Piece_Vertical_Tile;
				int Tile_Int;
				float Tile_Float;

				Tile_Int = (Tile_Index + 1) / 8;
				Tile_Float = (static_cast<float>(Tile_Index + 1)) / 8.0F;

				if (Tile_Float > Tile_Int)
				{
					Vertical_Tile = Tile_Int + 1;
				}
				else
				{
					Vertical_Tile = Tile_Int;
				}

				Horizontal_Tile = (Tile_Index + 1) - ((Vertical_Tile - 1) * 8);

				Tile_Int = This_Tile->ID / 8;
				Tile_Float = static_cast<float>(This_Tile->ID) / 8.0F;

				if (Tile_Float > Tile_Int)
				{
					Chess_Piece_Vertical_Tile = Tile_Int + 1;
				}
				else
				{
					Chess_Piece_Vertical_Tile = Tile_Int;
				}

				Chess_Piece_Horizontal_Tile = This_Tile->ID - ((Chess_Piece_Vertical_Tile - 1) * 8);

				bool Valid_Horizontal_Tile{ true };
				int Horizontal_Tile_Difference = Horizontal_Tile - Chess_Piece_Horizontal_Tile;

				if (Move_Offsets[Move_Offset_Count] > 0 && Horizontal_Tile_Difference < 0)
				{
					Valid_Horizontal_Tile = false;
				}
				else if (Move_Offsets[Move_Offset_Count] < 0 && Horizontal_Tile_Difference > 0)
				{
					Valid_Horizontal_Tile = false;
				}

				if (Tile_Index < 64 && Tile_Index >= 0 && Valid_Horizontal_Tile)
				{
					if (Tiles[Tile_Index].This_Chess_Piece != nullptr)
					{
						if (Tiles[Tile_Index].This_Chess_Piece->Team != Team && !(Type->Different_Capture_Moves))
						{
							Available_Moves[Tile_Index] = true;
						}

						break;
					}
					else
					{
						Available_Moves[Tile_Index] = true;

						if (Move_Offsets[Move_Offset_Count] != 0 && (Horizontal_Tile == 1 || Horizontal_Tile == 8))
						{
							break;
						}
					}

					if (Loop_Horizontal_Range > 0)
					{
						Loop_Horizontal_Range++;
					}
					else if (Loop_Horizontal_Range < 0)
					{
						Loop_Horizontal_Range--;
					}

					if (Loop_Vertical_Range > 0)
					{
						Loop_Vertical_Range++;
					}
					else if (Loop_Vertical_Range < 0)
					{
						Loop_Vertical_Range--;
					}
				}
			}
		}
		else // For Knight and King.
		{
			int Tile_Index = (This_Tile->ID - 1) + Move_Offsets[Move_Offset_Count] + (Move_Offsets[Move_Offset_Count + 1] * 8);

			int Horizontal_Tile;
			int Vertical_Tile;
			int Chess_Piece_Horizontal_Tile;
			int Chess_Piece_Vertical_Tile;
			int Tile_Int;
			float Tile_Float;

			// Calculate the horizontal tile.

			Tile_Int = (Tile_Index + 1) / 8;
			Tile_Float = (static_cast<float>(Tile_Index + 1)) / 8.0F;

			if (Tile_Float > Tile_Int)
			{
				Vertical_Tile = Tile_Int + 1;
			}
			else
			{
				Vertical_Tile = Tile_Int;
			}

			Horizontal_Tile = (Tile_Index + 1) - ((Vertical_Tile - 1) * 8);

			Tile_Int = This_Tile->ID / 8;
			Tile_Float = static_cast<float>(This_Tile->ID) / 8.0F;

			if (Tile_Float > Tile_Int)
			{
				Chess_Piece_Vertical_Tile = Tile_Int + 1;
			}
			else
			{
				Chess_Piece_Vertical_Tile = Tile_Int;
			}

			Chess_Piece_Horizontal_Tile = This_Tile->ID - ((Chess_Piece_Vertical_Tile - 1) * 8);

			bool Valid_Horizontal_Tile{ true };
			int Horizontal_Tile_Difference = Horizontal_Tile - Chess_Piece_Horizontal_Tile;

			if (Move_Offsets[Move_Offset_Count] > 0 && Horizontal_Tile_Difference < 0)
			{
				Valid_Horizontal_Tile = false;
			}
			else if (Move_Offsets[Move_Offset_Count] < 0 && Horizontal_Tile_Difference > 0)
			{
				Valid_Horizontal_Tile = false;
			}

			if (Tile_Index < 64 && Tile_Index >= 0 && Valid_Horizontal_Tile)
			{
				if (Tiles[Tile_Index].This_Chess_Piece != nullptr)
				{
					if (Tiles[Tile_Index].This_Chess_Piece->Team != Team)
					{
						if (Type->Different_Capture_Moves)
						{
							continue;
						}
					}
					else
					{
						continue;
					}
				}

				Available_Moves[Tile_Index] = true;
			}
		}
	}

	if (Type->Different_Capture_Moves) // For Pawn.
	{
		for (int Capture_Move_Offset_Count{ 0 }; Capture_Move_Offset_Count < Capture_Loop_Range; Capture_Move_Offset_Count = Capture_Move_Offset_Count + 2) // Loop to check the validity of each possible capture move for the chess piece. Increment by 2 because both the horizontal and vertical values for each move take 1 index each.
		{
			int Tile_Index = (This_Tile->ID - 1) + Capture_Move_Offsets[Capture_Move_Offset_Count] + (Capture_Move_Offsets[Capture_Move_Offset_Count + 1] * 8);

			// Calculate the horizontal tile.

			int Horizontal_Tile;
			int Vertical_Tile;
			int Chess_Piece_Horizontal_Tile;
			int Chess_Piece_Vertical_Tile;
			int Tile_Int;
			float Tile_Float;

			Tile_Int = (Tile_Index + 1) / 8;
			Tile_Float = (static_cast<float>(Tile_Index + 1)) / 8.0F;

			if (Tile_Float > Tile_Int)
			{
				Vertical_Tile = Tile_Int + 1;
			}
			else
			{
				Vertical_Tile = Tile_Int;
			}

			Horizontal_Tile = (Tile_Index + 1) - ((Vertical_Tile - 1) * 8);

			Tile_Int = This_Tile->ID / 8;
			Tile_Float = static_cast<float>(This_Tile->ID) / 8.0F;

			if (Tile_Float > Tile_Int)
			{
				Chess_Piece_Vertical_Tile = Tile_Int + 1;
			}
			else
			{
				Chess_Piece_Vertical_Tile = Tile_Int;
			}

			Chess_Piece_Horizontal_Tile = This_Tile->ID - ((Chess_Piece_Vertical_Tile - 1) * 8);

			bool Valid_Horizontal_Tile{ true };
			int Horizontal_Tile_Difference = Horizontal_Tile - Chess_Piece_Horizontal_Tile;

			if (Capture_Move_Offsets[Capture_Move_Offset_Count] > 0 && Horizontal_Tile_Difference < 0)
			{
				Valid_Horizontal_Tile = false;
			}
			else if (Capture_Move_Offsets[Capture_Move_Offset_Count] < 0 && Horizontal_Tile_Difference > 0)
			{
				Valid_Horizontal_Tile = false;
			}

			if (Tile_Index < 64 && Tile_Index >= 0 && Valid_Horizontal_Tile)
			{
				if (Tiles[Tile_Index].This_Chess_Piece != nullptr)
				{
					if (Tiles[Tile_Index].This_Chess_Piece->Team != Team)
					{
						Available_Moves[Tile_Index] = true;
					}
				}
			}
		}
	}

	delete[] Move_Offsets;

	if (Capture_Move_Offsets != nullptr)
	{
		delete[] Capture_Move_Offsets;
	}

	return Available_Moves;
}

void Chess_Piece::Toggle_Available_Moves(bool State, bool *Any_Available_Moves)
{
	bool *Available_Moves{ Get_Available_Moves() };

	for (int Available_Move_Count{ 0 }; Available_Move_Count < 64; Available_Move_Count++) // Loop through each tile to check if it is an available move for the chess piece.
	{
		if (Available_Moves[Available_Move_Count])
		{
			if (Tiles[Available_Move_Count].This_Chess_Piece != nullptr)
			{
				if (Tiles[Available_Move_Count].This_Chess_Piece->Type->ID == 5)
				{
					// Move is not valid because a king is on this tile. Kings cannot be captured.
					continue;
				}
			}

			Tile *Current_Position{ This_Tile };
			Chess_Piece *Captured_Chess_Piece_Return{ nullptr };

			// Virtually test the move to make sure its legal (doesn't put your own king in check, or make sure it gets your king out of check).

			Move_Chess_Piece(&Tiles[Available_Move_Count], true, &Captured_Chess_Piece_Return); // Virtually move the chess piece to the tile.
			Test_Check(Team);
			Move_Chess_Piece(Current_Position, true, &Captured_Chess_Piece_Return); // Virtually move the chess piece back to its original position after testing if your king is in check.

			if (Captured_Chess_Piece_Return != nullptr)
			{
				// Restore the virtually captured chess piece.

				Captured_Chess_Piece_Return->Captured = false;
				Captured_Chess_Piece_Return->This_Tile = &Tiles[Available_Move_Count];
				Tiles[Available_Move_Count].This_Chess_Piece = Captured_Chess_Piece_Return;
			}

			if (King_Tiles[Team]->This_Chess_Piece->Check)
			{
				// Move is not valid as the player's king is in check after the move was tested.

				Test_Check(Team);

				continue;
			}

			Test_Check(Team);

			Tiles[Available_Move_Count].Available_Move = State;

			if (Any_Available_Moves != nullptr)
			{
				*Any_Available_Moves = true;
			}
		}
	}

	delete[] Available_Moves;
}

void Chess_Piece::Move_Chess_Piece(Tile *Destination, bool Virtual_Move, Chess_Piece **Captured_Chess_Piece_Return)
{
	if (Virtual_Move) // Don't change unnecessary variables if virtual move.
	{
		if (Destination->This_Chess_Piece != nullptr)
		{
			*Captured_Chess_Piece_Return = Destination->This_Chess_Piece;
			Destination->This_Chess_Piece->Capture_Chess_Piece(*this, true);
		}
	}
	else
	{
		Toggle_Available_Moves(false);

		if (First_Move)
		{
			First_Move = false;
		}

		if (Destination->This_Chess_Piece != nullptr)
		{
			Destination->This_Chess_Piece->Capture_Chess_Piece(*this);
		}
	}

	This_Tile->This_Chess_Piece = nullptr;
	This_Tile = Destination;
	This_Tile->This_Chess_Piece = this;

	if (Type->ID == 5)
	{
		King_Tiles[Team] = This_Tile;
	}

	if (!(Virtual_Move))
	{
		Test_Check();

		if (Team == 0)
		{
			Test_Checkmate_And_Stalemate(1);
		}
		else
		{
			Test_Checkmate_And_Stalemate(0);
		}
	}
}

bool Loop_Condition(int Loop_Count, int Loop_Range)
{
	bool Return_Value;

	if (Loop_Range > 0)
	{
		if (Loop_Count < (Loop_Range) + 1)
		{
			Return_Value = true;
		}
		else
		{
			Return_Value = false;
		}
	}
	else
	{
		if (Loop_Count > (Loop_Range) - 1)
		{
			Return_Value = true;
		}
		else
		{
			Return_Value = false;
		}
	}

	return Return_Value;
}

void Loop_Increment(int &Loop_Count, int &Loop_Range)
{
	if (Loop_Range > 0)
	{
		Loop_Count++;
	}
	else
	{
		Loop_Count--;
	}
}

void Update_Chess_Piece_Images()
{
	int Index_Modifer;
	ID2D1Bitmap *Total_Chess_Piece_Images[]{ Chess_Piece_Images[5].This_Interface, Chess_Piece_Images[2].This_Interface, Chess_Piece_Images[0].This_Interface, Chess_Piece_Images[4].This_Interface, Chess_Piece_Images[1].This_Interface, Chess_Piece_Images[0].This_Interface, Chess_Piece_Images[2].This_Interface, Chess_Piece_Images[5].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[3].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[9].This_Interface,Chess_Piece_Images[9].This_Interface, Chess_Piece_Images[11].This_Interface, Chess_Piece_Images[7].This_Interface, Chess_Piece_Images[6].This_Interface, Chess_Piece_Images[10].This_Interface, Chess_Piece_Images[8].This_Interface, Chess_Piece_Images[6].This_Interface, Chess_Piece_Images[7].This_Interface, Chess_Piece_Images[11].This_Interface };

	for (int Chess_Piece_Count = 0; Chess_Piece_Count < 32; Chess_Piece_Count++)
	{
		Chess_Pieces[Chess_Piece_Count].Image = Total_Chess_Piece_Images[Chess_Piece_Count];

		if (Chess_Piece_Count < 16)
		{
			Index_Modifer = 0;
		}
		else
		{
			Index_Modifer = 32;
		}
	}
}

void Chess_Piece::Capture_Chess_Piece(Chess_Piece &Capturing_Chess_Piece, bool Virtual_Capture)
{
	This_Tile = nullptr;
	Captured = true;

	if (!(Virtual_Capture))
	{
		int Captured_Chess_Piece_Count{ 0 };

		for (Captured_Chess_Piece_Count; Captured_Chess_Piece_Count < 32; Captured_Chess_Piece_Count++)
		{
			if (Captured_Chess_Pieces[Captured_Chess_Piece_Count] == nullptr)
			{
				break;
			}
		}

		Captured_Chess_Pieces[Captured_Chess_Piece_Count] = this;
	}
}