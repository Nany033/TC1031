#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
string readFile(string filename){
    //Complexity: O(n)
    //Read the file of filename and return it as a concatenated string
    fstream fileStream(filename);
    string text="";
    if (fileStream.is_open()){
        string line;
        while(getline(fileStream,line)){
            text+=line;
        }
    }
    return text;
}

struct Bitacora {
   std::string mes;
   int dia;
   std::string hora;
   std::string ipOrigen;
   std::string razonFalla;
};
