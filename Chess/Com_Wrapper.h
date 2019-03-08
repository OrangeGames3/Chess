#pragma once

#include "stdafx.h"

class Com_Wrapper // Wrapper class to automatically initalise and uninitialise the COM library.
{
public:
	Com_Wrapper();
	~Com_Wrapper(); // Function called automatically when object goes out of scope to uninitialise the COM library.
};