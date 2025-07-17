#ifndef COR_H
#define COR_H

#include <iostream>
using namespace std;

class Cor {
    public:
    unsigned char r, g, b;

    Cor();  
    Cor(unsigned char _r, unsigned char _g, unsigned char _b);
};

#endif