#include "stdafx.h"
#include "d3d11_4.h"
#include "d2d1_1.h"
#include "wincodec.h"
#include "Interface_Wrapper.h"
#include "Resources.h"
#include "Chess.h"
#include "Chess_Piece.h"
#include "Tile.h"
#include "Chess_Piece_Type.h"
#include "dwrite.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dwrite.lib")

Interface_Wrapper <IDXGISwapChain1>Swap_Chain;
Interface_Wrapper <ID2D1DeviceContext>Device_Context;
Interface_Wrapper <IDWriteTextFormat>DWrite_Text_Format;
Interface_Wrapper <ID2D1SolidColorBrush>Brush;
Interface_Wrapper <ID2D1Bitmap>Chess_Piece_Images[12];

void Create_Resources()
{
	// This whole function just initialises all the objects required for DirectX rendering.

	for (int Interface_Count = 11; Interface_Count >= 0; Interface_Count--)
	{
		Chess_Piece_Images[Interface_Count].Release_Interface();
	}

	Brush.Release_Interface();
	DWrite_Text_Format.Release_Interface();
	Device_Context.Release_Interface();
	Swap_Chain.Release_Interface();

	const D3D_FEATURE_LEVEL Feature_Levels[]{ D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0, D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1 };
	D3D_FEATURE_LEVEL Feature_Level;
	Interface_Wrapper <ID3D11Device>D3D_Device_Temp;

	HRESULT D3D11CreateDevice_Return = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT, Feature_Levels, 9, D3D11_SDK_VERSION, &D3D_Device_Temp.This_Interface, &Feature_Level, nullptr);

	Interface_Wrapper <ID3D11Device5>D3D_Device;
	HRESULT QueryInterface_Return{ D3D_Device_Temp.This_Interface->QueryInterface(__uuidof(ID3D11Device5), reinterpret_cast<void**>(&D3D_Device.This_Interface)) };

	Interface_Wrapper <IDXGIDevice>DXGI_Device;
	HRESULT QueryInterface_Return2{ D3D_Device.This_Interface->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DXGI_Device.This_Interface)) };

	Interface_Wrapper <IDXGIAdapter>Adapter;
	HRESULT GetParent_Return{ DXGI_Device.This_Interface->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&Adapter.This_Interface)) };

	Interface_Wrapper <IDXGIFactory2>DXGI_Factory;
	HRESULT GetParent_Return2{ Adapter.This_Interface->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&DXGI_Factory.This_Interface)) };

	DXGI_SAMPLE_DESC Sample_Desc;
	Sample_Desc.Count = 1;
	Sample_Desc.Quality = 0;

	DXGI_SWAP_CHAIN_DESC1 Swap_Chain_Desc;
	Swap_Chain_Desc.Width = 0;
	Swap_Chain_Desc.Height = 0;
	Swap_Chain_Desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	Swap_Chain_Desc.Stereo = FALSE;
	Swap_Chain_Desc.SampleDesc = Sample_Desc;
	Swap_Chain_Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	Swap_Chain_Desc.BufferCount = 2;
	Swap_Chain_Desc.Scaling = DXGI_SCALING_NONE;
	Swap_Chain_Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	Swap_Chain_Desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	Swap_Chain_Desc.Flags = 0;

	HRESULT CreateSwapChainForHwnd_Return{ DXGI_Factory.This_Interface->CreateSwapChainForHwnd(D3D_Device.This_Interface, Main_Window_Handle, &Swap_Chain_Desc, nullptr, nullptr, &Swap_Chain.This_Interface) };

	Interface_Wrapper <IDXGISurface>Surface;
	HRESULT GetBuffer_Return{ Swap_Chain.This_Interface->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(&Surface.This_Interface)) };

	Interface_Wrapper <ID2D1Factory1>D2D_Factory;

	D2D1_FACTORY_OPTIONS Factory_Options;
	Factory_Options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

	HRESULT D2D1CreateFactory_Return{ D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &Factory_Options, reinterpret_cast<void**>(&D2D_Factory.This_Interface)) };

	Interface_Wrapper <ID2D1Device>D2D_Device;
	HRESULT CreateDevice_Return{ D2D_Factory.This_Interface->CreateDevice(DXGI_Device.This_Interface, &D2D_Device.This_Interface) };

	HRESULT CreateDeviceContext_Result{ D2D_Device.This_Interface->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &Device_Context.This_Interface) };

	D2D1_PIXEL_FORMAT PixelFormat;
	PixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	PixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;

	D2D1_BITMAP_PROPERTIES1 Bitmap_Properties;
	Bitmap_Properties.pixelFormat = PixelFormat;
	Bitmap_Properties.dpiX = 90.0F;
	Bitmap_Properties.dpiY = 90.0F;
	Bitmap_Properties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

	Interface_Wrapper <ID2D1Bitmap1>Surface_Bitmap;
	HRESULT CreateBitmapFromDxgiSurface_Return{ Device_Context.This_Interface->CreateBitmapFromDxgiSurface(Surface.This_Interface, nullptr, &Surface_Bitmap.This_Interface) };

	Device_Context.This_Interface->SetTarget(Surface_Bitmap.This_Interface);

	Interface_Wrapper <IDWriteFactory>DWrite_Factory;
	HRESULT DWriteCreateFactory_Return{ DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&DWrite_Factory.This_Interface)) };

	HRESULT CreateTextFormat_Return{ DWrite_Factory.This_Interface->CreateTextFormat(L"Arial", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 24.0F, L"en-gb", &DWrite_Text_Format.This_Interface) };

	DWrite_Text_Format.This_Interface->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	DWrite_Text_Format.This_Interface->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	D3DCOLORVALUE White;
	White.r = 1.0F;
	White.g = 1.0F;
	White.b = 1.0F;
	White.a = 1.0F;

	D2D1_MATRIX_3X2_F Matrix;
	Matrix._11 = 1.0F;
	Matrix._12 = 0.0F;
	Matrix._21 = 0.0F;
	Matrix._22 = 1.0F;
	Matrix._31 = 0.0F;
	Matrix._32 = 0.0F;

	D2D1_BRUSH_PROPERTIES Brush_Properties;
	Brush_Properties.opacity = 1.0F;
	Brush_Properties.transform = Matrix;

	HRESULT CreateSolidColorBrush_Return{ Device_Context.This_Interface->CreateSolidColorBrush(White, Brush_Properties, &Brush.This_Interface) };

	const wchar_t *Image_Names[]{ L"../Chess/Black Bishop.png", L"../Chess/Black King.png", L"../Chess/Black Knight.png", L"../Chess/Black Pawn.png", L"../Chess/Black Queen.png", L"../Chess/Black Rook.png", L"../Chess/White Bishop.png", L"../Chess/White Knight.png", L"../Chess/White King.png", L"../Chess/White Pawn.png", L"../Chess/White Queen.png", L"../Chess/White Rook.png" };

	for (int Image_Count = 0; Image_Count < 12; Image_Count++)
	{
		Interface_Wrapper <IWICImagingFactory>WIC_Imaging_Factory;
		HRESULT CoCreateInstance_Return{ CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), reinterpret_cast<void**>(&WIC_Imaging_Factory.This_Interface)) };

		Interface_Wrapper <IWICBitmapDecoder>Bitmap_Decoder;
		HRESULT CreateDecoderFromFilename_Return{ WIC_Imaging_Factory.This_Interface->CreateDecoderFromFilename(Image_Names[Image_Count], nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &Bitmap_Decoder.This_Interface) };

		Interface_Wrapper <IWICBitmapFrameDecode>Bitmap_Frame_Decode;
		HRESULT GetFrame_Return{ Bitmap_Decoder.This_Interface->GetFrame(0, &Bitmap_Frame_Decode.This_Interface) };

		Interface_Wrapper <IWICFormatConverter>Format_Converter;
		HRESULT CreateFormatConverter_Return{ WIC_Imaging_Factory.This_Interface->CreateFormatConverter(&Format_Converter.This_Interface) };

		HRESULT Initialize_Return{ Format_Converter.This_Interface->Initialize(Bitmap_Frame_Decode.This_Interface, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 1.0F, WICBitmapPaletteTypeCustom) };

		HRESULT CreateBitmapFromWicBitmap_Return{ Device_Context.This_Interface->CreateBitmapFromWicBitmap(Format_Converter.This_Interface, nullptr, &Chess_Piece_Images[Image_Count].This_Interface) };
	}
}