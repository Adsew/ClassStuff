#include <iostream>

#include "Circle.h"

Circle::Circle() {
    radius = 0;
}

Circle::Circle(double radius) {
    this->radius = radius;
}

void Circle::setRadius(double radius) {
    this->radius = radius;
}

double Circle::getRadius() const {
    return radius;
}

Circle::~Circle() {

    std::cout << "Circle " << radius << " has been destroyed!!\n";
}
