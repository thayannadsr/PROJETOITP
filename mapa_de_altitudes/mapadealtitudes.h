#ifndef MAPADEALTITUDES_H
#define MAPADEALTITUDES_H
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class MapaDeAltitudes {
private:
    int tamanho;
    float** matriz;
    bool** preenchido;

    
    void alocarMatriz();
    float randomFloat(float min = 0.0f, float max = 1.0f);
    float gerarDeslocamentoInicial(float min = 0.5f, float max = 1.0f, float deslocamentofixado = NAN);
    void inicializarCantos();
    
    public:
    MapaDeAltitudes(int t, float rugosidade, float deslocamentoinicial = NAN);
    ~MapaDeAltitudes();

    void aplicarSquare(int x, int y, int passo, float deslocamento);
    void diamondSquare(int x0, int y0, int x1, int y1, float deslocamento, float rugosidade);
    void normalizar();
    static int calcularTamanhoPorExpoente(int n);
    void gerar(float rugosidade, float deslocamentoinicial = NAN);
    void imprimir();
    float ConsultarAlturaXY(int x, int y);
    int QuantidadeLinhas();
    int QuantidadeColunas();
    void salvarEmArquivo(const string& meutxt) const;
    void lerDeArquivo(const string& nomeArquivo);
    void limparMatriz();
    void setAltura(int x, int y, float valor);
};

#endif