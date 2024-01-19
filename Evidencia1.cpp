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
   int puerto;
   std::string razonFalla;
};

void leerArchivo(const std::string& bitacora, std::vector<Bitacora>& bitacora1) {
   std::ifstream archivo(bitacora);

   if (!archivo) {
       std::cerr << "No se pudo abrir el archivo." << std::endl;
       return;
   }

   std::string mes, hora, ip, razonFalla;
   int dia, puerto;

   while (archivo >> mes >> dia >> hora >> ip >> puerto >> razonFalla) {
       Bitacora b;
       b.mes = mes;
       b.dia = dia;
       b.hora = hora;
       b.ipOrigen = ip + ":" + std::to_string(puerto);
       b.razonFalla = razonFalla;

       bitacora1.push_back(b);
   }

   archivo.close();
}


bool compararBitacora(const Bitacora& a, const Bitacora& b) {
   if (a.mes != b.mes)
       return a.mes < b.mes;
   if (a.dia != b.dia)
       return a.dia < b.dia;
   return a.hora < b.hora;
}



int main() {

    std::vector<Bitacora> bitacora;

    leerArchivo("bitacora.txt", bitacora);

    Bitacora buscarDesde;
    Bitacora buscarHasta;

    std::cout << "Introduzca la fecha de inicio (formato MM DD hh:mm:ss): ";
    std::cin >> buscarDesde.mes >> buscarDesde.dia >> buscarDesde.hora;

    std::cout << "Introduzca la fecha de fin (formato MM DD hh:mm:ss): ";
    std::cin >> buscarHasta.mes >> buscarHasta.dia >> buscarHasta.hora;

    
    leerArchivo("bitacora.txt", bitacora);

    
    std::sort(bitacora.begin(), bitacora.end(), compararBitacora);

    // aqui se inicia la busqueda de los datos
    std::cout << "Registros correspondientes al rango de fechas:" << std::endl;
    for (const auto& b : bitacora) {
        if ((b.mes > buscarDesde.mes || (b.mes == buscarDesde.mes && b.dia > buscarDesde.dia) ||
            (b.mes == buscarDesde.mes && b.dia == buscarDesde.dia && b.hora >= buscarDesde.hora)) &&
            (b.mes < buscarHasta.mes || (b.mes == buscarHasta.mes && b.dia < buscarHasta.dia) ||
                (b.mes == buscarHasta.mes && b.dia == buscarHasta.dia && b.hora <= buscarHasta.hora))) {
            // aqui mostramos las fechas entre los rangos indicados
            std::cout << b.mes << " " << b.dia << " " << b.hora << " " << b.ipOrigen << " " << b.razonFalla << std::endl;
        }
    }

    // aqui lo guardamos en el nuevo archivo txt
    std::ofstream archivoOrdenado("bitacora_ordenada.txt");
    if (archivoOrdenado.is_open()) {
        for (const auto& b : bitacora) {
            archivoOrdenado << b.mes << " " << b.dia << " " << b.hora << " " << b.ipOrigen << " " << b.razonFalla << std::endl;
        }
        archivoOrdenado.close();
        std::cout << "Resultado del ordenamiento almacenado en 'bitacora_ordenada.txt'" << std::endl;
    }
    else {
        std::cerr << "No se pudo abrir el archivo para escribir el resultado del ordenamiento." << std::endl;
    }

    return 0;
}
