#ifndef __POINT_H__

#define __POINT_H__

#include <cmath>

class Point
{

public:
	float x;
	float y;

public:
	Point() :
		x(0.0f),
		y(0.0f)
	{
	}

	Point(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}

	void setPoint(const float _x, const float _y, const float _z);

	static float calculateDistance(Point p1, Point p2)
	{
		return (float)sqrt( ((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
	}
};

#endif