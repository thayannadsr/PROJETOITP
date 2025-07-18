#include <iostream>
#include "mapadealtitudes.h"

int main() {
    int n = 2;                 
    float rugosidade = 0.5f;         

    MapaDeAltitudes mapa(n, rugosidade);
    mapa.imprimir();
    cout << "\n";
    
    mapa.salvarEmArquivo("./mapas_altitudes_txt/mapadealtitudes.txt");
    
    
    n = 1;                 
    rugosidade = 0.5f;         
    
    MapaDeAltitudes mapa3x3(n, rugosidade);
    mapa3x3.imprimir();
    cout << "\n";
    mapa3x3.salvarEmArquivo("./mapas_altitudes_txt/mapadealtitudes3x3.txt");
    
    MapaDeAltitudes novoMapa(2, rugosidade); // Inicializa com tamanho qualquer, pois vai ler do arquivo
    novoMapa.lerDeArquivo("./mapas_altitudes_txt/mapadealtitudes3x3.txt");
    novoMapa.imprimir();

    return 0;
}
