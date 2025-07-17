#include <iostream>
#include "gerar_imagem.cpp"
using namespace std;


int main() {
    GerarMapa mapa_teste(2, 0.5);
    mapa_teste.gerarMatrizMapa();
    mapa_teste.exibirValoresMapaAltura();
    cout << "\n";

    mapa_teste.matrizAlturas[0][0] = 33;
    mapa_teste.matrizAlturas[1][1] = 33;
    mapa_teste.matrizAlturas[3][4] = 40;
    mapa_teste.criarMapa(mapa_teste);
    // mapa_teste.exibirValoresMapaAltura();
    // cout << mapa_teste.consultarMatrizAlturas(4, 4);
    mapa_teste.desalocarMatriz();
}
