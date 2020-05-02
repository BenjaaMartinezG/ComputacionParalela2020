#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <iomanip>
#include <omp.h>

using namespace std;

std::vector<std::string> split(std::string line, char delimiter);

int main(int argc, char **argv)
{
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
    std::ofstream outFile("promedio.csv");
    std::string line;
    float average;
    std::vector<std::string> splitedLine;

#pragma omp parallel
    {

#pragma omp for

      for (int rut = 14916641; rut < 19932391; rut++)
      {
        if (std::getline(inFile, line))
        {
          std::istringstream iss(line);
          splitedLine = split(line, ';');
          average = (std::stoi(splitedLine[1]) + std::stoi(splitedLine[2]) + std::stoi(splitedLine[3]) + std::stoi(splitedLine[4]) + std::stoi(splitedLine[5]) + std::stoi(splitedLine[6])) / 6;

#pragma omp critical
          outFile << splitedLine[0] << ";" << average << endl;
        }
      }
      inFile.close();
      outFile.close();
    }
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
