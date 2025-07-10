#include <iostream>
#include <cmath>
// #include "imagem.h"
#include "../paleta/paleta.cpp"
using namespace std;

class MapaAltitudes {
    
    public:
        int tamanho;
        float rugosidade;
        int** matrizAlturas;

        MapaAltitudes(int N, float r) {
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

        // Cor consultarPixel(int x, int y) {
        //     return pixel[x][y];
        // }

        // void mudarPixel(int x, int y, char r, char g, char b) {
        //     pixel[x][y].r = r;
        //     pixel[x][y].g = g;
        //     pixel[x][y].b = b;
        // }

        void exibirValoresMapaAltura() {
            for (int a = 0; a < tamanho; a++) {
                cout << "| ";              
                for (int b = 0; b < tamanho; b++) {
                    cout << int(matrizAlturas[a][b]) << ", ";
                }
                cout << "|\n";
            }
        }

        // void escreverPPM(string nomeNovoPPM) {
        //     ofstream file(nomeNovoPPM);
        //     file << tipo << "\n";
        //     file << altura << " " << largura << "\n";
        //     file << max << "\n";
        //     for (int x = 0; x < largura; x++) {
        //         for (int y = 0; y < altura; y++) {
        //             file << int(pixel[x][y].r) << " " << int(pixel[x][y].g) << " " << int(pixel[x][y].b) << " ";
        //         }
        //         file << "\n";
        //     }
        // }
};
