#ifndef IMAGEM_H
#define IMAGEM_H

#include <iostream>
#include "../paleta/paleta.h"

using namespace std;

class Imagem {
    int largura;
    int altura;
    Cor** pixel;
    int max;

    public:
    string tipo;
    Imagem(int alargura, int aaltura, string atipo="P3", int mInt=255);
    void matrizImagem();
    void desalocarMatriz();
    Cor consultarPixel(int x, int y);
    void mudarPixel(int x, int y, char r, char g, char b);
    void exibirValoresPixelRGB();
    void escreverPPM(string nomeNovoPPM);
};

#endif