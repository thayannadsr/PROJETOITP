#include <iostream>
#include <cstdlib> // para gerar numeros aleatorios
#include <ctime> // fornece horario para numero aleatorio
#include <iomanip> // define espacamento e casas decimais
#include <cmath> // para pow
#include <algorithm> // Para min e max
#include <fstream> // leitura e escrita em arquivos
using namespace std;
    
int calcularTamanhoPorExpoente(int n) {
        return static_cast<int>(pow(2, n)) + 1;
}

class MapaDeAltitudes { 
private:
    int tamanho;
    float** matriz = nullptr;

    void alocarMatriz() {
        matriz = new float*[tamanho];
        for (int i = 0; i < tamanho; ++i) {
            matriz[i] = new float[tamanho];
            for (int j = 0; j < tamanho; ++j) {
                matriz[i][j] = 0.0f;
            }
        }
    }

    float randomFloat(float min = 0.0f, float max = 1.0f) {
        return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
    }

    float gerarDeslocamentoInicial(float min = 0.15f, float max = 0.25f) {
        return randomFloat(min, max);
    }

    void inicializarCantos() {
        matriz[0][0] = randomFloat();
        matriz[0][tamanho - 1] = randomFloat();
        matriz[tamanho - 1][0] = randomFloat();
        matriz[tamanho - 1][tamanho - 1] = randomFloat();
    }

    void aplicarSquare(int x, int y, int passo, float deslocamento) {
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

    void diamondSquare(int x0, int y0, int x1, int y1, float deslocamento, float rugosidade) {
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

    void normalizar() {
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

public:
    MapaDeAltitudes(int t) : tamanho(t) {
        srand(static_cast<unsigned>(time(0)));
        alocarMatriz();
        inicializarCantos();
    }

    void gerar(float rugosidade) {
        float deslocamento = gerarDeslocamentoInicial();
        diamondSquare(0, 0, tamanho - 1, tamanho - 1, deslocamento, rugosidade);
        normalizar();  // Normaliza após gerar
    }

    void imprimir() {
        for (int i = 0; i < tamanho; ++i) {
            for (int j = 0; j < tamanho; ++j)
                cout << fixed << setprecision(2) << setw(6) << matriz[i][j] << " ";
            cout << endl;
        }
    }

    float ConsultarAlturaXY(int x, int y) {
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho) {
        cerr << "Coordenadas fora dos limites!" << endl;
        return -7.0f;
    }
        return matriz[y][x];
    }

    int QuantidadeLinhas() {
        return tamanho;
    }

    int QuantidadeColunas() {
        return tamanho;
    }

    void salvarEmArquivo(const string& meutxt) const {
    ofstream arquivo(meutxt);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para escrita!" << endl;
        return;
    }
    // Primeiro salva o tamanho da matriz
    arquivo << tamanho << endl;

    // Agora salva os valores da matriz
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

    void lerDeArquivo(const string& nomeArquivo) {
     ifstream arquivo(nomeArquivo);
        if (!arquivo) {
            cerr << "Erro ao abrir o arquivo para leitura!" << endl;
            return;
        }

    // Primeiro, ler o tamanho da matriz
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

    // Agora le os valores da matriz
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

    ~MapaDeAltitudes() {
        if (matriz != nullptr) {
        for (int i = 0; i < tamanho; ++i)
            delete[] matriz[i];
        delete[] matriz;
        }
    }
};

int main() {
    int n = 3;                 
    float rugosidade = 0.5f;         // Fator de suavidade

    int tamanho = calcularTamanhoPorExpoente(n);

    MapaDeAltitudes mapa(tamanho);
    mapa.gerar(rugosidade);
    mapa.imprimir();

    mapa.salvarEmArquivo("mapadealtitudes.txt");

    MapaDeAltitudes novoMapa(1); // Inicializa com tamanho qualquer, pois vai ler do arquivo
    novoMapa.lerDeArquivo("mapadealtitudes.txt");
    novoMapa.imprimir();

    return 0;
}