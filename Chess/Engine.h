#pragma once

#include "stdafx.h"
#include "Tile.h"

extern Tile *Tile_Clicked;
extern bool Game_Over;
extern bool Display_Win_Lose_Message;
extern bool Display_Draw_Message;

void Process_Action(int, int); // Process mouse clicks on the chess board to perform the relevant actions.
void Test_Check(int); // Tests whether a specific team's King is in check.
void Test_Check(); // Tests both team's King to see if it is in check.
void Test_Checkmate_And_Stalemate(int);
void Test_Stalemate(int);