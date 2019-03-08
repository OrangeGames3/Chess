#include "stdafx.h"
#include "d3d11_4.h"
#include "d2d1_1.h"
#include "Tile.h"
#include "Chess_Piece.h"
#include "Chess.h"

Tile Tiles[64];
Tile *King_Tiles[2];

void Create_Tiles()
{
	D3DCOLORVALUE Light_Grey;
	Light_Grey.r = 0.8F;
	Light_Grey.g = 0.8F;
	Light_Grey.b = 0.8F;
	Light_Grey.a = 1.0F;

	D3DCOLORVALUE Dark_Grey;
	Dark_Grey.r = 0.2F;
	Dark_Grey.g = 0.2F;
	Dark_Grey.b = 0.2F;
	Dark_Grey.a = 1.0F;

	D3DCOLORVALUE Green_Dark_Grey;
	Green_Dark_Grey.r = 0.1F;
	Green_Dark_Grey.g = 0.6F;
	Green_Dark_Grey.b = 0.1F;
	Green_Dark_Grey.a = 1.0F;

	D3DCOLORVALUE Green_Light_Grey;
	Green_Light_Grey.r = 0.4F;
	Green_Light_Grey.g = 0.9F;
	Green_Light_Grey.b = 0.4F;
	Green_Light_Grey.a = 1.0F;

	D3DCOLORVALUE Yellow_Light_Grey;
	Yellow_Light_Grey.r = 0.9F;
	Yellow_Light_Grey.g = 0.9F;
	Yellow_Light_Grey.b = 0.4F;
	Yellow_Light_Grey.a = 1.0F;

	D3DCOLORVALUE Yellow_Dark_Grey;
	Yellow_Dark_Grey.r = 0.6F;
	Yellow_Dark_Grey.g = 0.6F;
	Yellow_Dark_Grey.b = 0.1F;
	Yellow_Dark_Grey.a = 1.0F;

	D3DCOLORVALUE Red_Light_Grey;
	Red_Light_Grey.r = 0.9F;
	Red_Light_Grey.g = 0.4F;
	Red_Light_Grey.b = 0.4F;
	Red_Light_Grey.a = 1.0F;

	D3DCOLORVALUE Red_Dark_Grey;
	Red_Dark_Grey.r = 0.6F;
	Red_Dark_Grey.g = 0.1F;
	Red_Dark_Grey.b = 0.1F;
	Red_Dark_Grey.a = 1.0F;

	RECT Client_Rect;
	GetClientRect(Main_Window_Handle, &Client_Rect);

	int Horizontal_Center = Client_Rect.right / 2;
	int Horizontal_Start = Horizontal_Center - 360;

	int Vertical_Center = Client_Rect.bottom / 2;
	int Vertical_Start = Vertical_Center - 360;

	D2D_RECT_F Tile_Rectangle;
	Tile_Rectangle.top = static_cast<float>(Vertical_Start);
	Tile_Rectangle.left = static_cast<float>(Horizontal_Start);
	Tile_Rectangle.right = static_cast<float>(Horizontal_Start) + 90.0F;
	Tile_Rectangle.bottom = static_cast<float>(Vertical_Start) + 90.0F;

	int Tile_Count{ 0 };

	for (int Vertical_Tile_Count = 0; Vertical_Tile_Count < 8; Vertical_Tile_Count++) // Initialise variables for all tiles.
	{
		for (int Horizontal_Tile_Count = 0; Horizontal_Tile_Count < 8; Horizontal_Tile_Count++)
		{
			Tiles[Tile_Count].ID = Tile_Count + 1;
			Tiles[Tile_Count].This_Tile = Tile_Rectangle;

			if (Vertical_Tile_Count % 2 == 0)
			{
				if (Horizontal_Tile_Count % 2 == 0)
				{
					Tiles[Tile_Count].Tile_Color = Light_Grey;
					Tiles[Tile_Count].Tile_Selected_Color = Green_Light_Grey;
					Tiles[Tile_Count].Tile_Available_Move_Color = Yellow_Light_Grey;
					Tiles[Tile_Count].Tile_Check_Color = Red_Light_Grey;
				}
				else
				{
					Tiles[Tile_Count].Tile_Color = Dark_Grey;
					Tiles[Tile_Count].Tile_Selected_Color = Green_Dark_Grey;
					Tiles[Tile_Count].Tile_Available_Move_Color = Yellow_Dark_Grey;
					Tiles[Tile_Count].Tile_Check_Color = Red_Dark_Grey;
				}
			}
			else
			{
				if (Horizontal_Tile_Count % 2 == 0)
				{
					Tiles[Tile_Count].Tile_Color = Dark_Grey;
					Tiles[Tile_Count].Tile_Selected_Color = Green_Dark_Grey;
					Tiles[Tile_Count].Tile_Available_Move_Color = Yellow_Dark_Grey;
					Tiles[Tile_Count].Tile_Check_Color = Red_Dark_Grey;
				}
				else
				{
					Tiles[Tile_Count].Tile_Color = Light_Grey;
					Tiles[Tile_Count].Tile_Selected_Color = Green_Light_Grey;
					Tiles[Tile_Count].Tile_Available_Move_Color = Yellow_Light_Grey;
					Tiles[Tile_Count].Tile_Check_Color = Red_Light_Grey;
				}
			}

			if (Tile_Count < 16)
			{
				Tiles[Tile_Count].This_Chess_Piece = &Chess_Pieces[Tile_Count];
			}
			else if (Tile_Count > 47)
			{
				Tiles[Tile_Count].This_Chess_Piece = &Chess_Pieces[Tile_Count - 32];
			}

			Tile_Rectangle.left += 90.0F;
			Tile_Rectangle.right += 90.0F;

			Tile_Count += 1;
		}

		Tile_Rectangle.left = static_cast<float>(Horizontal_Start);
		Tile_Rectangle.right = static_cast<float>(Horizontal_Start) + 90.0F;
		Tile_Rectangle.top += 90.0F;
		Tile_Rectangle.bottom += 90.0F;
	}
}

void Update_Tile_Positions()
{
	RECT Client_Rect;
	GetClientRect(Main_Window_Handle, &Client_Rect);

	int Horizontal_Center = Client_Rect.right / 2;
	int Horizontal_Start = Horizontal_Center - 360;

	int Vertical_Center = Client_Rect.bottom / 2;
	int Vertical_Start = Vertical_Center - 360;

	D2D_RECT_F Tile_Rectangle;
	Tile_Rectangle.top = static_cast<float>(Vertical_Start);
	Tile_Rectangle.left = static_cast<float>(Horizontal_Start);
	Tile_Rectangle.right = static_cast<float>(Horizontal_Start) + 90.0F;
	Tile_Rectangle.bottom = static_cast<float>(Vertical_Start) + 90.0F;

	int Tile_Count{ 0 };

	for (int Vertical_Tile_Count = 0; Vertical_Tile_Count < 8; Vertical_Tile_Count++)
	{
		for (int Horizontal_Tile_Count = 0; Horizontal_Tile_Count < 8; Horizontal_Tile_Count++)
		{
			Tiles[Tile_Count].This_Tile = Tile_Rectangle;

			Tile_Rectangle.left += 90.0F;
			Tile_Rectangle.right += 90.0F;

			Tile_Count += 1;
		}

		Tile_Rectangle.left = static_cast<float>(Horizontal_Start);
		Tile_Rectangle.right = static_cast<float>(Horizontal_Start) + 90.0F;
		Tile_Rectangle.top += 90.0F;
		Tile_Rectangle.bottom += 90.0F;
	}
}