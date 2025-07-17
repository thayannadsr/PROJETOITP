#ifndef COR_H
#define COR_H

#include <iostream>
using namespace std;

class Cor {
    public:
    unsigned char r, g, b;

    Cor() : r(0), g(0), b(0) {}
    Cor (unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b) {}
};

#endif