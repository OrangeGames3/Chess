#pragma once

#include "stdafx.h"
#include "d2d1_1.h"
#include "d3d11_4.h"
#include "Interface_Wrapper.h"
#include "dwrite.h"

// DirectX resources required for rendering.

extern Interface_Wrapper <IDXGISwapChain1>Swap_Chain;
extern Interface_Wrapper <ID2D1DeviceContext>Device_Context;
extern Interface_Wrapper <IDWriteTextFormat>DWrite_Text_Format;
extern Interface_Wrapper <ID2D1SolidColorBrush>Brush;
extern Interface_Wrapper <ID2D1Bitmap>Chess_Piece_Images[12];

extern void Create_Resources();