#pragma once

#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "tinyxml2.h"
using namespace tinyxml2;

#define ASSERT(_condition_) if (_condition_){ throw exception(); }

// Defined in debug mode;
#ifdef _DEBUG
    #define LOG(__out__) std::cout << __out__ << std::endl;
#else
    #define LOG(__out__)
#endif
