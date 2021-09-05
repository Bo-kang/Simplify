#pragma once

#include <math.h>
#include <vector>
#include <stack>
#include "Entity.hpp"

namespace simplify 
{
	bool DouglasPeucker_REC(const std::vector<Point >& polyLine, const int& epsilon, std::vector<Point>& result, int index = 0, int end = -1);
	bool DouglasPeucker_Stack(const std::vector<Point>& polyLine, const int& epsilon, std::vector<Point>& result, int index = 0, int end = -1);
	double PerpendicularDistance(const Point& curPoint, const Point& startPoint, const Point& endPoint);
}