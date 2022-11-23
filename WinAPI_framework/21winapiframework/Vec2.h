#pragma once
#include <assert.h>
class Vec2
{
public:
	float x;
	float y;
public:
	Vec2();
	~Vec2();
	Vec2(int _x, int _y);
	Vec2(long _x, long _y);
	Vec2(float _x, float _y);
	Vec2(POINT _pt);
	Vec2& Normalize();
	float Length();
public:
	Vec2 operator + (Vec2 _Oher)
	{
		return Vec2(x + _Oher.x, y + _Oher.y);
	}
	Vec2 operator - (Vec2 _Oher)
	{
		return Vec2(x - _Oher.x, y - _Oher.y);
	}
	Vec2 operator * (Vec2 _Oher)
	{
		return Vec2(x * _Oher.x, y * _Oher.y);
	}
	Vec2 operator / (Vec2 _Oher)
	{
		assert((_Oher.x == 0.f || _Oher.y == 0.f));
		return Vec2(x / _Oher.x, y / _Oher.y);
	}
};

