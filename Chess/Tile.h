#pragma once

#include "stdafx.h"
#include "d3d11_4.h"
#include "d2d1_1.h"

class Chess_Piece;

class Tile {
public:
	int ID;
	bool Available_Move{ false }; // True if this tile is an available move for a chess piece.
	Chess_Piece *This_Chess_Piece; // Pointer to the chess piece that is on this tile.
	D3DCOLORVALUE Tile_Color;
	D3DCOLORVALUE Tile_Selected_Color;
	D3DCOLORVALUE Tile_Available_Move_Color;
	D3DCOLORVALUE Tile_Check_Color;
	D2D_RECT_F This_Tile;
};

extern Tile Tiles[64];
extern Tile *King_Tiles[2];

extern void Create_Tiles();
extern void Update_Tile_Positions();