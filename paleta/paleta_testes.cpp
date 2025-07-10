#include "paleta.cpp"
using namespace std;

int main() {
    Cor red {255, 0, 0};

    Paleta cores(4,
        {{255,0,0}, {0,255,0}, {0,0,255}, {0,0,0}},
        {1000, 10, 20, 30}
    );

    
    Cor corConsulta = cores.consultarCor(10);
    cout << int(corConsulta.r) << int(corConsulta.g) << int(corConsulta.b) << endl;
    
    cores = cores.lerPaleta("./paletas_txt/paleta.txt");
    cores.escreverPaleta("nova_paleta");
    
    // for (auto n : cores.valores) cout << n << ", " << endl;
    // cout << int(red.b) << endl;
    // cout << cores.quantidade << endl;
    // cout << cores.valores[3] << endl;

    return 0;
}
