#include "MyString.h"

#include <iostream>

int main()
{
    MyString s1;
    MyString s2("foo");

    std::cout << "--- Initial state ---" << std::endl;
    
    std::cout << "s1: " << s1.c_str() << std::endl;
    std::cout << "s2: " << s2.c_str() << std::endl;

    std::cout << "--- Appending \"bar\" ---" << std::endl;

    s1.append("bar");
    s2.append("bar");
    
    std::cout << "s1: " << s1.c_str() << std::endl;
    std::cout << "s2: " << s2.c_str() << std::endl;

    // s1 and s2 are going out of scope, so their destructors get called here
}
