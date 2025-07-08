#include <iostream>
#include <cor.h>
#include <vector>
#include <fstream>
using namespace std;

class Paleta {
    public:
        int quantidade;
        vector<Cor> cores;
        vector<int> valores;
    
        Paleta(int q, vector<Cor> c, vector<int> v) {
            quantidade = q;
            cores = c;
            valores = v;
        }


};


int main() {
    Cor red {255, 0, 0};

    cout << int(red.b) << endl;

    Paleta cores(4,
        {{255,0,0}, {0,255,0}, {0,0,255}, {0,0,0}},
        {0, 10, 20, 30}
    );

    ofstream file("paleta.txt");
    file << cores.quantidade << "\n";
    for (int x=0; x<cores.quantidade; x++) {
        file << cores.valores[x] << " " << int(cores.cores[x].r) << " " << int(cores.cores[x].g) << " " << int(cores.cores[x].b) << "\n";
    }
    file.close();

    //     for (int y; y<cores.quantidade; y++) {
    // for (auto c : cores.cores) file << cores.valores << ", " << int(c.r) << ", " << int(c.b) << ", " << int(c.g) << "\n";
    //     // }
    // }
    
    cout << cores.quantidade;

    return 0;
}
