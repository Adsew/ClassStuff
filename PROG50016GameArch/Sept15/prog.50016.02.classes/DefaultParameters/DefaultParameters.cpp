#include <iostream>

//
// Function prototype: specify default values for parameters a, b, and c.
//
// This function returns a*x^2 + b*x + c
//
double ComputeQuadratic(double x, double a = 0, double b = 0, double c = 0);

int main()
{
	double x = 2;

	//
	// There is only one function called ComputeQuadratic,
	// but here we use it in three different ways.
	//
	std::cout << ComputeQuadratic(x) << std::endl;             // 0*x*x + 0*x + 0 = 0
	std::cout << ComputeQuadratic(x, 2) << std::endl;          // 2*x*x + 0*x + 0 = 8
	std::cout << ComputeQuadratic(x, 2, 3) << std::endl;       // 2*x*x + 3*x + 0 = 14
	std::cout << ComputeQuadratic(x, 2, 3, 4) << std::endl;    // 2*x*x + 3*x + 4 = 18
}


//
// Function definition: default values NOT specified again!
//
double ComputeQuadratic(double x, double a, double b, double c)
{
	return a*x*x + b*x + c;
}
