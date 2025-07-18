#include <iostream>
#include "mapadealtitudes.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

// Arredonda valor para 6 casas decimais
double arredondar6(double valor) {
    return round(valor * 1e6) / 1e6;
}

// Aloca memória dinâmica para a matriz de altitudes.
// Cria uma matriz tamanho x tamanho com valores iniciais 0.0f.
// Essa função é chamada internamente nos construtores e ao carregar arquivos.
void MapaDeAltitudes::alocarMatriz() {
    matriz = new double*[tamanho];
    preenchido = new bool*[tamanho];
    for (int i = 0; i < tamanho; ++i) {
        matriz[i] = new double[tamanho];
        preenchido[i] = new bool[tamanho];
        for (int j = 0; j < tamanho; ++j) {
            matriz[i][j] = 0.0;
            preenchido[i][j] = false;
        }
    }
}

// Setter para modificar valor da matriz
void MapaDeAltitudes::setAltura(int x, int y, double valor) {
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
        return;
    }
    matriz[y][x] = valor;
    preenchido[y][x] = true;
}

// Gera um número aleatório do tipo float entre os valores min e max.
// Por padrão, gera entre 0.0 e 1.0 se não forem fornecidos valores.
// Retorna esse número aleatório para ser usado em alturas e deslocamentos.
double MapaDeAltitudes::randomFloat(double min, double max) {
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

// Gera o deslocamento inicial aleatório.
// Recebe um intervalo de valores float entre min e max (default: 0.15f a 0.25f).
// Retorna um valor float dentro desse intervalo, usado para alterar as médias.
double MapaDeAltitudes::gerarDeslocamentoInicial(double min, double max, double deslocamentofixado) {
    if (isnan(deslocamentofixado)) {
    }
    return randomFloat(min, max);
}

// Inicializa os quatro cantos da matriz com valores aleatórios.
// Não recebe parâmetros e não retorna nada.
void MapaDeAltitudes::inicializarCantos() {
    matriz[0][0] = randomFloat();
    matriz[0][tamanho - 1] = randomFloat();
    matriz[tamanho - 1][0] = randomFloat();
    matriz[tamanho - 1][tamanho - 1] = randomFloat();
}

// Etapa Square
// Recebe coordenadas (x, y), a distância entre os pontos a serem gerados e o valor do deslocamento.
// Calcula a média dos vizinhos e adiciona um deslocamento aleatório.
void MapaDeAltitudes::aplicarSquare(int x, int y, int passo, double deslocamento) {
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) return;
    if (preenchido[y][x]) return;

    double soma = 0.0;
    int contador = 0;

    if (y - passo >= 0 && preenchido[y - passo][x]) {
        soma += matriz[y - passo][x]; contador++;
    }
    if (y + passo < tamanho && preenchido[y + passo][x]) {
        soma += matriz[y + passo][x]; contador++;
    }
    if (x - passo >= 0 && preenchido[y][x - passo]) {
        soma += matriz[y][x - passo]; contador++;
    }
    if (x + passo < tamanho && preenchido[y][x + passo]) {
        soma += matriz[y][x + passo]; contador++;
    }

    if (contador > 0) {
        matriz[y][x] = soma / contador + randomFloat(-deslocamento, deslocamento);
        preenchido[y][x] = true;
    }
}

// Executa o algoritmo Diamond-Square recursivamente até preenchê-la completamente.
// Recebe coordenadas do canto superior esquerdo (x0, y0) e inferior direito (x1, y1),
// bem como o deslocamento inicial e rugosidade para gerar variação no relevo.
void MapaDeAltitudes::diamondSquare(int x0, int y0, int x1, int y1, double deslocamento, double rugosidade) {
    int dist = x1 - x0;
    if (dist < 2) return;

    int meioX = x0 + dist / 2;
    int meioY = y0 + dist / 2;

    if (!preenchido[meioY][meioX]) {
        double media = (matriz[y0][x0] + matriz[y0][x1] +
                        matriz[y1][x0] + matriz[y1][x1]) / 4.0;
        matriz[meioY][meioX] = media + randomFloat(-deslocamento, deslocamento);
        preenchido[meioY][meioX] = true;
    }

    aplicarSquare(meioX, y0, dist / 2, deslocamento);  // topo
    aplicarSquare(meioX, y1, dist / 2, deslocamento);  // baixo
    aplicarSquare(x0, meioY, dist / 2, deslocamento);  // esquerda
    aplicarSquare(x1, meioY, dist / 2, deslocamento);  // direita

    double novoDeslocamento = deslocamento * rugosidade;
    diamondSquare(x0, y0, meioX, meioY, novoDeslocamento, rugosidade);
    diamondSquare(meioX, y0, x1, meioY, novoDeslocamento, rugosidade);
    diamondSquare(x0, meioY, meioX, y1, novoDeslocamento, rugosidade);
    diamondSquare(meioX, meioY, x1, y1, novoDeslocamento, rugosidade);
}

// Normaliza os valores da matriz para ficarem entre 0.0 e 1.0.
// Procura o menor e o maior valor na matriz e reescala todos proporcionalmente.
// Não recebe parâmetros nem retorna valor. Modifica a matriz diretamente.
void MapaDeAltitudes::normalizar() {
    double minVal = matriz[0][0];
    double maxVal = matriz[0][0];

    for (int i = 0; i < tamanho; ++i)
        for (int j = 0; j < tamanho; ++j) {
            minVal = min(minVal, matriz[i][j]);
            maxVal = max(maxVal, matriz[i][j]);
        }

    double intervalo = maxVal - minVal;
    if (intervalo == 0.0) return;

    for (int i = 0; i < tamanho; ++i)
        for (int j = 0; j < tamanho; ++j)
            matriz[i][j] = arredondar6((matriz[i][j] - minVal) / intervalo);
}

