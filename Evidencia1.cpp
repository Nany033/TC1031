#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Bitacora {
   std::string mes;
   int dia;
   std::string hora;
   std::string ipOrigen;
   std::string razonFalla;
};

void leerArchivo(const std::string& nombreArchivo, std::vector<Bitacora>& bitacora) {
   std::ifstream archivo(nombreArchivo);

   if (!archivo) {
       std::cerr << "No se pudo abrir el archivo." << std::endl;
       return;
   }

   std::string linea;
   while (getline(archivo, linea)) {
       std::istringstream ss(linea);
       Bitacora b;
       char c;
       ss >> b.mes >> b.dia >> c >> b.hora >> b.ipOrigen >> c >> b.razonFalla;
       bitacora.push_back(b);
   }

   archivo.close();
}

bool compararBitacora(const Bitacora &a, const Bitacora &b) {
   if (a.mes != b.mes)
       return a.mes < b.mes;
   if (a.dia != b.dia)
       return a.dia < b.dia;
   return a.hora < b.hora;
}

int main(){

    std::vector<Bitacora> bitacora;
    Bitacora buscarDesde;
    Bitacora buscarHasta;

    std::cout << "Introduzca la fecha de inicio (formato MM DD hh:mm:ss): ";
    std::cin >> buscarDesde.mes >> buscarDesde.dia >> buscarDesde.hora;

    std::cout << "Introduzca la fecha de fin (formato MM DD hh:mm:ss): ";
    std::cin >> buscarHasta.mes >> buscarHasta.dia >> buscarHasta.hora;

    // Buscar en el vector entre las fechas especificadas
    for (const auto &b : bitacora) {
       if (b.mes >= buscarDesde.mes && b.dia >= buscarDesde.dia && b.hora >= buscarDesde.hora &&
           b.mes <= buscarHasta.mes && b.dia <= buscarHasta.dia && b.hora <= buscarHasta.hora) {
           // Mostrar la información de la bitácora
       }
    }

    // Ordenar el vector
    std::sort(bitacora.begin(), bitacora.end(), compararBitacora);

}