#include <iostream>
#include <fstream>
#include "imagem.h"
using namespace std;

// Construtor que inicializa os atributos da imagem: tipo, largura, altura e valor máximo de cor.
// Recebe largura, altura, tipo de imagem ("P3" por padrão) e valor máximo (255 por padrão).
// Não retorna nada, pois é um construtor.
Imagem::Imagem(int alargura, int aaltura, string atipo = "P3", int mInt = 255) {
    largura = alargura;
    altura = aaltura;
    tipo = atipo;
    max = mInt;
    pixel = nullptr;
}

// Destrutor que desaloca a matriz de pixels da imagem para evitar vazamento de memória.
// Não recebe parâmetros.
// Chama a função desalocarMatriz() automaticamente ao destruir o objeto.
Imagem::~Imagem() {
    desalocarMatriz();
}

// Aloca dinamicamente a matriz de pixels (Cor**) com base na largura e altura da imagem.
// Inicializa cada pixel com a cor preta (r=0, g=0, b=0).
// Não recebe parâmetros e não retorna nada.
void Imagem::matrizImagem() {
    pixel = new Cor*[altura];
    for (int a = 0; a < altura; a++) {
        pixel[a] = new Cor[largura];
        for (int b = 0; b < largura; b++) {
            Cor p {0, 0, 0};
            pixel[a][b] = p;
        }
    }
}

// Libera da memória toda a matriz de pixels alocada dinamicamente por matrizImagem().
// Não recebe parâmetros.
// Não retorna nada.
void Imagem::desalocarMatriz() {
    for (int c = 0; c < altura; c++) {
        delete[] pixel[c];
    }
    delete[] pixel;
}

// Retorna a cor do pixel localizado na posição (x, y) na matriz.
// Recebe duas coordenadas inteiras: x (coluna) e y (linha).
// Retorna um objeto da classe Cor.
Cor Imagem::consultarPixel(int x, int y) {
    return pixel[x][y];
}

// Altera a cor do pixel na posição (x, y) para a nova cor definida por r, g e b.
// Recebe duas coordenadas inteiras e três componentes de cor (char).
// Não retorna nada, apenas modifica o pixel.
void Imagem::mudarPixel(int x, int y, char r, char g, char b) {
    pixel[x][y].r = r;
    pixel[x][y].g = g;
    pixel[x][y].b = b;
}

// Imprime na tela os valores RGB de todos os pixels da imagem.
// Não recebe parâmetros.
// Serve para visualizar a imagem como valores numéricos RGB no terminal.
void Imagem::exibirValoresPixelRGB() {
    for (int a = 0; a < altura; a++) {
        cout << "| ";
        for (int b = 0; b < largura; b++) {
            cout << int(pixel[a][b].r) << int(pixel[a][b].g) << int(pixel[a][b].b) << ", ";
        }
        cout << "|\n";
    }
}

// Escreve a imagem no formato .ppm (P3 - texto), salvando o conteúdo da matriz de pixels.
// Recebe uma string com o nome do novo arquivo (sem a extensão).
// Não retorna nada, apenas grava no disco.
void Imagem::escreverPPM(string nomeNovoPPM) {
    ofstream file(nomeNovoPPM + ".ppm");
    file << tipo << "\n";
    file << largura << " " << altura << "\n";
    file << max << "\n";
    for (int row = 0; row < altura; row++) {
        for (int linha = 0; linha < largura; linha++) {
            file << int(pixel[row][linha].r) << " "
                 << int(pixel[row][linha].g) << " "
                 << int(pixel[row][linha].b) << " ";
        }
        file << "\n";
    }
}
