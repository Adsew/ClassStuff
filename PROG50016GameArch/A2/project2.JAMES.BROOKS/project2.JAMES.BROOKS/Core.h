#ifndef CORE_H
#define CORE_H

/*
Student: James Brooks
Class: Game Architecture

File: Core.h

Description: Precompiled header for the common files and support macros.
*/


// Basic standard libraries

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <time.h>
#include <functional>
#include <memory>


// Extra libraries

#include "FileSystem.h"


// Easy debug output

#ifdef _DEBUG
    #define LOG(__out__) std::cout << __out__ << std::endl;
#else
    #define LOG(__out__)
#endif


#endif // !CORE_H
