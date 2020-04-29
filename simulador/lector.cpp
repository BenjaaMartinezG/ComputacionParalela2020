
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

float promedio(std::vector<std::string> newVector);

int main(int argc, char **argv)
{

  //se debe señalar la ruta del archivo
  std::string line, root;
  ifstream archivo(root);
  //inicializamos un vector para almacenar los datos del archivo
  std::vector<std::string> newVector;

  if (archivo.fail())
  {
    std::cerr << "Error al abrir Archivo";
  }
  else
  {
    //escribimos en el archivo
    ofstream salidaArchivo("promedio.csv", ios::trunc);
    if (salidaArchivo.fail())
    {
      std::cerr << "Error al abrir Archivo";
    }
    else
    {
      while (!archivo.eof())
      {
        getline(archivo, line);
        //newVector = funcionSplit(line);
        /*
               ...
               ...
               */

        newVector.clear();
      }
    }
    salidaArchivo.close();
  }

  archivo.close();
}

//funcion que agarra en el vector los puntajes y los promedia
float promedio(std::vector<std::string> newVector)
{
  float suma = 0.0, prom = 0.0;

  for (int i = 0; i <= newVector.size(); i++)
  {
    //stoi() convierte de string a numeros
    suma = suma + stoi(newVector[i]);
  }
  //redondea a entero
  prom = rint(prom);
  prom = suma / 6;

  return prom;
}
