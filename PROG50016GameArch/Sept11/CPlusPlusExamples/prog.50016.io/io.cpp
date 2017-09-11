#include <iostream>

int main()
{
	std::cout << "Hello, world!\n";

	// declare some basic variables of different types...
	char c = 'C';
	const char *msg = "Here is some stuff";
	int x = 17;
	float y = 123.4f;
	double pi = 3.14159265;

	// ...and print them out
	std::cout << msg << std::endl;
	std::cout << c << "++" << std::endl;
	std::cout << x << ", " << y << ", " << pi << std::endl;

	// declare an integer array
	int arr[5] = { 0, 1, 2, 3, 4 };

	// note: c++ allows declaring the counter variable in the for loop body
	for (int i = 0; i != 5; ++i ) 
		std::cout << arr[i] << ' ';
	std::cout << std::endl;

	std::cout << std::endl << "Enter two numbers:" << std::endl;

	float f1, f2;

	// read two numbers from standard input
	std::cin >> f1 >> f2;

	// print the numbers and their sum
	std::cout << f1 << " + " << f2 << " = " << (f1 + f2) << std::endl;

	return 0;
}
