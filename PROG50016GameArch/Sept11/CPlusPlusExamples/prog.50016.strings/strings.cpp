#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s1 = "test";
	string s2 = s1;	// copy a string (no need for strcpy!)

	s2[0] = 'j';	// subscript operator is allowed

	// s1 and s2 are separate objects (changing s2 didn't change s1)
	cout << "s1 = '" << s1 << "'" << endl;
	cout << "s2 = '" << s2 << "'" << endl;

	// getting the C-style string from std::string
	string cppstyle = "Hello";
	const char *cstyle = cppstyle.c_str();	// const means cannot be modified

	cout << "Doin' it C-style: " << cstyle << endl;

	// reading strings
	cout << "Enter two strings:" << endl;
	cin >> s1 >> s2;

	// string comparisons (no more strcmp!)
	if (s1 == s2)
		cout << s1 << " is equal to " << s2 << endl;
	if (s1 < s2)
		cout << s1 << " is smaller than " << s2 << endl;
	if (s1 > s2)
		cout << s1 << " is bigger than " << s2 << endl;

	// string concatenation (no more strcat!)
	cout << s1 << " + " << s2 << " is " << (s1 + s2) << endl;

	return 0;
}
