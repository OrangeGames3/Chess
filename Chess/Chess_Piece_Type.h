#pragma once

#include "stdafx.h"

class Chess_Piece_Type
{
public:
	int ID; // The ID of the type. 1 = Rook, 2 = Knight, 3 = Bishop, 4 = Queen, 5 = King, 6 = Pawn
	int *White_Move_Offsets; // Stores tile positions of possible moves relative to the chess piece's position.
	int *Black_Move_Offsets; // Stores tile positions of possible moves relative to the chess piece's position.
	int *White_Capture_Move_Offsets; // For types that can move differently to capture an enemy chess piece. Only relevant for Pawns.
	int *Black_Capture_Move_Offsets; // For types that can move differently to capture an enemy chess piece. Only relevant for Pawns.
	int Number_Of_Moves; // Number of different directions a chess piece can move.
	int Max_Variable_Move_Distance;
	int Capture_Number_Of_Moves; // For types that can move differently to capture an enemy chess piece. Only relevant for Pawns.
	bool Different_First_Moves;
	bool Variable_Move_Distance;
	bool Different_Capture_Moves;
	bool Variable_First_Move_Distance;

	Chess_Piece_Type();
	~Chess_Piece_Type(); // Function called automatically when object goes out of scope to free memory.
};

extern Chess_Piece_Type Chess_Piece_Types[6];

extern void Create_Chess_Piece_Types();