#include "paleta.h"


int main() {
    Cor red {255, 0, 0};

    Paleta cores(4,
        {{255,0,0}, {0,255,0}, {0,0,255}, {0,0,0}},
        {1000, 10, 20, 30}
    );
    
    cout << cores.quantidade << endl;
    for (auto n : cores.valores) cout << n << ", " << endl;
    // cout << cores.valores[3] << endl;
    
    // cout << int(red.r) << endl;
    // cout << int(red.b) << endl;
    Cor corConsulta = cores.consultarCor(10);
    cout << int(corConsulta.r) << int(corConsulta.g) << int(corConsulta.b) << endl;
    
    cores = cores.lerPaleta("./paletas_txt/paleta.txt");
    for (auto n : cores.valores) cout << n << ", " << endl;
    cores.escreverPaleta("nova_paleta");
    

    return 0;
}
