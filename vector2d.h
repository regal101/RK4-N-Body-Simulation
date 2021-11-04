#pragma once
#include <string>
#include <vector>

struct vector2d
{
	double x;
	double y;

	vector2d operator*(vector2d a)
	{
		return vector2d{ x * a.x, y * a.y};
	}

	vector2d operator*(double a)
	{
		return vector2d{ x * a, y * a};
	}

	vector2d operator/(vector2d a)
	{
		return vector2d{ x / a.x, y / a.y};
	}

	vector2d operator/(double a)
	{
		return vector2d{ x / a, y / a};
	}

	vector2d operator+(vector2d a)
	{
		return vector2d{ x + a.x, y + a.y};
	}

	vector2d operator+=(const vector2d& a)
	{
		x += a.x;
		y += a.y;
		return vector2d{ x, y};
	}

	vector2d operator-(vector2d a)
	{
		return vector2d{ x - a.x, y - a.y};
	}
};