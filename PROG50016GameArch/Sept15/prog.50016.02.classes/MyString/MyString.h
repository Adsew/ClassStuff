#ifndef SMART_STRING_H__
#define SMART_STRING_H__

//
// a string class tha manages its own memory
//
class MyString {

    char* mStr;                    // pointer to dynamically allocated string contents

public:
    MyString();                    // constructor that creates an empty string
    MyString(const char* arg);     // constructor that creates a copy of its argument

    ~MyString();                   // destructor that deallocates string storage

    void append(const char* arg);  // a method that appends string contents

    const char* c_str() const;     // a method that returns a pointer to the string contents
                                   // - The return type "const char*" means that the method returns
                                   //   a character pointer but the contents cannot be modified.
                                   // - The "const" at the end of the method signature means that
                                   //   calling this method will not cause the object to be modified.
};

#endif
