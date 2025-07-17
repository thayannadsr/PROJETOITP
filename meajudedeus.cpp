#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath> // para pow
#include <algorithm> // Para min e max
using namespace std;
    
int calcularTamanhoPorExpoente(int n) {
        return static_cast<int>(pow(2, n)) + 1;
}

class MapaDeAltitudes {
private:
    int tamanho;
    float** matriz;

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

    void gerar(float deslocamento, float rugosidade) {
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

    ~MapaDeAltitudes() {
        for (int i = 0; i < tamanho; ++i)
            delete[] matriz[i];
        delete[] matriz;
    }
};

int main() {
    int n = 1;                 
    float deslocamento = 1.0f;       // Deslocamento inicial
    float rugosidade = 0.5f;         // Fator de suavidade

    int tamanho = calcularTamanhoPorExpoente(n);

    MapaDeAltitudes mapa(tamanho);
    mapa.gerar(deslocamento, rugosidade);
    mapa.imprimir();

    return 0;
}