#include <iostream>
#include <cmath>
#include <ctime>
// #include "imagem.h"
#include "../paleta/paleta.h"
#include "../imagem/imagem.cpp"
using namespace std;


class GerarMapa {
    
    public:
        int tamanho;
        float rugosidade;
        int** matrizAlturas;

        GerarMapa(int N, float r) {
            tamanho = pow(2, N)+1;
            rugosidade = r;
        }

        void gerarMatrizMapa() {
            matrizAlturas = new int*[tamanho];
            for (int a = 0; a < tamanho; a++) {
                matrizAlturas[a] = new int[tamanho];
                
                for (int b = 0; b < tamanho; b++) {
                    matrizAlturas[a][b] = 0;
                }
            }
        }

        void desalocarMatriz() {
            for (int c = 0; c < tamanho; c++){
                delete[] matrizAlturas[c];
            }
            delete[] matrizAlturas;
        }
        
        void exibirValoresMapaAltura() {
            for (int a = 0; a < tamanho; a++) {
                cout << "| ";              
                for (int b = 0; b < tamanho; b++) {
                    cout << int(matrizAlturas[a][b]) << ", ";
                }
                cout << "|\n";
            }
        }
        
        int consultarMatrizAlturas(int x, int y) {
            return matrizAlturas[x][y];
        }

        int consultarTamanho() {
            return tamanho;
        }

        void criarMapa(GerarMapa m) { // paleta e imagens tbm
            Paleta cores(3,
                {{0,0,0}, {255,255,255}, {200, 200, 200}},
                {0, 20, 40}
            );

            Imagem img(tamanho, tamanho);
            img.matrizImagem();

            m.exibirValoresMapaAltura();
            img.exibirValoresPixelRGB();

            // Cor cor = cores.consultarCor(0);

            // Cor cor = cores.consultarCor(m.matrizAlturas[0][0]);
            // cout << endl << int(cor.r) << int(cor.g) << int(cor.b) << endl;
            for (int a = 0; a < tamanho; a++) {
                for (int b = 0; b < tamanho; b++) {
                    Cor cor = cores.consultarCor(m.matrizAlturas[a][b]);
                    img.mudarPixel(a, b, cor.r, cor.g, cor.b);
                }
            }
            img.exibirValoresPixelRGB();
            img.escreverPPM("./mapas_gerados/teste");
            img.desalocarMatriz();
        }
};
