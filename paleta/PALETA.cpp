#include "paleta.h"
#include <fstream>
#include <algorithm>


Cor::Cor(unsigned char _r, unsigned char _g, unsigned char _b) {
    this->r = _r;
    this->g = _g;
    this->b = _b;
}

Paleta::Paleta(int q, vector<Cor> c, vector<int> v) {
    quantidade = q;
    cores = c;
    valores = ordenarValores(v);
}

vector<int> Paleta::ordenarValores(vector<int> v) {
    sort(v.begin(), v.end());
    return v;
}

void Paleta::escreverPaleta(string nomeNovaPaleta) {
    ofstream file("./paletas_txt/" + nomeNovaPaleta + ".txt");
    file << quantidade << "\n";
    for (int x = 0; x < quantidade; x++) {
        file << valores[x] << " " << int(cores[x].r) << " " << int(cores[x].g) << " " << int(cores[x].b) << "\n";
    }
    file.close();
}

Paleta Paleta::lerPaleta(string nome_paleta) {
    ifstream arquivo;
    arquivo.open(nome_paleta);
    string line;
    
    arquivo >> line;
    int quantidadeNovaPaleta = stoi(line);
    vector<int> listaValoresNovaPaleta;
    vector<Cor> listaCoresNovaPaleta;
    
    for (int x = 0; x < quantidadeNovaPaleta; x++) {
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

Cor Paleta::consultarCor(int n) {
    for (int x = 0; x < quantidade; x++) {
        if (n < valores[0]) {
            cout << "o número não está no intervalo\n";
            break;
        } else if (n >= valores[x] && n < valores[x+1]) {
            return cores[x];
        } 
        if (x+1 == valores.size()-1) {
            return cores[x+1];
        }
    }
    return cores[0];
}
