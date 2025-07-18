#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "mapadealtitudes.h"
#include <fstream>
#include <cmath>
using namespace std;
using doctest::Approx;

TEST_CASE("Verifica inicialização da matriz com valores normalizados") {
    MapaDeAltitudes mapa(2, 1.0f); // 5x5
    int tamanho = mapa.QuantidadeLinhas();
    for (int y = 0; y < tamanho; ++y) {
        for (int x = 0; x < tamanho; ++x) {
            float altura = mapa.ConsultarAlturaXY(x, y);
            CHECK(altura >= 0.0f);
            CHECK(altura <= 1.0f);
        }
    }
}

TEST_CASE("Verifica salvamento de mapa 5x5 em arquivo") {
    MapaDeAltitudes mapa(2, 1.0f); // 5x5
    string nomeArquivo = "saida_mapa_5x5.txt";
    mapa.salvarEmArquivo(nomeArquivo);

    ifstream arq(nomeArquivo);
    REQUIRE(arq.is_open());

    int tamanho;
    arq >> tamanho;
    CHECK(tamanho == 5);

    float valor;
    int count = 0;
    while (arq >> valor) {
        CHECK(valor >= 0.0f);
        CHECK(valor <= 1.0f);
        count++;
    }

    CHECK(count == 25);
    arq.close();
}

TEST_CASE("Verifica leitura de arquivo 3x3 com dados específicos") {
    string nomeArquivo = "entrada_matriz_3x3.txt";
    ofstream arq(nomeArquivo);
    arq << "3\n"
        << "0.1 0.2 0.3\n"
        << "0.4 0.5 0.6\n"
        << "0.7 0.8 0.9\n";
    arq.close();

    MapaDeAltitudes mapa(1, 1.0f); // Tamanho inicial não importa
    mapa.lerDeArquivo(nomeArquivo);

    CHECK(mapa.QuantidadeLinhas() == 3);
    CHECK(mapa.QuantidadeColunas() == 3);
    CHECK(Approx(mapa.ConsultarAlturaXY(0, 0)) == 0.1f);
    CHECK(Approx(mapa.ConsultarAlturaXY(1, 1)) == 0.5f);
    CHECK(Approx(mapa.ConsultarAlturaXY(2, 2)) == 0.9f);
}

TEST_CASE("Verifica geração determinística com rugosidade 0.0, usei o deslocamento 0 e a rugosidade 1") {
    float deslocamentofixado = 0.0f;
    MapaDeAltitudes mapa(3, 1.0f, deslocamentofixado); // 9x9
    float alturaInicial = 0.5f;
    mapa.limparMatriz();

    // Define cantos usando setAltura
    int maxIdx = mapa.QuantidadeLinhas() - 1;
    mapa.setAltura(0, 0, alturaInicial);
    mapa.setAltura(maxIdx, 0, alturaInicial);
    mapa.setAltura(0, maxIdx, alturaInicial);
    mapa.setAltura(maxIdx, maxIdx, alturaInicial);

    mapa.diamondSquare(0, 0, maxIdx, maxIdx, deslocamentofixado, 0.0f);

    for (int y = 0; y < mapa.QuantidadeLinhas(); ++y) {
        for (int x = 0; x < mapa.QuantidadeColunas(); ++x) {
            CHECK(Approx(mapa.ConsultarAlturaXY(x, y)) == alturaInicial);
        }
    }
}