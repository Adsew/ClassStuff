#pragma once


class Circle
{
private:

    double radius;

public:

    Circle();

    Circle(double radius);

    void setRadius(double radius);

    double getRadius() const;

    ~Circle();
};
