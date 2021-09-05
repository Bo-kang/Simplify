#include "DouglasPeucker.h"




double GetLength( const Point &A, const Point &B )
{
	return sqrt( ((A.x - B.x)* (A.x - B.x)) + ((A.y + B.y)* (A.x - B.x)) );
}

/*
	@ From - https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
*/
double simplify::PerpendicularDistance( const Point & curPoint ,const Point & startPoint, const Point & endPoint )
{
	double numerator = abs ( ( ( endPoint.x - startPoint.x ) * ( startPoint.y - curPoint.y ) ) - ( ( startPoint.x - curPoint.x ) * ( endPoint.y - startPoint.y ) ) ) ;
	double denominator = sqrt( ( ( endPoint.x - startPoint.x) * (endPoint.x - startPoint.x) ) + ( (endPoint.y - startPoint.y) * (endPoint.y - startPoint.y) ) ) ;

	if (denominator == 0)
		return 0;

	return numerator / denominator ;
}


/*
	@ Desc : DouglasPeucker Polyline  Simplify logic using Recursive
	@ Author : Bo-kang (ebfks0301@gmail.com)
	@ Param1 : Target Polyline
	@ Param2 : Simplify Factor ( Epsilon )
	@ Param3 : Result 
	@ Return : true - Done  / false - Unknown Error
*/
bool simplify::DouglasPeucker_REC( const std::vector<Point > & polyLine, const int & epsilon, std::vector<Point>& result , int index , int end )
{
	double maxDistance = 0;
	int nextIndex = 0;

	if(end == -1)
		end = polyLine.size() - 1;

	for (int i = index + 1; i < end; i++)
	{
		// 현재의 직선을 저장해두고, 직선 ~ Point까지의 거리를 구하는 식으로 개선해볼 필요가 있음 (속도 증진이나 결과 도출에 차이가 있는 지 여부 확인 필요)
		int tmpDistance = PerpendicularDistance( polyLine[i], polyLine[index], polyLine[end] ) ;
		if (tmpDistance > maxDistance)
		{
			maxDistance = tmpDistance;
			nextIndex = i ;
		}
	}
	if (maxDistance > epsilon)
	{
		DouglasPeucker_REC( polyLine, epsilon, result, 0, nextIndex ) ;
		DouglasPeucker_REC( polyLine, epsilon, result, nextIndex, end ) ;
	}
	else
	{
		result.emplace_back(polyLine[index]);
		result.emplace_back(polyLine[end]);
	}
	return true;
}



/*
	@ Desc : DouglasPeucker Polyline  Simplify logic using Stack
	@ Author : Bo-kang (ebfks0301@gmail.com)
	@ Param1 : Target Polyline
	@ Param2 : Simplify Factor ( Epsilon )
	@ Param3 : Result
	@ Return : true - Done  / false - Unknown Error
*/
bool simplify::DouglasPeucker_Stack(const std::vector<Point>& polyLine, const int& epsilon, std::vector<Point>& result, int index, int end )
{
	double maxDistance = 0;
	std::stack<std::pair<int , int>> afStack;
	afStack.push(std::pair<int, int>(0, polyLine.size() - 1));

	int anchorIdx = 0;
	int floaterIdx = polyLine.size() - 1;

	while (!afStack.empty())
	{
		anchorIdx = afStack.top().first ;
		floaterIdx = afStack.top().second ;
		double curDistance = 0;
		double maxDistance = 0;
		int targIdx = 0;
		for (int i = anchorIdx; i < floaterIdx; i++)
		{
			curDistance = PerpendicularDistance(polyLine[i], polyLine[anchorIdx], polyLine[floaterIdx]);
			if (maxDistance < curDistance)
			{
				targIdx = i;
				maxDistance = curDistance;
			}
		}

		if (epsilon >= maxDistance)
		{
			result.push_back(polyLine[anchorIdx]);
			result.push_back(polyLine[floaterIdx]);
			afStack.pop();
		}
		else
		{
			afStack.pop();
			afStack.push(std::pair<int, int>(anchorIdx, targIdx));
			afStack.push(std::pair<int, int>(targIdx, floaterIdx));
		}
	}
	return true;
}