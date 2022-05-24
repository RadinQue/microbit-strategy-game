#ifndef FMATH_H
#define FMATH_H

#include <algorithm>
#include <cmath>

template <class _Tx>
inline _Tx s_clamp(const _Tx& x, const _Tx& min, const _Tx& max)
{
	return std::min(std::max(x, min), max);
}

template<class _Tx>
inline _Tx sqr(const _Tx& x)
{
	return x * x;
}

struct Point
{
	Point()
	{
	}

    Point(int8_t x, int8_t y)
        : x(x)
        , y(y)
    {
    }

    Point(const Point& other)
        : x(other.x)
        , y(other.y)
    {
    }

	Point operator+(const Point& rhs) const
	{
		return Point(rhs.x + x, rhs.y + y);
	}

	Point& operator+=(const Point& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Point operator*(const int& scalar) const
	{
		return Point(scalar * x, scalar * y);
	}

	bool operator==(const Point& rhs) const
	{
		return rhs.x == x && rhs.y == y;
	}

	static Point clamp_screen(const Point& point)
	{
		return Point(s_clamp<int8_t>(point.x, 0, 4), s_clamp<int8_t>(point.y, 0, 4));
	}

    int8_t x;
	int8_t y;
};

float inline dist(const Point& P1, const Point& P2)
{
	return sqrt(sqr(P2.x - P1.x) + sqr(P2.y - P1.y));
}


#endif