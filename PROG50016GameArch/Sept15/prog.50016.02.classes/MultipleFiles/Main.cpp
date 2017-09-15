#include "Shape.h"
#include "Circle.h"

#include <iostream>


//Example using ifdef to get rid of testing outputs

#define DEBUG false

#ifdef DEBUG
#define LOG(value)  std::cout << value << "\n";
#else
#define LOG(value)
#endif



int main()
{
	double value = 1.0472;

	Shape sp;		// a usless shape
    Circle c1;      // c1 gets initialized using default constructor
    Circle c2(17);  // c2 gets initialized using parameterized constructor

#if DEBUG
    LOG("--- initial state ---");
#endif
    std::cout << "c1 radius = " << c1.getRadius() << std::endl;
    std::cout << "c2 radius = " << c2.getRadius() << std::endl;

    std::cout << "--- setting c1 radius to 42 ---\n";
    c1.setRadius(42);
    std::cout << "c1 radius = " << c1.getRadius() << std::endl;

    std::cout << "--- setting c2 radius to 99 through a pointer ---\n";
    Circle* p = &c2;   // Circle pointer that holds the address of c2
    p->setRadius(99);  // use '->' instead of '.' with pointers
    std::cout << "c2 radius = " << c2.getRadius() << std::endl;
}
