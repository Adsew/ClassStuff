#include "MyString.h"

#include <cstdlib>  // malloc, realloc, and free
#include <cstring>  // strlen, strcpy, and strcat

MyString::MyString()
{
    // create an empty string (just a nul terminator)
    mStr = (char*)std::malloc(sizeof(char));
    mStr[0] = '\0';
}

MyString::MyString(const char* arg)
{
    // check if argument is a NULL pointer
    if (arg == NULL) {
        // create empty string
        mStr = (char*)std::malloc(sizeof(char));
        mStr[0] = '\0';
    } else {
        // create copy of argument
        mStr = (char*)std::malloc(std::strlen(arg) + 1);
        std::strcpy(mStr, arg);
    }
}

MyString::~MyString()
{
    // release memory
    std::free(mStr);
}

void MyString::append(const char* arg)
{
    if (arg != NULL) {
        // reallocate string
        char* newStr = (char*)std::realloc(mStr, std::strlen(mStr) + std::strlen(arg) + 1);
        if (newStr != NULL) {
            // if reallocation succeeded, point mStr to new buffer
            mStr = newStr;
            // append argument
            std::strcat(mStr, arg);
        }
    }
}

const char* MyString::c_str() const
{
    return mStr;
}
