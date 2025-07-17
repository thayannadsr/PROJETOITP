#ifndef GERARIMAGEM_H
#define GERARIMAGEM_H
#include <iostream>
using namespace std;

class GerarMapa {
public:
    int tamanho;
    float rugosidade;
    int** matrizAlturas;

    GerarMapa(int N, float r);

    void gerarMatrizMapa();
    void desalocarMatriz();
    void exibirValoresMapaAltura();
    int consultarMatrizAlturas(int x, int y);
    int consultarTamanho();
    void criarMapa(GerarMapa m);
};

#endif