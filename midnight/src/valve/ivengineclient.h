#pragma once
#include "../util/memory.h"

#include "cvector.h"
#include "cmatrix.h"

class IVEngineClient
{
public:
	constexpr void GetScreenSize(std::int32_t& width, std::int32_t& height) noexcept
	{
		memory::Call<void>(this, 5, std::ref(width), std::ref(height));
	}

	// returns index of local player
	constexpr std::int32_t GetLocalPlayerIndex() noexcept
	{
		return memory::Call<std::int32_t>(this, 12);
	}

	constexpr void SetViewAngles(const vec3& viewAngles) noexcept
	{
		memory::Call<void, const vec3&>(this, 19, viewAngles);
	}

	// returns true if in-game
	constexpr bool IsInGame() noexcept
	{
		return memory::Call<bool>(this, 26);
	}

	constexpr const matrix4x4_t& WorldToScreenMatrix() noexcept
	{
		return memory::Call<const matrix4x4_t&>(this, 37);
	}

	constexpr void ClientCmd(const char* szCmdString)
	{
		memory::Call<void>(this, 114, szCmdString, true);
	}
};
