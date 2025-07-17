#ifndef MAPADEALTITUDES_H
#define MAPADEALTITUDES_H

#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class MapaDeAltitudes {
private:
    int tamanho;
    double** matriz;

    void alocarMatriz();
    double randomFloat(double min = 0.0, double max = 1.0);
    double gerarDeslocamentoInicial(double min = 0.15, double max = 0.25, double deslocamentofixado = NAN);
    void inicializarCantos();

public:
    MapaDeAltitudes(int t, double rugosidade, double deslocamentoinicial = NAN);
    ~MapaDeAltitudes();

    double getAltura(int x, int y) const;
    void setAltura(int x, int y, double valor);
    void aplicarSquare(int x, int y, int passo, double deslocamento);
    void diamondSquare(int x0, int y0, int x1, int y1, double deslocamento, double rugosidade);
    void normalizar();
    static int calcularTamanhoPorExpoente(int n);
    void gerar(double rugosidade, double deslocamentoinicial = NAN);
    void imprimir();
    double ConsultarAlturaXY(int x, int y);
    int QuantidadeLinhas();
    int QuantidadeColunas();
    void salvarEmArquivo(const string& meutxt) const;
    void lerDeArquivo(const string& nomeArquivo);
};

#endif