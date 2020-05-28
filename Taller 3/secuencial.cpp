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

//Structs
struct median
{
  //Vector que guardará los numeros que aparecen en el listado
  std::vector<float> uniqueNumbers;
  //Vector que guardará la cantidad de veces que se vio el numero en uniqueNumbers
  std::vector<long int> totalViewed;
};

//Functions
std::vector<std::string> split(std::string line, char delimiter);
void printScore(std::string name, float average, struct median st);
void integrantes();
void manageMedian(float number, struct median &st);
float calculateMedian(struct median st);

int main(int argc, char **argv)
{
  long int totalScores[6] = {0, 0, 0, 0, 0, 0};
  struct median nemMedian, rankingMedian, mathMedian, LangMedian, CienMedian, HistMedian;
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

      // Mediana
      manageMedian(std::stoi(splitedLine[1]), nemMedian);
      manageMedian(std::stoi(splitedLine[2]), rankingMedian);
      manageMedian(std::stoi(splitedLine[3]), mathMedian);
      manageMedian(std::stoi(splitedLine[4]), LangMedian);
      manageMedian(std::stoi(splitedLine[5]), CienMedian);
      manageMedian(std::stoi(splitedLine[6]), HistMedian);

      //Contador de personas
      cont++;
    }
    std::cout << nemMedian.totalViewed[0] << endl;

    //llamado a funcione con todo el contenido que se pide
    printScore("NEM", totalScores[0] / cont, nemMedian);
    printScore("RANKING", totalScores[1] / cont, rankingMedian);
    printScore("MATEMÁTICAS", totalScores[2] / cont, mathMedian);
    printScore("LENGUAJE", totalScores[3] / cont, LangMedian);
    printScore("CIENCIAS", totalScores[4] / cont, CienMedian);
    printScore("HISTORIA", totalScores[5] / cont, HistMedian);
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

void printScore(std::string name, float avegare, struct median st)
{
  std::cout << "\n===" << name << "===" << std::endl
            << "Promedio: " << avegare << std::endl
            << "Desviacion Estandar: " << std::endl
            << "Moda: " << calculateMedian(st) << std::endl
            << "Mediana: " << std::endl;
}

void integrantes()
{
  std::cout << "\n=== Integrantes ===" << std::endl
            << "Jose Carvallo" << std::endl
            << "Luis Felipe Jana" << std::endl
            << "Benjamin Martinez" << std::endl;
}

void manageMedian(float number, struct median &st)
{
  int index;
  bool isOnVector = false;
  for (int i = 0; st.uniqueNumbers.size(); i++)
  {
    if (st.uniqueNumbers[i] == number)
    {
      isOnVector = true;
      index = i;
    }
  }
  if (isOnVector)
  {
    st.totalViewed[index] += 1;
  }
  else
  {
    st.uniqueNumbers.push_back(number);
    st.totalViewed.push_back(1);
  }
}

float calculateMedian(struct median st)
{
  int bigestIndex = 0;
  for (int i = 0; st.totalViewed.size(); i++)
  {
    if (st.totalViewed[i] > bigestIndex)
    {
      bigestIndex = i;
    }
  }
  return st.uniqueNumbers[bigestIndex];
}