#pragma once

#include "centity.h"

class CBaseViewModel
{
public:

	constexpr int* GetModelIndexPointer()
	{
		return (int*)(this + offsets::m_nModelIndex);
	}


};

class CBaseHandle
{
public:


};

class IClientEntityList
{
public:
	CEntity* GetClientEntityFromID(int index)
	{
		return memory::Call<CEntity*>(this, 3, index);
	}

	CEntity* GetClientEntityFromHandle(int hEnt)
	{
		return memory::Call<CEntity*>(this, 4, hEnt);
	}
	
};