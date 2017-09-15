// multiple inclusion guard
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"

//
// Circle class definition.
// - We want to move these methods to a C++ file
// - Only the method prototypes should be provided
//
class Circle : public Shape
{
	// instance variable
	double radius;

public:

	// no-arg constructor
	Circle()
	{
		radius = 0;
	}

	// parameterized constructor
	Circle(double radius)
	{
		this->radius = radius;
	}

	// a setter
	void setRadius(double radius)
	{
		this->radius = radius;
	}

	// a getter
	double getRadius() const
	{
		return radius;
	}
};

#endif  // end of multiple inclusion guard
