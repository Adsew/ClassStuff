#include <iostream>
#include <string>

//
// Function overloading.
//
// There are four functions called 'min'
// but their parameter lists are different.
//
// Overloading can also be applied to methods of a class.
//

// minimum of two ints
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

// minimum of three ints
int min(int a, int b, int c)
{
	return min(a, min(b, c));
}

// minimum of two doubles
double min(double a, double b)
{
	if (a < b)
		return a;
	else
		return b;
}

std::string min(std::string a, std::string b) {

    if (a < b) {
        return a;
    }
    return b;
}

int main()
{
	int i1 = 3;
	int i2 = 5;
	int i3 = -1;
	
	std::cout << "The minimum of " << i1 << " and " << i2
		<< " is " << min(i1, i2) << std::endl;
	
	std::cout << "The minimum of " << i1 << ", " << i2 << ", and " << i3
		<< " is " << min(i1, i2, i3) << std::endl;

	double d1 = 3.3;
	double d2 = 5.1;

	std::cout << "The minimum of " << d1 << " and " << d2
		<< " is " << min(d1, d2) << std::endl;

	std::string s1 = "ABC";
	std::string s2 = "DEF";

	std::cout << "The minimum of " << s1 << " and " << s2
		<< " is " << min(s1, s2) << std::endl;


}
