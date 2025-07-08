#include <iostream>
#include <imagem.h>
using namespace std;

Imagem::Imagem(int alargura, int aaltura) {
        largura = alargura;
        altura = aaltura;

        pixel = new Cor*[largura];
        for (int a = 0; a < largura; a++) {
            pixel[a] = new Cor[altura];

            for (int b = 0; b < altura; b++) {
                pixel[a][b] = Cor(0, 0, 0);
            }
        }
}

Imagem::~Imagem() {
            for (int c = 0; c < largura; c++){
                delete[] pixel[c];
            }
            delete[] pixel;
}