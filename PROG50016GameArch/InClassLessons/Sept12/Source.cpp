
#include <iostream>
#include <time.h>

void sizeofLook() {

    std::cout << "bool " << sizeof(bool) << "\n";
    std::cout << "char " << sizeof(char) << "\n";
    std::cout << "short " << sizeof(short) << "\n";
    std::cout << "int " << sizeof(int) << "\n";
    std::cout << "float " << sizeof(float) << "\n";
    std::cout << "double " << sizeof(double) << "\n";
    std::cout << "long " << sizeof(long) << "\n";
    std::cout << "longlong " << sizeof(long long) << "\n";

    std::cout << "\n";
}

void randomgenerator() {

    int num[10];
    int i = 0;

    srand((unsigned)time(0));

    for (int i = 0; i < sizeof(num) / sizeof(int); i++) {

        num[i] = (rand() % 100) + 1;
    }

    for (int i = 0; i < sizeof(num) / sizeof(int); i++) {

        std::cout << num[i] << " ";
    }
    
    std::cout << "\n";
}

int main(int argc, char *argv[]) {

    sizeofLook();

    randomGenerator();

    return 0;
}