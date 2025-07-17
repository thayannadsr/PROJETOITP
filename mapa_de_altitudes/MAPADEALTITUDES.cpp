#include <iostream>
#include "mapadealtitudes.h"
#include <cstdlib> // para gerar numeros aleatorios
#include <ctime> // fornece horario para numero aleatorio
#include <iomanip> // define espacamento e casas decimais
#include <cmath> // para pow
#include <algorithm> // Para min e max
#include <fstream> // leitura e escrita em arquivos
using namespace std;

// Aloca memória dinâmica para a matriz de altitudes.
// Cria uma matriz tamanho x tamanho com valores iniciais 0.0f.
// Essa função é chamada internamente nos construtores e ao carregar arquivos.
void MapaDeAltitudes::alocarMatriz() {
    matriz = new float*[tamanho];
    for (int i = 0; i < tamanho; ++i) {
        matriz[i] = new float[tamanho];
        for (int j = 0; j < tamanho; ++j) {
            matriz[i][j] = 0.0f;
        }
    }
}

// Gera um número aleatório do tipo float entre os valores min e max.
// Por padrão, gera entre 0.0 e 1.0 se não forem fornecidos valores.
// Retorna esse número aleatório para ser usado em alturas e deslocamentos.
float MapaDeAltitudes::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

// Gera o deslocamento inicial aleatório.
// Recebe um intervalo de valores float entre min e max (default: 0.15f a 0.25f).
// Retorna um valor float dentro desse intervalo, usado para alterar as médias.
float MapaDeAltitudes::gerarDeslocamentoInicial(float min, float max) {
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
void MapaDeAltitudes::aplicarSquare(int x, int y, int passo, float deslocamento) {
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) return;
    if (matriz[y][x] != 0.0f) return;

    float soma = 0.0f;
    int contador = 0;

    if (y - passo >= 0) { soma += matriz[y - passo][x]; contador++; }
    if (y + passo < tamanho) { soma += matriz[y + passo][x]; contador++; }
    if (x - passo >= 0) { soma += matriz[y][x - passo]; contador++; }
    if (x + passo < tamanho) { soma += matriz[y][x + passo]; contador++; }

    if (contador > 0)
        matriz[y][x] = soma / contador + randomFloat(-deslocamento, deslocamento);
}

// Executa o algoritmo Diamond-Square recursivamente até preenchê-la completamente.
// Recebe coordenadas do canto superior esquerdo (x0, y0) e inferior direito (x1, y1),
// bem como o deslocamento inicial e rugosidade para gerar variação no relevo.
void MapaDeAltitudes::diamondSquare(int x0, int y0, int x1, int y1, float deslocamento, float rugosidade) {
    int dist = x1 - x0;
    if (dist < 2) return;

    int meioX = x0 + dist / 2;
    int meioY = y0 + dist / 2;

    float media = (matriz[y0][x0] + matriz[y0][x1] +
                   matriz[y1][x0] + matriz[y1][x1]) / 4.0f;
    matriz[meioY][meioX] = media + randomFloat(-deslocamento, deslocamento);

    aplicarSquare(meioX, y0, dist / 2, deslocamento);
    aplicarSquare(meioX, y1, dist / 2, deslocamento);
    aplicarSquare(x0, meioY, dist / 2, deslocamento);
    aplicarSquare(x1, meioY, dist / 2, deslocamento);

    float novoDeslocamento = deslocamento * rugosidade;
    diamondSquare(x0, y0, meioX, meioY, novoDeslocamento, rugosidade);
    diamondSquare(meioX, y0, x1, meioY, novoDeslocamento, rugosidade);
    diamondSquare(x0, meioY, meioX, y1, novoDeslocamento, rugosidade);
    diamondSquare(meioX, meioY, x1, y1, novoDeslocamento, rugosidade);
}

// Normaliza os valores da matriz para ficarem entre 0.0 e 1.0.
// Procura o menor e o maior valor na matriz e reescala todos proporcionalmente.
// Não recebe parâmetros nem retorna valor. Modifica a matriz diretamente.
void MapaDeAltitudes::normalizar() {
    float minVal = matriz[0][0];
    float maxVal = matriz[0][0];

    for (int i = 0; i < tamanho; ++i)
        for (int j = 0; j < tamanho; ++j) {
            minVal = min(minVal, matriz[i][j]);
            maxVal = max(maxVal, matriz[i][j]);
        }

    float intervalo = maxVal - minVal;
    if (intervalo == 0.0f) return;

    for (int i = 0; i < tamanho; ++i)
        for (int j = 0; j < tamanho; ++j)
            matriz[i][j] = (matriz[i][j] - minVal) / intervalo;
}

// Construtor que recebe o expoente 'n' e o valor de rugosidade.
// Calcula o tamanho da matriz com base em 2^n + 1, aloca memória, inicializa os cantos,
// em seguida, gera o terreno usando o algoritmo Diamond-Square.
MapaDeAltitudes::MapaDeAltitudes(int n, float rugosidade) : tamanho(calcularTamanhoPorExpoente(n)), matriz(nullptr) {
    srand(static_cast<unsigned>(time(0)));
    alocarMatriz();
    inicializarCantos();
    gerar(rugosidade);
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
void MapaDeAltitudes::gerar(float rugosidade) {
    float deslocamento = gerarDeslocamentoInicial();
    diamondSquare(0, 0, tamanho - 1, tamanho - 1, deslocamento, rugosidade);
    normalizar();
}

// AQQQQUIIII! Imprime a matriz de altitudes na tela formatada com duas casas decimais.
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
// Retorna um valor float da altitude, ou -7.0f se as coordenadas forem inválidas.
// Serve para acesso externo à matriz sem exposição direta.
float MapaDeAltitudes::ConsultarAlturaXY(int x, int y) {
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
        cerr << "Coordenadas fora dos limites!" << endl;
        return -7.0f;
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
// Cada linha do arquivo representa uma linha da matriz com valores formatados.
// Recebe o nome do arquivo como string; não retorna valor.
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
// Recebe o nome do arquivo como string; não retorna valor.
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

// Destrutor da classe. Libera a memória alocada dinamicamente da matriz.
// Garante que não haja vazamentos de memória ao final do uso do objeto.
// É chamado automaticamente quando o objeto é destruído ou sai de escopo.
MapaDeAltitudes::~MapaDeAltitudes() {
    if (matriz != nullptr) {
        for (int i = 0; i < tamanho; ++i)
            delete[] matriz[i];
        delete[] matriz;
    }
}

int main() {
    int n = 2;                 
    float rugosidade = 0.5f;         // Fator de suavidade

    MapaDeAltitudes mapa(n, rugosidade);
    mapa.imprimir();

    mapa.salvarEmArquivo("mapadealtitudes.txt");

    MapaDeAltitudes novoMapa(1, rugosidade); // Inicializa com tamanho qualquer, pois vai ler do arquivo
    novoMapa.lerDeArquivo("mapadealtitudes.txt");
    novoMapa.salvarEmArquivo("mapadealtitudes.txt");
    return 0;
}
