#ifndef PALETA_H
#define PALETA_H

#include <iostream>
#include <vector>
#include "cor.h"
using namespace std;


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