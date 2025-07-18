#include <iostream>
#include <cmath>
#include <ctime>
// #include "imagem.h"
#include "../paleta/paleta.h"
#include "../imagem/imagem.h"
#include "../mapa_de_altitudes/mapadealtitudes.h"
using namespace std;


class GerarMapa {
    
    public:
        int tamanho;
        float rugosidade;
        MapaDeAltitudes matrizAlturas;

        GerarMapa(int N, float r) : matrizAlturas(N, r)
        {
            tamanho = N;
            rugosidade = r;
        }

        // void gerarMatrizMapa(GerarMapa m) {
        //     MapaDeAltitudes mapa_altitudes(m.tamanho, m.rugosidade);
        //     matrizAlturas = mapa_altitudes.matriz;
        //     mapa_altitudes.imprimir();
        //     // matrizAlturas = new int*[tamanho];
        //     // for (int a = 0; a < tamanho; a++) {
        //     //     matrizAlturas[a] = new int[tamanho];
                
        //     //     for (int b = 0; b < tamanho; b++) {
        //     //         matrizAlturas[a][b] = 0;
        //     //     }
        //     // }
        // }

        // void desalocarMatriz() {
        //     for (int c = 0; c < tamanho; c++){
        //         delete[] matrizAlturas[c];
        //     }
        //     delete[] matrizAlturas;
        // }
        
        // void exibirValoresMapaAltura() {
        //     for (int a = 0; a < pow(2, tamanho)+1; a++) {
        //         cout << "| ";              
        //         for (int b = 0; b < pow(2, tamanho)+1; b++) {
        //             cout << (matrizAlturas[a][b]) << ", ";
        //         }
        //         cout << "|\n";
        //     }
        // }
        
        // int consultarMatrizAlturas(int x, int y) {
        //     return matrizAlturas[x][y];
        // }

        int consultarTamanho() {
            return tamanho;
        }

        void criarMapa(GerarMapa m, string nome, Paleta coresTerreno) { // paleta e imagens tbm
            Imagem img(m.matrizAlturas.calcularTamanhoPorExpoente(m.tamanho), m.matrizAlturas.calcularTamanhoPorExpoente(m.tamanho));
            img.matrizImagem();

            // img.exibirValoresPixelRGB();

            // Cor cor = cores.consultarCor(0);

            // Cor cor = cores.consultarCor(m.matrizAlturas[0][0]);
            // cout << endl << int(cor.r) << int(cor.g) << int(cor.b) << endl;
            for (int a = 0; a < m.matrizAlturas.calcularTamanhoPorExpoente(m.tamanho); a++) {
                for (int b = 0; b < m.matrizAlturas.calcularTamanhoPorExpoente(m.tamanho); b++) {
                    // cout << m.matrizAlturas.matriz[a][b] << endl;
                    Cor cor = coresTerreno.consultarCor((m.matrizAlturas.matriz[a][b]*100));
                    // cout << endl << int(cor.r) << int(cor.g) << int(cor.b) << endl;
                    img.mudarPixel(a, b, cor.r, cor.g, cor.b);
                    if (a > 0 && b > 0 && m.matrizAlturas.matriz[a-1][b-1] > m.matrizAlturas.matriz[a][b]) {
                        // sombra
                        float sombra = 0.9;
                        img.mudarPixel(a, b, cor.r*sombra, cor.g*sombra, cor.b*sombra);
                    }
                }
            }
            // img.exibirValoresPixelRGB();
            img.escreverPPM(nome);
            img.desalocarMatriz();
            m.matrizAlturas.~MapaDeAltitudes();
        }

        void aplicarSombras(GerarMapa m, Imagem img) {
            for (int a = 1; a < m.matrizAlturas.calcularTamanhoPorExpoente(m.tamanho); a++) {
                for (int b = 1; b < m.matrizAlturas.calcularTamanhoPorExpoente(m.tamanho); b++) {
                    if (m.matrizAlturas.matriz[a-1][b-1] > m.matrizAlturas.matriz[a][b]) {
                        // cout << m.matrizAlturas.matriz[a-1][b-1] << " " << m.matrizAlturas.matriz[a][b] << " " << m.matrizAlturas.matriz[a][b]*0.5 << endl;
                        // Cor cor = coresTerreno.consultarCor((m.matrizAlturas.matriz[a][b]*100));
                        // img.mudarPixel(a, b, cor.r, cor.g, cor.b);
                    }
                }
            }
        }
};
