#include <iostream>
#include <fstream>
#include "imagem.h"
using namespace std;


class Imagem {
    string tipo;
    int largura;
    int altura;
    int max;
    Cor** pixel;
    
    public:

        Imagem(int alargura, int aaltura, string atipo="P3", int mInt=255) {
            largura = alargura;
            altura = aaltura;
            tipo = atipo;
            max = mInt;
        }
        
        ~Imagem() {
            desalocarMatriz();
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
            for (int a = 0; a < largura; a++) {
                cout << "| ";              
                for (int b = 0; b < altura; b++) {
                    cout << int(pixel[a][b].r) << int(pixel[a][b].g) << int(pixel[a][b].b) << ", ";
                }
                cout << "|\n";
            }
        }

        void escreverPPM(string nomeNovoPPM) {
            ofstream file(nomeNovoPPM + ".ppm");
            file << tipo << "\n";
            file << altura << " " << largura << "\n";
            file << max << "\n";
            for (int row = 0; row < largura; row++) {
                for (int linha = 0; linha < altura; linha++) {
                    file << int(pixel[row][linha].r) << " " << int(pixel[row][linha].g) << " " << int(pixel[row][linha].b) << " ";
                }
                file << "\n";
            }
        }
};
