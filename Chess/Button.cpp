#include "stdafx.h"
#include "Button.h"
#include "Tile.h"
#include "Chess.h"
#include "Scene.h"

Button *Buttons{ nullptr };
int Size_Of_Button_Array{ 0 };

Button::Button()
{
	Width = 200;
	Height = 50;
}

void Button::Process_Button_Click()
{
	Load_Scene(ID);
}

void Button::Add_Button_To_Array()
{
	Button *Buttons_Buffer{ nullptr };

	if (Buttons != nullptr)
	{
		Buttons_Buffer = new Button[Size_Of_Button_Array]; // Create a buffer to store all the buttons that were already in the Buttons array.

		for (int Count{ 0 }; Count < Size_Of_Button_Array; Count++) // Fill the buffer.
		{
			Buttons_Buffer[Count] = Buttons[Count];
		}

		delete[] Buttons;
	}

	Buttons = new Button[Size_Of_Button_Array + 1]; // Create new array to store everything in the buffer.
	Size_Of_Button_Array += 1;

	if (Buttons_Buffer != nullptr)
	{
		for (int Count{ 0 }; Count < Size_Of_Button_Array - 1; Count++) // Fill the new array.
		{
			Buttons[Count] = Buttons_Buffer[Count];
		}

		delete[] Buttons_Buffer;
	}

	Buttons[Size_Of_Button_Array - 1] = *this; // Add the newly created button.
}

void Create_Button(int ID, wchar_t Text[], int X, int Y)
{
	Button *This_Button{ new Button };
	This_Button->ID = ID;
	This_Button->Text = Text;
	This_Button->X = X;
	This_Button->Y = Y;

	This_Button->Add_Button_To_Array();
}

void Create_Dynamically_Positioned_Button(int ID, wchar_t Text[])
{
	Button *Latest_Button{ nullptr };

	if (Buttons != nullptr)
	{
		Latest_Button = &Buttons[Size_Of_Button_Array - 1];
	}

	Button *This_Button{ new Button };
	This_Button->ID = ID;
	This_Button->Text = Text;
	This_Button->X = Latest_Button->X;
	This_Button->Y = Latest_Button->Y + Latest_Button->Height + 10;

	This_Button->Add_Button_To_Array();
}

void Delete_All_Buttons()
{
	delete[] Buttons;
	Buttons = nullptr;
	Size_Of_Button_Array = 0;
}