#include <iostream>
#include "gerar_imagem.cpp"
using namespace std;


int main() {
    GerarMapa mapa_teste(7, 0.5);

    vector<int> valores {0, 10, 20, 30, 40, 45, 65, 60, 70, 100};
    Paleta predefinida(10, {
        {10, 20, 40}, {20, 40, 80}, {30, 60, 250}, {255, 229, 193}, {255, 229, 153}, {130, 135, 40}, {130, 162, 40}, {90, 147, 50}, {50, 160, 60}, {50, 131, 60}
    }, valores);
    // vector<int> valores {0, 9, 18, 27, 36, 44, 52, 60, 68, 76, 84, 92, 100};
    // Paleta predefinida(13, {
    //     {0, 0, 0}, {10, 20, 40}, {20, 40, 80}, {30, 60, 250}, {40, 100, 120}, {30, 140, 100}, {50, 160, 60}, {90, 147, 50}, {130, 135, 40}, {140, 120, 40}, {120, 90, 50}, {160, 120, 80}, {200, 180, 160}
    // }, valores);

    // mapa_teste.matrizAlturas.imprimir();
    mapa_teste.criarMapa(mapa_teste, "./mapas_gerados/mapa_muito_top", predefinida);
    // mapa_teste.gerarMatrizMapa(mapa_teste);
    // mapa_teste.matrizAlturas[0][0] = 33;
    // mapa_teste.matrizAlturas[1][1] = 33;
    // mapa_teste.matrizAlturas[1][2] = 66;
    // mapa_teste.matrizAlturas[1][3] = 66;
    // mapa_teste.matrizAlturas[2][3] = 33;
    // mapa_teste.matrizAlturas[3][4] = 40;
    // mapa_teste.exibirValoresMapaAltura();
    cout << "\n";
    // cout << mapa_teste.consultarMatrizAlturas(4, 4);
    // mapa_teste.criarMapa(mapa_teste, "./mapas_gerados/teste4", predefinida);
    // mapa_teste.exibirValoresMapaAltura();
    // mapa_teste.desalocarMatriz();

    
    // vector<int> valores {10, 20, 30};
    // Paleta paleta_simples(3, {{0,0,255}, {255,255,0}, {0, 255, 0}}, valores);
    // GerarMapa mapa_simplificado(3, 0.5);

    // mapa_simplificado.gerarMatrizMapa();
    // mapa_simplificado.exibirValoresMapaAltura();
    // paleta_simples.escreverPaleta("paleta_simples");
    // // 2 e resto
    // mapa_simplificado.criarMapa(mapa_simplificado, "./mapas_gerados/teste3", paleta_simples);
    // mapa_simplificado.desalocarMatriz();
}
