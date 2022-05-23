#ifndef FMATH_H
#define FMATH_H

#include <algorithm>

template <class _Tx>
inline _Tx s_clamp(const _Tx& x, const _Tx& min, const _Tx& max)
{
	return std::min(std::max(x, min), max);
}

struct Point
{
	Point()
	{
	}

    Point(int x, int y)
        : x(x)
        , y(y)
    {
    }

    Point(const Point& other)
        : x(other.x)
        , y(other.y)
    {
    }

	Point operator+(const Point& rhs)
	{
		return Point(rhs.x + x, rhs.y + y);
	}

	Point operator*(const int& scalar)
	{
		return Point(scalar * x, scalar * y);
	}

	bool operator==(const Point& rhs)
	{
		return rhs.x == x && rhs.y == y;
	}

	static Point clamp_screen(const Point& point)
	{
		return Point(s_clamp<int>(point.x, 0, 4), s_clamp<int>(point.y, 0, 4));
	}

    int x;
    int y;
};


#endif