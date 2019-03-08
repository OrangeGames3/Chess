#pragma once

#include "stdafx.h"
#include "d2d1_1.h"

class Tile;
class Chess_Piece_Type;

class Chess_Piece
{
public:
	ID2D1Bitmap *Image;
	Tile *This_Tile; // Pointer to the tile that this chess piece is on.
	Chess_Piece_Type *Type;
	bool First_Move; // True if the chess piece hasn't made any moves yet.
	bool Check; // True if the chess piece is in Check. Only relevant for King chess piece types.
	int Team; // The team the chess piece is associated with. Either 0 (Black) or 1 (White).
	int ID;
	bool Captured; // True if the chess piece has been captured by an enemy chess piece.

	void Toggle_Available_Moves(bool, bool* = nullptr);
	void Move_Chess_Piece(Tile*, bool = false, Chess_Piece** = nullptr );
	bool* Get_Available_Moves();
	void Capture_Chess_Piece(Chess_Piece&, bool = false);
};

extern Chess_Piece Chess_Pieces[32];
extern Chess_Piece *Captured_Chess_Pieces[32];

void Create_Chess_Pieces();
void Update_Chess_Piece_Images();