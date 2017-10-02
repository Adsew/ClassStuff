
#include "Object.h"
#include "Component.h"


int main(int argc, const char *argv[]) {

    Object *ptrcomp = new Component(2);
    ptrcomp->initialize();

    delete ptrcomp;

    return -1;
}