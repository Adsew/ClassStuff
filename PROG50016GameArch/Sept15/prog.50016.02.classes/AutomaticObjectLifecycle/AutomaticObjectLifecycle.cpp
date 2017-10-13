#include <iostream>
#include <string>

//
// A class that prints messages out of its constructor and destructor.
// Useful to study object lifecycle.
//
class VerboseObject 
{
protected:
    
    std::string mName;

public:

    VerboseObject() {

        mName = "No Name Given";
        std::cout << "*** Creating default " << mName << std::endl;
    }

    // constructor
    VerboseObject(std::string name)
    {
        mName = name;
        std::cout << "*** Creating " << mName << std::endl;
    }

    // destructor
    virtual ~VerboseObject()
    {
        std::cout << "*** Destroying Verbose Object " << mName << std::endl;
    }

    virtual void greet() const
    {
        std::cout << mName << " says hi" << std::endl;
    }
};

class DerivedObject : public VerboseObject {

public:

    DerivedObject() {

        std::cout << "*** Creating derived " << mName << std::endl;
    }

    DerivedObject(std::string name) : VerboseObject(name) {

        std::cout << "*** Creating derived with name " << mName << std::endl;
    }

    ~DerivedObject() {

        std::cout << "*** Destroying Derived Object " << mName << std::endl;
    }

    void greet() const
    {
        std::cout << mName << " says hi derived" << std::endl;
    }
};

class Derived2Object : public DerivedObject {

public:

    Derived2Object() {

        std::cout << "*** Creating derived2 " << mName << std::endl;
    }

    Derived2Object(std::string name) : DerivedObject(name) {

        std::cout << "*** Creating derived2 with name " << mName << std::endl;
    }

    ~Derived2Object() {

        std::cout << "*** Destroying Derived2 Object " << mName << std::endl;
    }

    void greet() const
    {
        std::cout << mName << " says hi derived 2" << std::endl;
    }
};

int main()
{
    VerboseObject jim("Jim");
    DerivedObject *sally = NULL;
    sally = new Derived2Object("Sally");

    std::cout << "--- Entering loop ---" << std::endl;
    for (int i = 0; i < 3; i++) 
	{
        jim.greet();

        VerboseObject bubba("Bubba");
        bubba.greet();

        sally->greet();

        // end of for-loop scope; destructor called for bubba
    }
    std::cout << "--- Finishing loop ---" << std::endl;

    delete sally;
    // end of main; destructors called for sally and jim
}
