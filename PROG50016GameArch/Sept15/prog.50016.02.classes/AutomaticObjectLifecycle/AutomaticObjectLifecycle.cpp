#include <iostream>
#include <string>

//
// A class that prints messages out of its constructor and destructor.
// Useful to study object lifecycle.
//
class VerboseObject 
{
    std::string mName;

public:
    // constructor
    VerboseObject(std::string name)
    {
        mName = name;
        std::cout << "*** Creating " << mName << std::endl;
    }

    // destructor
    ~VerboseObject()
    {
        std::cout << "*** Destroying " << mName << std::endl;
    }

    void greet() const
    {
        std::cout << mName << " says hi" << std::endl;
    }
};

int main()
{
    VerboseObject jim("Jim");
    VerboseObject sally("Sally");

    std::cout << "--- Entering loop ---" << std::endl;
    for (int i = 0; i < 3; i++) 
	{
        jim.greet();

        VerboseObject bubba("Bubba");
        bubba.greet();

        sally.greet();

        // end of for-loop scope; destructor called for bubba
    }
    std::cout << "--- Finishing loop ---" << std::endl;

    // end of main; destructors called for sally and jim
}
