#ifndef __POINT_H__

#define __POINT_H__

class Point
{

public:
	float x;
	float y;

public:
	Point(float _x, float _y)
	{
        setPoint(_x, _y);
	};

	void setPoint(const float _x, const float _y);
};

#endif