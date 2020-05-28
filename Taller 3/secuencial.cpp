#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <cmath>
#include <iomanip>

using namespace std;

//Functions
std::vector<std::string> split(std::string line, char delimiter);
void printScore(float average, std::string name);
void integrantes();

int main(int argc, char **argv)
{
  long int totalScores[6] = {0, 0, 0, 0, 0, 0};
  try
  {
    if (!argv[1])
    {
      throw "Especifica la ruta";
    }
    std::vector<std::string> csvDir;
    csvDir = split(argv[1], '=');
    cout << "Intentando abrir archivo " << csvDir[1] << endl;
    std::ifstream inFile(csvDir[1]);
    if (inFile.fail())
    {
      inFile.close();
      throw "No se ha podido abrir el archivo";
    }
    std::cout << "Leyendo..." << endl;
    std::string line;
    float cont = 0;
    std::vector<std::string> splitedLine;
    while (std::getline(inFile, line))
    {
      std::istringstream iss(line);
      splitedLine = split(line, ';');
      /*
        Obtenemos la suma de todos los puntajes de
        NEM, Ranking, Matematica, Lenguaje, Ciencias e Historia respectivamente
      */
      totalScores[0] += std::stoi(splitedLine[1]);
      totalScores[1] += std::stoi(splitedLine[2]);
      totalScores[2] += std::stoi(splitedLine[3]);
      totalScores[3] += std::stoi(splitedLine[4]);
      totalScores[4] += std::stoi(splitedLine[5]);
      totalScores[5] += std::stoi(splitedLine[6]);
      //Contador de personas
      cont++;
    }

    //llamado a funcione con todo el contenido que se pide
    printScore(totalScores[0] / cont, "NEM");
    printScore(totalScores[1] / cont, "RANKING");
    printScore(totalScores[2] / cont, "MATEMÁTICAS");
    printScore(totalScores[3] / cont, "LENGUAJE");
    printScore(totalScores[4] / cont, "CIENCIAS");
    printScore(totalScores[5] / cont, "HISTORIA");
    integrantes();

    inFile.close();
  }
  catch (const char *e)
  {
    std::cerr << e << '\n';
  }
}

std::vector<std::string> split(std::string line, char delimiter = ';')
{
  std::vector<std::string> splitedString;
  std::stringstream ss(line);
  std::string token;
  while (std::getline(ss, token, delimiter))
  {
    splitedString.push_back(token);
  }
  return splitedString;
}

void printScore(float avegare, std::string name)
{
  std::cout << "\n===" << name << "===" << std::endl
            << "Promedio: " << avegare << std::endl
            << "Desviacion Estandar: " << std::endl
            << "Moda: " << std::endl
            << "Mediana: " << std::endl;
}

void integrantes()
{
  std::cout << "\n=== Integrantes ===" << std::endl
            << "Jose Carvallo" << std::endl
            << "Luis Felipe Jana" << std::endl
            << "Benjamin Martinez" << std::endl;
}