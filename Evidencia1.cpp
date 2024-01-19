#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

struct Bitacora {
 string mes;
 int dia;
 string hora;
 string ipOrigen;
 string razonFalla;
};

void leerArchivo(const string& bitacora, vector<Bitacora>& bitacora1) {
 ifstream archivo(bitacora);

 if (!archivo) {
   cerr << "No se pudo abrir el archivo." << endl;
   return;
 }

 map<string, int> meses = {{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};

 string mes, hora, ip, razonFalla;
 int dia, puerto;

 while (archivo >> mes >> dia >> hora >> ip >> puerto >> razonFalla) {
   Bitacora b;
   b.mes = meses[mes];
   b.dia = dia;
   b.hora = hora;
   b.ipOrigen = ip + ":" + to_string(puerto);
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
 vector<Bitacora> bitacora;

 leerArchivo("bitacora.txt", bitacora);

 Bitacora buscarDesde, buscarHasta;

 cout << "Introduzca la fecha de inicio (formato MM DD hh:mm:ss): ";
 cin >> buscarDesde.mes >> buscarDesde.dia >> buscarDesde.hora;

 cout << "Introduzca la fecha de fin (formato MM DD hh:mm:ss): ";
 cin >> buscarHasta.mes >> buscarHasta.dia >> buscarHasta.hora;

 sort(bitacora.begin(), bitacora.end(), compararBitacora);

 cout << "Registros correspondientes al rango de fechas:" << endl;
 for (const auto& b : bitacora) {
   if ((b.mes > buscarDesde.mes || (b.mes == buscarDesde.mes && b.dia > buscarDesde.dia) ||
       (b.mes == buscarDesde.mes && b.dia == buscarDesde.dia && b.hora >= buscarDesde.hora)) &&
       (b.mes < buscarHasta.mes || (b.mes == buscarHasta.mes && b.dia < buscarHasta.dia) ||
       (b.mes == buscarHasta.mes && b.dia == buscarHasta.dia && b.hora <= buscarHasta.hora))) {
          cout << b.mes << " " << b.dia << " " << b.hora << " " << b.ipOrigen << " " << b.razonFalla << endl;
      }
  }

  ofstream archivoOrdenado("bitacora_ordenada.txt");
  if (archivoOrdenado.is_open()) {
      for (const auto& b : bitacora) {
          archivoOrdenado << b.mes << " " << b.dia << " " << b.hora << " " << b.ipOrigen << " " << b.razonFalla << endl;
      }
      archivoOrdenado.close();
      cout << "Resultado del ordenamiento almacenado en 'bitacora_ordenada.txt'" << endl;
  }
  else {
      cerr << "No se pudo abrir el archivo para escribir el resultado del ordenamiento." << endl;
  }


  return 0;
}
