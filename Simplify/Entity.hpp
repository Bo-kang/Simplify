#pragma once

struct Point {
	double x;
	double y;

	Point()
	{
		x = 0;
		y = 0;
	}

	Point(const double &x, const double &y)
	{
		this->x = x;
		this->y = y;
	}
};