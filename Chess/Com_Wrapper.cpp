#include "stdafx.h"
#include "objbase.h"
#include "Com_Wrapper.h"

Com_Wrapper::Com_Wrapper()
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
}

Com_Wrapper::~Com_Wrapper()
{
	CoUninitialize();
}