// Construtor que recebe o expoente 'n' e o valor de rugosidade.
// Calcula o tamanho da matriz com base em 2^n + 1, aloca memória, inicializa os cantos,
// em seguida, gera o terreno usando o algoritmo Diamond-Square.
MapaDeAltitudes::MapaDeAltitudes(int n, double rugosidade, double deslocamentoinicial) : tamanho(calcularTamanhoPorExpoente(n)), matriz(nullptr) {
    srand(static_cast<unsigned>(time(0)));
    alocarMatriz();
    inicializarCantos();
    gerar(rugosidade, deslocamentoinicial);
}

// Recebe o n
// Calcula o tamanho da matriz.
// Retorna um valor igual a 2^n + 1, necessário para o algoritmo Diamond-Square.
int MapaDeAltitudes::calcularTamanhoPorExpoente(int n) {
    return static_cast<int>(pow(2, n)) + 1;
}

// Gera as altitudes usando o algoritmo Diamond-Square com uma dada rugosidade.
// O parâmetro rugosidade controla a sutileza do relevo gerado.
// Ao final, normaliza os valores para manter a escala entre 0.0 e 1.0.
void MapaDeAltitudes::gerar(double rugosidade, double deslocamentoinicial) {
    double deslocamento;
    if (!isnan(deslocamentoinicial)) {
        deslocamento = deslocamentoinicial;
    } else {
        deslocamento = gerarDeslocamentoInicial();  // usa o valor aleatório se não passou o fixo
    }
    diamondSquare(0, 0, tamanho - 1, tamanho - 1, deslocamento, rugosidade);
    normalizar();
}

// Imprime a matriz de altitudes na tela formatada com duas casas decimais.
// Não recebe parâmetros e não retorna nada.
// Serve para visualização do relevo gerado.
void MapaDeAltitudes::imprimir() {
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j)
            cout << fixed << setprecision(2) << setw(6) << matriz[i][j] << " ";
        cout << endl;
    }
}

// Consulta a altura em uma posição específica da matriz, com coordenadas (x, y).
// Retorna a altitude, ou -7.0 se as coordenadas forem inválidas.
// Serve para acesso externo à matriz.
double MapaDeAltitudes::ConsultarAlturaXY(int x, int y) {
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
        cerr << "Coordenadas fora dos limites!" << endl;
        return -7.0;
    }
    return matriz[y][x];
}

// Retorna o número de linhas da matriz de altitudes.
// Como a matriz é quadrada, é igual à quantidade de colunas.
// Não recebe parâmetros.
int MapaDeAltitudes::QuantidadeLinhas() {
    return tamanho;
}

// Retorna o número de colunas da matriz de altitudes.
// Como a matriz é quadrada, é igual à quantidade de linhas.
// Não recebe parâmetros.
int MapaDeAltitudes::QuantidadeColunas() {
    return tamanho;
}

// Salva a matriz de altitudes em um arquivo de texto.
// Recebe o nome do arquivo como string.
// Não retorna valor
void MapaDeAltitudes::salvarEmArquivo(const string& meutxt) const {
    ofstream arquivo(meutxt);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para escrita!" << endl;
        return;
    }
    arquivo << tamanho << endl;
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            arquivo << fixed << setprecision(5) << matriz[i][j];
            if (j < tamanho - 1)
                arquivo << " ";
        }
        arquivo << endl;
    }
    arquivo.close();
}

// Lê os dados da matriz de um arquivo de texto gerado previamente.
// Substitui a matriz atual pelos dados lidos do arquivo fornecido.
// Recebe o nome do arquivo como string e não retorna valor.
void MapaDeAltitudes::lerDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para leitura!" << endl;
        return;
    }
    int novoTamanho;
    arquivo >> novoTamanho;
    if (novoTamanho <= 0) {
        cerr << "Tamanho inválido no arquivo!" << endl;
        return;
    }
    if (matriz != nullptr) {
        for (int i = 0; i < tamanho; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
        matriz = nullptr;
    }
    tamanho = novoTamanho;
    alocarMatriz();
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            arquivo >> matriz[i][j];
            if (arquivo.fail()) {
                cerr << "Erro na leitura dos dados da matriz!" << endl;
                return;
            }
        }
    }
    arquivo.close();
}

void MapaDeAltitudes::limparMatriz() {
    for (int y = 0; y < tamanho; ++y) {
        for (int x = 0; x < tamanho; ++x) {
            matriz[y][x] = 0.0;
            preenchido[y][x] = false;
        }
    }
}


// Destrutor da classe. Libera a memória alocada dinamicamente da matriz.
// Garante que não haja vazamentos de memória ao final do uso do objeto.
// É chamado automaticamente quando o objeto é destruído ou sai de escopo.
MapaDeAltitudes::~MapaDeAltitudes() {
    if (matriz != nullptr) {
        for (int i = 0; i < tamanho; ++i) {
            delete[] matriz[i];
            delete[] preenchido[i];
        }
        delete[] matriz;
        delete[] preenchido;
    }
}