#include "stdafx.h"
#include "Chess_Piece_Type.h"

Chess_Piece_Type Chess_Piece_Types[6];

Chess_Piece_Type::Chess_Piece_Type()
{
	Different_First_Moves = false;
	Variable_Move_Distance = true ;
	Different_Capture_Moves = false;
	Variable_First_Move_Distance = false;
}

Chess_Piece_Type::~Chess_Piece_Type()
{
	delete[] White_Move_Offsets;
	delete[] Black_Move_Offsets;

	if (Different_Capture_Moves)
	{
		delete[] White_Capture_Move_Offsets;
		delete[] Black_Capture_Move_Offsets;
	}
}

void Create_Chess_Piece_Types()
{
	for (int Type_Count = 0; Type_Count < 6; Type_Count++) // Initialise variables for all chess piece types.
	{
		Chess_Piece_Types[Type_Count].ID = Type_Count + 1;

		if (Type_Count == 0) // Rook.
		{
			Chess_Piece_Types[Type_Count].Number_Of_Moves = 4;
			Chess_Piece_Types[Type_Count].Max_Variable_Move_Distance = 7;

			Chess_Piece_Types[Type_Count].White_Move_Offsets = new int[8];
			Chess_Piece_Types[Type_Count].White_Move_Offsets[0] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[1] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[2] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[3] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[4] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[5] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[6] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[7] = 0;

			Chess_Piece_Types[Type_Count].Black_Move_Offsets = new int[8];

			for (int Count{ 0 }; Count < 8; Count++)
			{
				Chess_Piece_Types[Type_Count].Black_Move_Offsets[Count] = Chess_Piece_Types[Type_Count].White_Move_Offsets[Count];
			}
		}
		else if (Type_Count == 1) // Knight.
		{
			Chess_Piece_Types[Type_Count].Number_Of_Moves = 8;
			Chess_Piece_Types[Type_Count].Variable_Move_Distance = false;

			Chess_Piece_Types[Type_Count].White_Move_Offsets = new int[16];
			Chess_Piece_Types[Type_Count].White_Move_Offsets[0] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[1] = -2;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[2] = 2;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[3] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[4] = 2;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[5] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[6] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[7] = 2;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[8] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[9] = 2;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[10] = -2;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[11] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[12] = -2;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[13] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[14] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[15] = -2;

			Chess_Piece_Types[Type_Count].Black_Move_Offsets = new int[16];

			for (int Count{ 0 }; Count < 16; Count++)
			{
				Chess_Piece_Types[Type_Count].Black_Move_Offsets[Count] = Chess_Piece_Types[Type_Count].White_Move_Offsets[Count];
			}
		}
		else if (Type_Count == 2) // Bishop.
		{
			Chess_Piece_Types[Type_Count].Number_Of_Moves = 4;
			Chess_Piece_Types[Type_Count].Max_Variable_Move_Distance = 7;

			Chess_Piece_Types[Type_Count].White_Move_Offsets = new int[8];
			Chess_Piece_Types[Type_Count].White_Move_Offsets[0] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[1] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[2] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[3] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[4] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[5] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[6] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[7] = -1;

			Chess_Piece_Types[Type_Count].Black_Move_Offsets = new int[8];

			for (int Count{ 0 }; Count < 8; Count++)
			{
				Chess_Piece_Types[Type_Count].Black_Move_Offsets[Count] = Chess_Piece_Types[Type_Count].White_Move_Offsets[Count];
			}
		}
		else if (Type_Count == 3) // Queen.
		{
			Chess_Piece_Types[Type_Count].Number_Of_Moves = 8;
			Chess_Piece_Types[Type_Count].Max_Variable_Move_Distance = 7;

			Chess_Piece_Types[Type_Count].White_Move_Offsets = new int[16];
			Chess_Piece_Types[Type_Count].White_Move_Offsets[0] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[1] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[2] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[3] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[4] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[5] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[6] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[7] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[8] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[9] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[10] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[11] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[12] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[13] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[14] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[15] = -1;

			Chess_Piece_Types[Type_Count].Black_Move_Offsets = new int[16];

			for (int Count{ 0 }; Count < 16; Count++)
			{
				Chess_Piece_Types[Type_Count].Black_Move_Offsets[Count] = Chess_Piece_Types[Type_Count].White_Move_Offsets[Count];
			}
		}
		else if (Type_Count == 4) // King.
		{
			Chess_Piece_Types[Type_Count].Number_Of_Moves = 8;
			Chess_Piece_Types[Type_Count].Variable_Move_Distance = false;

			Chess_Piece_Types[Type_Count].White_Move_Offsets = new int[16];
			Chess_Piece_Types[Type_Count].White_Move_Offsets[0] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[1] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[2] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[3] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[4] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[5] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[6] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[7] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[8] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[9] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[10] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[11] = 1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[12] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[13] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[14] = -1;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[15] = -1;

			Chess_Piece_Types[Type_Count].Black_Move_Offsets = new int[16];

			for (int Count{ 0 }; Count < 16; Count++)
			{
				Chess_Piece_Types[Type_Count].Black_Move_Offsets[Count] = Chess_Piece_Types[Type_Count].White_Move_Offsets[Count];
			}
		}
		else // Pawn.
		{
			Chess_Piece_Types[Type_Count].Number_Of_Moves = 1;
			Chess_Piece_Types[Type_Count].Capture_Number_Of_Moves = 2;
			Chess_Piece_Types[Type_Count].Max_Variable_Move_Distance = 2;
			Chess_Piece_Types[Type_Count].Different_First_Moves = true;
			Chess_Piece_Types[Type_Count].Variable_Move_Distance = false;
			Chess_Piece_Types[Type_Count].Different_Capture_Moves = true;
			Chess_Piece_Types[Type_Count].Variable_First_Move_Distance = true;

			Chess_Piece_Types[Type_Count].White_Move_Offsets = new int[2];
			Chess_Piece_Types[Type_Count].White_Move_Offsets[0] = 0;
			Chess_Piece_Types[Type_Count].White_Move_Offsets[1] = -1;

			Chess_Piece_Types[Type_Count].Black_Move_Offsets = new int[2];
			Chess_Piece_Types[Type_Count].Black_Move_Offsets[0] = 0;
			Chess_Piece_Types[Type_Count].Black_Move_Offsets[1] = 1;

			Chess_Piece_Types[Type_Count].White_Capture_Move_Offsets = new int[4];
			Chess_Piece_Types[Type_Count].White_Capture_Move_Offsets[0] = 1;
			Chess_Piece_Types[Type_Count].White_Capture_Move_Offsets[1] = -1;
			Chess_Piece_Types[Type_Count].White_Capture_Move_Offsets[2] = -1;
			Chess_Piece_Types[Type_Count].White_Capture_Move_Offsets[3] = -1;

			Chess_Piece_Types[Type_Count].Black_Capture_Move_Offsets = new int[4];
			Chess_Piece_Types[Type_Count].Black_Capture_Move_Offsets[0] = 1;
			Chess_Piece_Types[Type_Count].Black_Capture_Move_Offsets[1] = 1;
			Chess_Piece_Types[Type_Count].Black_Capture_Move_Offsets[2] = -1;
			Chess_Piece_Types[Type_Count].Black_Capture_Move_Offsets[3] = 1;
		}
	}
}