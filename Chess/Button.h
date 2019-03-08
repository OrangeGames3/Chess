#pragma once

#include "stdafx.h"

class Button
{
public:
	int ID; // ID used to identify the functionality of the button. 0 = Main Menu, 1 = Play Computer, 2 = Play Local.
	wchar_t *Text;
	int X;
	int Y;
	int Width;
	int Height;

	Button();
	void Process_Button_Click();
	void Add_Button_To_Array();
};

extern Button *Buttons;
extern int Size_Of_Button_Array;

void Create_Button(int, wchar_t[], int, int);
void Create_Dynamically_Positioned_Button(int, wchar_t[]);
void Delete_All_Buttons();