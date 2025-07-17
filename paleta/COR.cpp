#include <iostream>
#include "cor.h"
using namespace std;

// Construtor padrão que inicializa os valores da cor como preto (r=0, g=0, b=0).
// Não recebe parâmetros.
// Cria uma cor "vazia" por padrão.
Cor::Cor() : r(0), g(0), b(0) {}

// Construtor que inicializa a cor com valores fornecidos para vermelho, verde e azul.
// Recebe três unsigned char (0 a 255), representando cada componente da cor RGB.
// Permite criar uma cor com valores personalizados.
Cor::Cor(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b) {}