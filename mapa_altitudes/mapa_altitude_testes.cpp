#include <iostream>
#include "mapa_altitudes.cpp"
using namespace std;

int main() {
    MapaAltitudes mapa_teste(3, 0.5);
    mapa_teste.gerarMatrizMapa();
    mapa_teste.exibirValoresMapaAltura(); // corrigir erro de exibição
    mapa_teste.desalocarMatriz();
}
