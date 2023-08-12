#pragma once

#include "studio.h"
#include "cvector.h"
#include "cmatrix.h"
#include "centity.h"

#pragma once
#include "../util/memory.h"

typedef uintptr_t DrawModelResults_t;



// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/public/istudiorender.h#L201
class CStudioHdr;
//class IClientRenderable;
class DrawModelInfo_t
{
public:
	CStudioHdr* studioHdr;
	void* hardwareData;
	std::int32_t decals;
	std::int32_t skin;
	std::int32_t body;
	std::int32_t hitboxSet;
	IClientRenderable* renderable;
};

// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/public/istudiorender.h#L324
class IMaterial;
class IStudioRender
{
public:
	enum
	{
		STUDIORENDER_DRAW_ENTIRE_MODEL = 0,
		STUDIORENDER_DRAW_OPAQUE_ONLY = 0x01,
		STUDIORENDER_DRAW_TRANSLUCENT_ONLY = 0x02,
		STUDIORENDER_DRAW_GROUP_MASK = 0x03,
		STUDIORENDER_DRAW_NO_FLEXES = 0x04,
		STUDIORENDER_DRAW_STATIC_LIGHTING = 0x08,
		STUDIORENDER_DRAW_ACCURATETIME = 0x10,		// Use accurate timing when drawing the model.
		STUDIORENDER_DRAW_NO_SHADOWS = 0x20,
		STUDIORENDER_DRAW_GET_PERF_STATS = 0x40,
		STUDIORENDER_DRAW_WIREFRAME = 0x80,
		STUDIORENDER_DRAW_ITEM_BLINK = 0x100,
		STUDIORENDER_SHADOWDEPTHTEXTURE = 0x200,
		STUDIORENDER_UNUSED = 0x400,
		STUDIORENDER_SKIP_DECALS = 0x800,
		STUDIORENDER_MODEL_IS_CACHEABLE = 0x1000,
		STUDIORENDER_SHADOWDEPTHTEXTURE_INCLUDE_TRANSLUCENT_MATERIALS = 0x2000,
		STUDIORENDER_NO_PRIMARY_DRAW = 0x4000,
		STUDIORENDER_SSAODEPTHTEXTURE = 0x8000,
	};

	enum EOverrideType : std::int32_t
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
		OVERRIDE_SELECTIVE,
		OVERRIDE_SSAO_DEPTH_WRITE,
	};

	constexpr void SetColorModulation(const float* color) noexcept
	{
		memory::Call<void>(this, 27, color);
	}

	constexpr void SetAlphaModulation(const float alpha) noexcept
	{
		memory::Call<void>(this, 28, alpha);
	}

	constexpr void ForcedMaterialOverride(IMaterial* material, const std::int32_t type = OVERRIDE_NORMAL, const std::int32_t index = -1) noexcept
	{
		memory::Call<void>(this, 33, material, type, index);
	}

	constexpr bool IsForcedMaterialOverride() noexcept
	{
		return memory::Call<bool>(this, 34);
	}

	virtual void DrawModel(DrawModelResults_t* pResults, const DrawModelInfo_t& info,
		matrix3x4_t* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, const vec3& modelOrigin, int flags = STUDIORENDER_DRAW_ENTIRE_MODEL)
	{
		return memory::Call<void>(this, 29, pResults, info, pBoneToWorld, pFlexWeights, pFlexDelayedWeights, modelOrigin, flags);
	}
};	
