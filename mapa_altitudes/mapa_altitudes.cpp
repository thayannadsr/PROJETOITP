#include <iostream>
#include <cmath>
#include <ctime>
// #include "imagem.h"
#include "../paleta/paleta.cpp"
using namespace std;


struct Posicao {
    int linha;
    int coluna;
};

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

        Posicao diamond(Posicao SE, Posicao SD, Posicao IE, Posicao ID) {
            // calcula o centro dos pontos dados
            int dLinha = (SE.linha + SD.linha + IE.linha + ID.linha) / 4;
            int dColuna = (SE.coluna + SD.coluna + IE.coluna + ID.coluna) / 4;
            Posicao dCentro {dLinha, dColuna};

            // calcula o valor medio dos pontos dados
            int dValorMedio = (matrizAlturas[SE.linha][SE.coluna] + matrizAlturas[SD.linha][SD.coluna] + matrizAlturas[IE.linha][IE.coluna] + matrizAlturas[ID.linha][ID.coluna]) / 4;

            matrizAlturas[dCentro.linha][dCentro.coluna] = dValorMedio; // adicionar a variação aleatória

            return dCentro;
        }

        void encontrarMediaDeDoisPontos(Posicao p1, Posicao p2) {
            // calcula o ponto medio entre dois pontos dados
            int sEntreSEeSDlinha = (p1.linha + p2.linha) / 2;
            int sEntreSEeSDcoluna = (p1.coluna + p2.coluna) / 2;
            Posicao sCentro {sEntreSEeSDlinha, sEntreSEeSDcoluna};

            // calcula o valor medio dos dois pontos
            int sValorMedioEntreSEeSDlinha = (matrizAlturas[p1.linha][p1.coluna] + matrizAlturas[p2.linha][p2.coluna]) / 2;

            matrizAlturas[sEntreSEeSDlinha][sEntreSEeSDcoluna] = sValorMedioEntreSEeSDlinha; // adicionar a variação aleatória
        }

        void square(Posicao SE, Posicao SD, Posicao IE, Posicao ID, Posicao centro) {
            encontrarMediaDeDoisPontos(SE, SD);

        }

        void algoritmoDiamonSquare(int maximo, int maxVariacao) {
            srand(time(0));
            int maximoNoPonto = maximo - maxVariacao;
            if (maximoNoPonto <= 0) {
                cout << "A variação não pode ser maior que o máximo";
                return;
            }

            // define os valores das quatro pontas
            matrizAlturas[0][0] = (rand() % (maximoNoPonto))+1;
            matrizAlturas[0][tamanho-1] = (rand() % (maximoNoPonto))+1;
            matrizAlturas[tamanho-1][0] = (rand() % (maximoNoPonto))+1;
            matrizAlturas[tamanho-1][tamanho-1] = (rand() % (maximoNoPonto))+1;
            Posicao SE {0, 0};
            Posicao SD {0, tamanho-1};
            Posicao IE {tamanho-1, 0};
            Posicao ID {tamanho-1, tamanho-1};

            Posicao dCentro = diamond(SE, SD, IE, ID);
            square(SE, SD, IE, ID, dCentro);
        }
        
        // terminar algoritmo diamond square
        // permitir matriz com dimensões diferentes
        // escrever em arquivo
        // ler matriz de altitudes de um arquivo

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
