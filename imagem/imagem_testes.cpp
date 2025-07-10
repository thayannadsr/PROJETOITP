#include <iostream>
#include "imagem.cpp"
using namespace std;


int main() {
    Imagem matrizTeste(2, 3);
    cout << matrizTeste.tipo << "\n";
    matrizTeste.matrizImagem();
    matrizTeste.mudarPixel(0, 0, 255, 0, 0);
    matrizTeste.mudarPixel(1, 1, 0, 255, 0);
    matrizTeste.mudarPixel(0, 2, 0, 0, 255);
    matrizTeste.escreverPPM("imagem_teste_erro"); // corrigir x, y
    matrizTeste.exibirValoresPixelRGB();

    // Imagem matrizTeste(10, 10);
    // cout << matrizTeste.tipo << "\n";
    // matrizTeste.matrizImagem();
    // matrizTeste.exibirValoresPixelRGB();
    // cout << "\n";

    // matrizTeste.mudarPixel(0, 0, 255, 255, 255);
    // matrizTeste.mudarPixel(0, 1, 255, 255, 255);
    // matrizTeste.mudarPixel(0, 7, 255, 255, 255);
    // matrizTeste.mudarPixel(0, 8, 255, 255, 255);
    // matrizTeste.mudarPixel(0, 9, 255, 255, 255);
    
    // matrizTeste.mudarPixel(1, 0, 255, 255, 255);
    // matrizTeste.mudarPixel(1, 2, 255, 0, 0);
    // matrizTeste.mudarPixel(1, 3, 255, 0, 0);
    // matrizTeste.mudarPixel(1, 4, 255, 0, 0);
    // matrizTeste.mudarPixel(1, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(1, 8, 255, 255, 255);
    // matrizTeste.mudarPixel(1, 9, 255, 255, 255);
    
    // matrizTeste.mudarPixel(2, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(2, 6, 255, 0, 0);

    // matrizTeste.mudarPixel(3, 1, 7, 191, 250);
    // matrizTeste.mudarPixel(3, 2, 255, 255, 255);
    // matrizTeste.mudarPixel(3, 3, 255, 255, 255);
    // matrizTeste.mudarPixel(3, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(3, 6, 255, 0, 0);
    // matrizTeste.mudarPixel(3, 8, 255, 0, 0);

    // matrizTeste.mudarPixel(4, 1, 7, 191, 250);
    // matrizTeste.mudarPixel(4, 2, 7, 191, 250);
    // matrizTeste.mudarPixel(4, 3, 7, 191, 250);
    // matrizTeste.mudarPixel(4, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(4, 6, 255, 0, 0);
    // matrizTeste.mudarPixel(4, 8, 255, 0, 0);

    // matrizTeste.mudarPixel(5, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(5, 6, 255, 0, 0);
    // matrizTeste.mudarPixel(5, 8, 255, 0, 0);
    
    // matrizTeste.mudarPixel(6, 0, 255, 255, 255);
    // matrizTeste.mudarPixel(6, 2, 255, 0, 0);
    // matrizTeste.mudarPixel(6, 3, 255, 0, 0);
    // matrizTeste.mudarPixel(6, 4, 255, 0, 0);
    // matrizTeste.mudarPixel(6, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(6, 6, 255, 0, 0);

    // matrizTeste.mudarPixel(7, 0, 255, 255, 255);
    // matrizTeste.mudarPixel(7, 2, 255, 0, 0);
    // matrizTeste.mudarPixel(7, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(7, 6, 255, 0, 0);
    // matrizTeste.mudarPixel(7, 8, 255, 255, 255);
    // matrizTeste.mudarPixel(7, 8, 255, 255, 255);
    // matrizTeste.mudarPixel(7, 9, 255, 255, 255);
    
    // matrizTeste.mudarPixel(8, 0, 255, 255, 255);
    // matrizTeste.mudarPixel(8, 2, 255, 0, 0);
    // matrizTeste.mudarPixel(8, 3, 255, 0, 0);
    // matrizTeste.mudarPixel(8, 5, 255, 0, 0);
    // matrizTeste.mudarPixel(8, 6, 255, 0, 0);
    // matrizTeste.mudarPixel(8, 0, 255, 255, 255);
    // matrizTeste.mudarPixel(8, 8, 255, 255, 255);
    // matrizTeste.mudarPixel(8, 9, 255, 255, 255);
    
    // matrizTeste.mudarPixel(9, 0, 255, 255, 255);
    // matrizTeste.mudarPixel(9, 8, 255, 255, 255);
    // matrizTeste.mudarPixel(9, 9, 255, 255, 255);

    // matrizTeste.exibirValoresPixelRGB();
    // matrizTeste.escreverPPM("amogus.ppm");
    // matrizTeste.desalocarMatriz();
}
