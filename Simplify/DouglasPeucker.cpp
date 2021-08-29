
#include <math.h>
#include <vector>
#include "Entity.hpp"


double GetLength( const Point &A, const Point &B )
{
	return sqrt( ((A.x - B.x)* (A.x - B.x)) + ((A.y + B.y)* (A.x - B.x)) );
}

/*
	@ From - https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
*/
double PerpendicularDistance( const Point & curPoint ,const Point & startPoint, const Point & endPoint )
{
	double numerator = abs ( ( ( endPoint.x - startPoint.x ) * ( startPoint.y - curPoint.y ) ) - ( ( startPoint.x - curPoint.x ) * ( endPoint.y - startPoint.y ) ) ) ;
	double denominator = sqrt( ( ( endPoint.x - startPoint.x) * (endPoint.x - startPoint.x) ) + ( (endPoint.y - startPoint.y) * (endPoint.y - startPoint.y) ) ) ;

	if (denominator == 0)
		return 0;

	return numerator / denominator ;
}


/*
	@ Desc : DouglasPeucker Polyline  Simplify logic using DFS
	@ Author : Bo-kang (ebfks0301@gmail.com)
	@ Param1 : Target Polyline
	@ Param2 : Simplify Factor ( Epsilon )
	@ Param3 : Result 
	@ Return : true - Done  / false - Unknown Error
*/
bool DouglasPeucker_DFS( const std::vector<Point> & polyLine, const int & epsilon, std::vector<Point>& result , int index = 0, int end = - 1 )
{
	double maxDistance = 0;
	int nextIndex = 0;

	if(end == -1)
		end = polyLine.size() - 1;

	for (int i = index + 1; i < end; i++)
	{
		// ������ ������ �����صΰ�, ���� ~ Point������ �Ÿ��� ���ϴ� ������ �����غ� �ʿ䰡 ���� (�ӵ� �����̳� ��� ���⿡ ���̰� �ִ� �� ���� Ȯ�� �ʿ�)
		int tmpDistance = PerpendicularDistance( polyLine[i], polyLine[index], polyLine[end] ) ;
		if (tmpDistance > maxDistance)
		{
			maxDistance = tmpDistance;
			nextIndex = i ;
		}
	}

	if (maxDistance > epsilon)
	{
		DouglasPeucker_DFS( polyLine, epsilon, result, 0, nextIndex ) ;
		DouglasPeucker_DFS( polyLine, epsilon, result, nextIndex, end ) ;
	}
	else
	{
		result.emplace_back(polyLine[index], polyLine[end]);
	}

	return true;
}