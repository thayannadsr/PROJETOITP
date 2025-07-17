#ifndef MAPADEALTITUDES_H
#define MAPADEALTITUDES_H
#include <fstream>
#include <string>

using namespace std;

class MapaDeAltitudes {
private:
    int tamanho;
    float** matriz;

    void alocarMatriz();
    float randomFloat(float min = 0.0f, float max = 1.0f);
    float gerarDeslocamentoInicial(float min = 0.15f, float max = 0.25f);
    void inicializarCantos();
    void aplicarSquare(int x, int y, int passo, float deslocamento);
    void diamondSquare(int x0, int y0, int x1, int y1, float deslocamento, float rugosidade);
    void normalizar();

public:
    MapaDeAltitudes(int t, float rugosidade);
    ~MapaDeAltitudes();

    static int calcularTamanhoPorExpoente(int n);
    void gerar(float rugosidade);
    void imprimir();
    float ConsultarAlturaXY(int x, int y);
    int QuantidadeLinhas();
    int QuantidadeColunas();
    void salvarEmArquivo(const string& meutxt) const;
    void lerDeArquivo(const string& nomeArquivo);
};

#endif