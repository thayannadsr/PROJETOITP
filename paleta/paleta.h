#ifndef PALETA_H
#define PALETA_H

#include <iostream>
#include <vector>
using namespace std;

struct Cor {
public:
    unsigned char r, g, b;

    Cor(unsigned char _r, unsigned char _g, unsigned char _b);
    Cor() : r(0), g(0), b(0) {}
};

class Paleta {
public:
    int quantidade;
    vector<Cor> cores;
    vector<int> valores;

    Paleta(int q, vector<Cor> c, vector<int> v);

    vector<int> ordenarValores(vector<int> v);

    void escreverPaleta(string nomeNovaPaleta);

    Paleta lerPaleta(string nome_paleta);

    Cor consultarCor(int n);
};

#endif