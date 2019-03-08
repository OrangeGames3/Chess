#pragma once

#include "stdafx.h"

template <typename Type>
class Interface_Wrapper // Wrapper class used to follow RAII (Resource Acquisition Is Initialisation) programming technique to help prevent memory leaks.
{
public:
	Type *This_Interface; // The new resource that has been acquired.

	~Interface_Wrapper(); // Function to be called automatically when the object goes out of scope.
	void Release_Interface(); // Releases the memory acquired by the new resource.
};

template<typename Type>
Interface_Wrapper<Type>::~Interface_Wrapper()
{
	Release_Interface();
}

template<typename Type>
void Interface_Wrapper<Type>::Release_Interface()
{
	if (This_Interface != nullptr)
	{
		This_Interface->Release(); // Free the memory acquired by the resource.
		This_Interface = nullptr;
	}
}