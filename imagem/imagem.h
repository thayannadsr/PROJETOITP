#include <iostream>
#include "./paleta/paleta.h"

using namespace std;
#ifndef IMAGEM_H
#define IMAGEM_H

class Imagem {
    int largura;
    int altura;
    Cor** pixel;

    public:
    Imagem(int alargura, int aaltura);
    ~Imagem();
    
};

#endif