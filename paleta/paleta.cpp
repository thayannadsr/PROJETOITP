#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


struct Cor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class Paleta {
    public:
        int quantidade;
        vector<Cor> cores;
        vector<int> valores;
    
        Paleta(int q, vector<Cor> c, vector<int> v) {
            quantidade = q;
            cores = c;
            valores = ordenarValores(v);
        }

        vector<int> ordenarValores(vector<int> v) {
            sort(v.begin(), v.end());
            return v;
        }

        void escreverPaleta(string nomeNovaPaleta) {
            ofstream file("./paletas_txt/" + nomeNovaPaleta + ".txt");
            file << quantidade << "\n";
            for (int x=0; x<quantidade; x++) {
                file << valores[x] << " " << int(cores[x].r) << " " << int(cores[x].g) << " " << int(cores[x].b) << "\n";
            }
            file.close();
        }

        Paleta lerPaleta(string nome_paleta) {
            ifstream arquivo;
            arquivo.open(nome_paleta);
            string line;

            arquivo >> line;
            int quantidadeNovaPaleta = stoi(line);
            vector<int> listaValoresNovaPaleta;
            vector<Cor> listaCoresNovaPaleta;

            for (int x=0; x<quantidadeNovaPaleta; x++) {
                arquivo >> line;
                int valorNovaPaleta = stoi(line);
                listaValoresNovaPaleta.push_back(valorNovaPaleta);

                Cor novaCor;
                arquivo >> line;
                novaCor.r = stoi(line);
                arquivo >> line;
                novaCor.g = stoi(line);
                arquivo >> line;
                novaCor.b = stoi(line);
                listaCoresNovaPaleta.push_back(novaCor);
            }

            arquivo.close();

            Paleta novaPaleta(quantidadeNovaPaleta, listaCoresNovaPaleta, listaValoresNovaPaleta);

            return novaPaleta;
        }

        Cor consultarCor(int n) {
            for (int x=0; x<quantidade; x++) {
                if (valores[x] > n) {
                    // cout << "maior: " << valores[x] << endl;
                    return cores[x-1];
                }
            }

            return cores[quantidade-1];
        }
};
