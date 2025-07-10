#include <iostream>
// #include "imagem.h"
#include "../paleta/paleta.cpp"
using namespace std;

class Imagem {
    int largura;
    int altura;
    Cor** pixel;
    int max;
    
    public:
        string tipo;

        Imagem(int alargura, int aaltura, string atipo="P3", int mInt=255) {
            largura = alargura;
            altura = aaltura;
            tipo = atipo;
            max = mInt;
        }

        void matrizImagem() {
            pixel = new Cor*[largura];
            for (int a = 0; a < largura; a++) {
                pixel[a] = new Cor[altura];
                
                for (int b = 0; b < altura; b++) {
                    Cor p {0, 0, 0};
                    pixel[a][b] = p;
                }
            }
        }

        void desalocarMatriz() {
            for (int c = 0; c < largura; c++){
                delete[] pixel[c];
            }
            delete[] pixel;
        }

        Cor consultarPixel(int x, int y) {
            return pixel[x][y];
        }

        void mudarPixel(int x, int y, char r, char g, char b) {
            pixel[x][y].r = r;
            pixel[x][y].g = g;
            pixel[x][y].b = b;
        }

        void exibirValoresPixelRGB() {
            for (int a = 0; a < altura; a++) {
                cout << "| ";              
                for (int b = 0; b < largura; b++) {
                    cout << int(pixel[b][a].r) << int(pixel[b][a].g) << int(pixel[b][a].b) << ", ";
                }
                cout << "|\n";
            }
        }

        void escreverPPM(string nomeNovoPPM) {
            ofstream file(nomeNovoPPM);
            file << tipo << "\n";
            file << largura << " " << altura << "\n";
            file << max << "\n";
            for (int x = 0; x < largura; x++) {
                for (int y = 0; y < altura; y++) {
                    file << int(pixel[x][y].r) << " " << int(pixel[x][y].g) << " " << int(pixel[x][y].b) << " ";
                }
                file << "\n";
            }
        }
};
