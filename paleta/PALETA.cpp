#include <iostream>
#include "paleta.h"
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

// Construtor que inicializa a paleta com a quantidade de cores, um vetor de cores (c) e os valores associados (v).
// Ele também ordena os valores usando a função ordenarValores.
// Não retorna nada, pois é o construtor da classe.
Paleta::Paleta(int q, vector<Cor> c, vector<int> v) {
    quantidade = q;
    cores = c;
    valores = ordenarValores(v);
}

// Ordena o vetor de inteiros v em ordem crescente usando std::sort.
// Recebe um vector<int> como parâmetro e retorna o mesmo vetor, porém ordenado.
// Serve para garantir que os valores associados às cores estejam organizados.
vector<int> Paleta::ordenarValores(vector<int> v) {
    sort(v.begin(), v.end());
    return v;
}

// Salva a paleta atual em um arquivo .txt dentro da pasta ./paletas_txt/.
// Recebe o nome da nova paleta.
// Escreve no arquivo a quantidade, os valores e as cores no formato especificado.
void Paleta::escreverPaleta(string nomeNovaPaleta) {
    ofstream file("./paletas_txt/" + nomeNovaPaleta + ".txt");
    file << quantidade << "\n";
    for (int x = 0; x < quantidade; x++) {
        file << valores[x] << " " << int(cores[x].r) << " " << int(cores[x].g) << " " << int(cores[x].b) << "\n";
    }
    file.close();
}

// Lê uma paleta de um arquivo .txt, reconstruindo os valores e as cores a partir do conteúdo.
// Recebe o caminho do arquivo como string e retorna uma nova instância da classe Paleta.
// Serve para carregar paletas salvas previamente.
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

// Consulta qual cor está associada a um dado valor.
// Retorna um objeto Cor, de acordo com a faixa de valor em que n se encaixa.
// Se n estiver abaixo do primeiro valor, imprime uma mensagem de erro.
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
