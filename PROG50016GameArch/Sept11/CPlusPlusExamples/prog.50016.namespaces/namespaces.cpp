#include <iostream>

// create a namespace for 2d graphics stuff
namespace Graphics2D
{
	struct Point {
		float x, y;
	};

	void Greeting()
	{
		std::cout << "Hello, 2D!" << std::endl;
	}
}

// create a namespace for 3d graphics stuff
namespace Graphics3D
{
	struct Point {       // no name clash with Graphics2D Point class
		float x, y, z;
	};

	void Greeting()
	{
		std::cout << "Hello, 3D!" << std::endl;
	}
}

//
// The main function must be defined in the global namespace
//
int main()
{

	// Not working but we want to use the Graphics2D.... 
	Graphics2D::Point p1;
    Graphics2D::Point p2;
    Graphics2D::Greeting();
    Graphics2D::Greeting();

	// Not working but we want to use the Graphics3D.... 
    Graphics3D::Point p3;
    Graphics3D::Point p4;
    Graphics3D::Greeting();
    Graphics3D::Greeting();

	// I don't like using namespaces before can you fix me to use Graphics3D
    using namespace Graphics3D;
    Point p5;
    Graphics2D::Greeting();             // uses Graphics2D::Greeting

	return 0;
}
