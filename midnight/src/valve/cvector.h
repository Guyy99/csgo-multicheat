#pragma once

#include <numbers>
#include <cmath>

constexpr float Deg2Rad(const float deg) noexcept
{
	return deg * (std::numbers::pi_v<float> / 180.f);
}

class vec3
{
public:
	constexpr vec3 operator-(const vec3& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr vec3 operator+(const vec3& other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr vec3 operator*(const float scale) const noexcept
	{
		return { x * scale, y * scale, z * scale };
	}

	constexpr vec3 operator/(const float scale) const noexcept
	{
		return { x / scale, y / scale, z / scale };
	}

	constexpr bool operator==(const vec3& other) const noexcept
	{
		if ((x == other.x) && (y == other.y) && (z == other.z)) return true;
		else return false;
	}

	constexpr vec3 Scale(float factor) const noexcept
	{
		return { x * factor, y * factor, z * factor };
	}

	// convert angles -> vector
	vec3 ToVector() const noexcept
	{
		return {
			std::cos(Deg2Rad(x)) * std::cos(Deg2Rad(y)),
			std::cos(Deg2Rad(x)) * std::sin(Deg2Rad(y)),
			-std::sin(Deg2Rad(x))
		};
	}

	inline vec3 ToAngle() const noexcept
	{
		return {
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f
		};
	}

public:
	float x{ };
	float y{ };
	float z{ };
};

struct vec2 {
	float x, y;
};

struct vec4 {
	float w, x, y, z;
};