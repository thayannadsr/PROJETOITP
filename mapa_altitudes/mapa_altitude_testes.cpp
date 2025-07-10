#include <iostream>
#include "mapa_altitudes.cpp"
using namespace std;


int main() {
    MapaAltitudes mapa_teste(2, 0.5);
    mapa_teste.gerarMatrizMapa();
    // mapa_teste.exibirValoresMapaAltura();
    // cout << "\n";
    mapa_teste.algoritmoDiamonSquare(10, 5);
    mapa_teste.exibirValoresMapaAltura();
    // cout << mapa_teste.consultarMatrizAlturas(4, 4);
    mapa_teste.desalocarMatriz();
}
