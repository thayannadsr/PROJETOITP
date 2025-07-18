#include "paleta.h"


int main() {
    // Cor red {255, 0, 0};

    // Paleta cores(4,
    //     {{255,0,0}, {0,255,0}, {0,0,255}, {0,0,0}},
    //     {1000, 10, 20, 30}
    // );

    vector<int> valores {0, 9, 18, 27, 36, 44, 52, 60, 68, 76, 84, 92, 100};
    Paleta cores(13, {
        {0, 0, 0}, {10, 20, 40}, {20, 40, 80}, {30, 60, 250}, {40, 100, 120}, {30, 140, 100}, {50, 160, 60}, {90, 147, 50}, {130, 135, 40}, {140, 120, 40}, {120, 90, 50}, {160, 120, 80}, {200, 180, 160}
    }, valores);
    
    // cout << cores.quantidade << endl;
    // for (auto n : cores.valores) cout << n << ", " << endl;
    // cout << cores.valores[3] << endl;
    
    // cout << int(red.r) << endl;
    // cout << int(red.b) << endl;

    int altura = 10;
    Cor corConsulta = cores.consultarCor(altura);
    string cor = "(" + to_string(int(corConsulta.r)) + ", " + to_string(int(corConsulta.g)) + ", " + to_string(int(corConsulta.b)) + ")";
    cout << "A altura corresponde a cor: " << cor << endl;
    
    cores.escreverPaleta("paleta_definida");
    cores = cores.lerPaleta("./paletas_txt/paleta.txt");
    // for (auto n : cores.valores) cout << n << ", " << endl;
    cores.escreverPaleta("nova_paleta");

    return 0;
}
