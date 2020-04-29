
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

float getAvegare(std::vector<std::string> califications);
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
    std::ifstream inFile(csvDir[1]);
    std::ofstream outFile("avegares.csv");
    if (inFile.fail())
    {
      inFile.close();
      outFile.close();
      throw "No se ha podido abrir el archivo";
    }
    std::cout << "Leyendo...";
    while (!inFile.eof())
    {
      float avegare;
      std::string line;
      std::vector<std::string> splitedLine;
      splitedLine = split(line, ';');
      avegare = getAvegare(splitedLine);
      outFile << splitedLine[0] << ";" << avegare << endl;
    }
    inFile.close();
    outFile.close();
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

float getAvegare(std::vector<std::string> califications)
{
  float sum = 0.0, prom = 0.0;
  for (int i = 1; i <= califications.size(); i++)
  {
    int actualCalification;
    std::istringstream(califications[i]) >> actualCalification;
    sum += actualCalification;
  }
  return califications.size() - 1;
}
