#pragma once

#include <cstdint>

class CClientClass
{
public:
	void* createFn;
	void* createEventFn;
	char* networkName;
	void* table;
	CClientClass* next;
	std::int32_t classID;
};
