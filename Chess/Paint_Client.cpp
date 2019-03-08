#include "stdafx.h"
#include "d3d11_4.h"
#include "d2d1_1.h"
#include "Resources.h"
#include "Engine.h"
#include "Chess.h"
#include "Paint_Client.h"
#include "Tile.h"
#include "Chess_Piece.h"
#include "Team.h"
#include "Button.h"
#include "Scene.h"

void Paint_Client()
{
	D3DCOLORVALUE Dark_Grey;
	Dark_Grey.r = 0.2F;
	Dark_Grey.g = 0.2F;
	Dark_Grey.b = 0.2F;
	Dark_Grey.a = 1.0F;

	BeginPaint(Main_Window_Handle, nullptr);
	Device_Context.This_Interface->BeginDraw();
	Device_Context.This_Interface->Clear(Dark_Grey);

	if (Scene != 0)
	{
		D3DCOLORVALUE Light_Grey;
		Light_Grey.r = 0.8F;
		Light_Grey.g = 0.8F;
		Light_Grey.b = 0.8F;
		Light_Grey.a = 1.0F;

		D3DCOLORVALUE White;
		White.r = 1.0F;
		White.g = 1.0F;
		White.b = 1.0F;
		White.a = 1.0F;

		D3DCOLORVALUE Black;
		Black.r = 0.0F;
		Black.g = 0.0F;
		Black.b = 0.0F;
		Black.a = 1.0F;

		D2D_RECT_F Outer_Border;
		Outer_Border.bottom = Tiles[63].This_Tile.bottom + 1;
		Outer_Border.left = Tiles[0].This_Tile.left - 1;
		Outer_Border.right = Tiles[63].This_Tile.right + 1;
		Outer_Border.top = Tiles[0].This_Tile.top - 1;

		D2D_RECT_F White_Turn_Text;
		White_Turn_Text.bottom = Outer_Border.bottom - 1;
		White_Turn_Text.right = Outer_Border.left - 10;
		White_Turn_Text.top = White_Turn_Text.bottom - 24;
		White_Turn_Text.left = White_Turn_Text.right - 133;

		D2D_RECT_F Black_Turn_Text;
		Black_Turn_Text.top = Outer_Border.top + 1;
		Black_Turn_Text.right = Outer_Border.left - 10;
		Black_Turn_Text.bottom = Black_Turn_Text.top + 24;
		Black_Turn_Text.left = Black_Turn_Text.right - 133;

		D2D_RECT_F White_Check_Text;
		White_Check_Text.bottom = White_Turn_Text.top - 24;
		White_Check_Text.right = White_Turn_Text.right;
		White_Check_Text.top = White_Check_Text.bottom - 24;
		White_Check_Text.left = White_Check_Text.right - 69;

		D2D_RECT_F Black_Check_Text;
		Black_Check_Text.right = Black_Turn_Text.right;
		Black_Check_Text.top = Black_Turn_Text.bottom + 24;
		Black_Check_Text.left = Black_Check_Text.right - 69;
		Black_Check_Text.bottom = Black_Check_Text.top + 24;

		D2D_RECT_F White_Captured_Chess_Pieces_Rect;
		White_Captured_Chess_Pieces_Rect.bottom = Outer_Border.bottom;
		White_Captured_Chess_Pieces_Rect.top = White_Captured_Chess_Pieces_Rect.bottom - 124;
		White_Captured_Chess_Pieces_Rect.left = Outer_Border.right + 1;
		White_Captured_Chess_Pieces_Rect.right = White_Captured_Chess_Pieces_Rect.left + 360;

		D2D_RECT_F Black_Captured_Chess_Pieces_Rect;
		Black_Captured_Chess_Pieces_Rect.top = Outer_Border.top;
		Black_Captured_Chess_Pieces_Rect.bottom = Black_Captured_Chess_Pieces_Rect.top + 124;
		Black_Captured_Chess_Pieces_Rect.left = Outer_Border.right + 1;
		Black_Captured_Chess_Pieces_Rect.right = Black_Captured_Chess_Pieces_Rect.left + 360;

		D2D_RECT_F White_Captured_Chess_Pieces_Text;
		White_Captured_Chess_Pieces_Text.bottom = White_Captured_Chess_Pieces_Rect.bottom - 10;
		White_Captured_Chess_Pieces_Text.top = White_Captured_Chess_Pieces_Text.bottom - 24;
		White_Captured_Chess_Pieces_Text.left = Outer_Border.right;
		White_Captured_Chess_Pieces_Text.right = White_Captured_Chess_Pieces_Text.left + 360;

		D2D_RECT_F Black_Captured_Chess_Pieces_Text;
		Black_Captured_Chess_Pieces_Text.top = Black_Captured_Chess_Pieces_Rect.top + 10;
		Black_Captured_Chess_Pieces_Text.bottom = Black_Captured_Chess_Pieces_Text.top + 24;
		Black_Captured_Chess_Pieces_Text.left = Outer_Border.right;
		Black_Captured_Chess_Pieces_Text.right = Black_Captured_Chess_Pieces_Text.left + 360;

		D2D_RECT_F White_Captured_Chess_Pieces_Background;
		White_Captured_Chess_Pieces_Background.bottom = White_Captured_Chess_Pieces_Rect.bottom - 1;
		White_Captured_Chess_Pieces_Background.left = White_Captured_Chess_Pieces_Rect.left + 1;
		White_Captured_Chess_Pieces_Background.right = White_Captured_Chess_Pieces_Rect.right - 1;
		White_Captured_Chess_Pieces_Background.top = White_Captured_Chess_Pieces_Rect.top + 1;

		for (int Tile_Count = 0; Tile_Count < 64; Tile_Count++) // Draw the tiles and chess pieces.
		{
			if (Tile_Clicked != nullptr)
			{
				if (Tile_Count == Tile_Clicked->ID - 1)
				{
					Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Selected_Color);
				}
				else if (Tiles[Tile_Count].Available_Move)
				{
					Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Available_Move_Color);
				}
				else if (Tiles[Tile_Count].This_Chess_Piece != nullptr)
				{
					if (Tiles[Tile_Count].This_Chess_Piece->Check)
					{
						Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Check_Color);
					}
					else
					{
						Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Color);
					}
				}
				else
				{
					Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Color);
				}
			}
			else if (Tiles[Tile_Count].This_Chess_Piece != nullptr)
			{
				if (Tiles[Tile_Count].This_Chess_Piece->Check)
				{
					Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Check_Color);
				}
				else
				{
					Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Color);
				}
			}
			else
			{
				Brush.This_Interface->SetColor(Tiles[Tile_Count].Tile_Color);
			}

			Device_Context.This_Interface->FillRectangle(Tiles[Tile_Count].This_Tile, Brush.This_Interface);

			if (Tiles[Tile_Count].This_Chess_Piece != nullptr)
			{
				Device_Context.This_Interface->DrawBitmap(Tiles[Tile_Count].This_Chess_Piece->Image, &Tiles[Tile_Count].This_Tile, 1.0F, D2D1_INTERPOLATION_MODE_CUBIC);
			}
		}

		Brush.This_Interface->SetColor(White);
		Device_Context.This_Interface->DrawRectangle(Outer_Border, Brush.This_Interface); // Draw border around chess board.

		DWrite_Text_Format.This_Interface->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

		// Draw all text.

		if (Team_Turn == 0)
		{
			DWrite_Text_Format.This_Interface->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			Device_Context.This_Interface->DrawTextW(L"Black's Turn", 12, DWrite_Text_Format.This_Interface, &Black_Turn_Text, Brush.This_Interface);
		}
		else
		{
			DWrite_Text_Format.This_Interface->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			Device_Context.This_Interface->DrawTextW(L"White's Turn", 12, DWrite_Text_Format.This_Interface, &White_Turn_Text, Brush.This_Interface);
		}

		if (King_Tiles[0]->This_Chess_Piece->Check || King_Tiles[1]->This_Chess_Piece->Check)
		{
			wchar_t *Text{ const_cast<wchar_t*>(L"Check") };

			if (Game_Over)
			{
				Text = const_cast<wchar_t*>(L"Checkmate");
			}

			if (King_Tiles[0]->This_Chess_Piece->Check)
			{
				if (Game_Over)
				{
					Black_Check_Text.left = Black_Check_Text.right - 122;
				}

				DWrite_Text_Format.This_Interface->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				Device_Context.This_Interface->DrawTextW(Text, static_cast<UINT32>(wcslen(Text)), DWrite_Text_Format.This_Interface, &Black_Check_Text, Brush.This_Interface);
			}
			else
			{
				if (Game_Over)
				{
					White_Check_Text.left = White_Check_Text.right - 122;
				}

				DWrite_Text_Format.This_Interface->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				Device_Context.This_Interface->DrawTextW(Text, static_cast<UINT32>(wcslen(Text)), DWrite_Text_Format.This_Interface, &White_Check_Text, Brush.This_Interface);
			}
		}

		DWrite_Text_Format.This_Interface->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		DWrite_Text_Format.This_Interface->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		// Draw captured chess piece boxes.

		Device_Context.This_Interface->DrawRectangle(Black_Captured_Chess_Pieces_Rect, Brush.This_Interface);
		Brush.This_Interface->SetColor(Light_Grey);
		Device_Context.This_Interface->FillRectangle(White_Captured_Chess_Pieces_Background, Brush.This_Interface);
		Brush.This_Interface->SetColor(White);
		Device_Context.This_Interface->DrawRectangle(White_Captured_Chess_Pieces_Rect, Brush.This_Interface);

		Device_Context.This_Interface->DrawTextW(L"Captured Chess Pieces", 21, DWrite_Text_Format.This_Interface, &Black_Captured_Chess_Pieces_Text, Brush.This_Interface);
		Brush.This_Interface->SetColor(Black);
		Device_Context.This_Interface->DrawTextW(L"Captured Chess Pieces", 21, DWrite_Text_Format.This_Interface, &White_Captured_Chess_Pieces_Text, Brush.This_Interface);
		Brush.This_Interface->SetColor(White);

		int White_Captured_Chess_Pieces_Horizontal_Count{ 0 };
		int White_Captured_Chess_Pieces_Vertical_Count{ 0 };
		int Black_Captured_Chess_Pieces_Horizontal_Count{ 0 };
		int Black_Captured_Chess_Pieces_Vertical_Count{ 0 };

		for (int Captured_Chess_Piece_Count{ 0 }; Captured_Chess_Piece_Count < 32; Captured_Chess_Piece_Count++) // Add the captured chess pieces to the related box.
		{
			if (Captured_Chess_Pieces[Captured_Chess_Piece_Count] == nullptr)
			{
				break;
			}

			D2D_RECT_F Captured_Chess_Piece;

			if (Captured_Chess_Pieces[Captured_Chess_Piece_Count]->Team == 0)
			{
				Captured_Chess_Piece.bottom = White_Captured_Chess_Pieces_Text.top - (White_Captured_Chess_Pieces_Vertical_Count * 45);
				Captured_Chess_Piece.top = Captured_Chess_Piece.bottom - 45;
				Captured_Chess_Piece.left = Outer_Border.right + (White_Captured_Chess_Pieces_Horizontal_Count * 45);
				Captured_Chess_Piece.right = Captured_Chess_Piece.left + 45;

				Device_Context.This_Interface->DrawBitmap(Captured_Chess_Pieces[Captured_Chess_Piece_Count]->Image, Captured_Chess_Piece, 1.0F, D2D1_INTERPOLATION_MODE_CUBIC);

				if (White_Captured_Chess_Pieces_Horizontal_Count == 7)
				{
					White_Captured_Chess_Pieces_Horizontal_Count = 0;
					White_Captured_Chess_Pieces_Vertical_Count++;
				}
				else
				{
					White_Captured_Chess_Pieces_Horizontal_Count++;
				}
			}
			else
			{
				Captured_Chess_Piece.top = Black_Captured_Chess_Pieces_Text.bottom + (Black_Captured_Chess_Pieces_Vertical_Count * 45);
				Captured_Chess_Piece.bottom = Captured_Chess_Piece.top + 45;
				Captured_Chess_Piece.left = Outer_Border.right + (Black_Captured_Chess_Pieces_Horizontal_Count * 45);
				Captured_Chess_Piece.right = Captured_Chess_Piece.left + 45;

				Device_Context.This_Interface->DrawBitmap(Captured_Chess_Pieces[Captured_Chess_Piece_Count]->Image, Captured_Chess_Piece, 1.0F, D2D1_INTERPOLATION_MODE_CUBIC);

				if (Black_Captured_Chess_Pieces_Horizontal_Count == 7)
				{
					Black_Captured_Chess_Pieces_Horizontal_Count = 0;
					Black_Captured_Chess_Pieces_Vertical_Count++;
				}
				else
				{
					Black_Captured_Chess_Pieces_Horizontal_Count++;
				}
			}
		}
	}

	for (int Count{ 0 }; Count < Size_Of_Button_Array; Count++)
	{
		D2D_RECT_F Button_Rect;
		Button_Rect.top = static_cast<float>(Buttons[Count].Y);
		Button_Rect.bottom = Button_Rect.top + Buttons[Count].Height;
		Button_Rect.left = static_cast<float>(Buttons[Count].X);
		Button_Rect.right = Button_Rect.left + Buttons[Count].Width;

		Device_Context.This_Interface->DrawRectangle(Button_Rect, Brush.This_Interface);
		Device_Context.This_Interface->DrawTextW(Buttons[Count].Text, static_cast<UINT32>(wcslen(Buttons[Count].Text)), DWrite_Text_Format.This_Interface, Button_Rect, Brush.This_Interface);
	}

	if (Device_Context.This_Interface->EndDraw() == D2DERR_RECREATE_TARGET)
	{
		Create_Resources();
		Update_Tile_Positions();
		Update_Chess_Piece_Images();
	}
	else
	{
		DXGI_PRESENT_PARAMETERS Present_Parameters;
		Present_Parameters.DirtyRectsCount = 0;
		Present_Parameters.pDirtyRects = 0;
		Present_Parameters.pScrollRect = 0;
		Present_Parameters.pScrollOffset = 0;

		HRESULT Present1_Result{ Swap_Chain.This_Interface->Present1(1, 0, &Present_Parameters) }; // Display the new frame.

		ValidateRect(Main_Window_Handle, nullptr);
	}

	EndPaint(Main_Window_Handle, nullptr);
}