#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <assert.h>

using namespace std;

//Structs
struct score
{
  //Vector que guardará los numeros que aparecen en el listado
  std::vector<float> uniqueNumbers;
  //Vector que guardará la cantidad de veces que se vio el numero en uniqueNumbers
  std::vector<long int> totalViewed;
  //float que guarda la suma de todos los valores
  long double summedValues;
};

//Functions
std::vector<std::string> split(std::string line, char delimiter);
void printScore(std::string name, long int cont, struct score st);
void integrantes();
void manageScore(long double number, struct score &st);
float calculateModa(struct score st);
float calculateDev(struct score st, long int cont);
float calculateMediana(struct score st);
void sort(std::vector<float> &arr);
void mergeSort(vector<float> &left, vector<float> &right, vector<float> &bars);
float Stdev(const std::vector<float> &moments);

int main(int argc, char **argv)
{
  struct score nemScore, rankingScore, mathScore, LangScore, CienScore, HistScore;
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
    long int cont = 0;
    std::vector<std::string> splitedLine;
    while (std::getline(inFile, line))
    {
      std::istringstream iss(line);
      splitedLine = split(line, ';');
      /*
        Obtenemos la suma de todos los puntajes de
        NEM, Ranking, Matematica, Lenguaje, Ciencias e Historia respectivamente
      */
      nemScore.summedValues += std::stoi(splitedLine[1]);
      rankingScore.summedValues += std::stoi(splitedLine[2]);
      mathScore.summedValues += std::stoi(splitedLine[3]);
      LangScore.summedValues += std::stoi(splitedLine[4]);
      CienScore.summedValues += std::stoi(splitedLine[5]);
      HistScore.summedValues += std::stoi(splitedLine[6]);

      // Se manejan los valores en structs por separado
      manageScore(std::stoi(splitedLine[1]), nemScore);
      manageScore(std::stoi(splitedLine[2]), rankingScore);
      manageScore(std::stoi(splitedLine[3]), mathScore);
      manageScore(std::stoi(splitedLine[4]), LangScore);
      manageScore(std::stoi(splitedLine[5]), CienScore);
      manageScore(std::stoi(splitedLine[6]), HistScore);

      //Contador de personas
      cont++;
    }

    //llamado a funcione con todo el contenido que se pide
    printScore("NEM", cont, nemScore);
    printScore("RANKING", cont, rankingScore);
    printScore("MATEMATICAS", cont, mathScore);
    printScore("LENGUAJE", cont, LangScore);
    printScore("CIENCIAS", cont, CienScore);
    printScore("HISTORIA", cont, HistScore);
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

void printScore(std::string name, long int cont, struct score st)
{
  std::cout << "\n===" << name << "===" << std::endl
            << "Promedio: " << st.summedValues / cont << std::endl
            << "Desviacion Estandar: " << calculateDev(st, cont) << std::endl
            << "Moda: " << calculateModa(st) << std::endl
            << "Mediana: " << calculateMediana(st) << std::endl;
}

void integrantes()
{
  std::cout << "\n=== Integrantes ===" << std::endl
            << "Jose Carvallo" << std::endl
            << "Luis Felipe Jana" << std::endl
            << "Benjamin Martinez" << std::endl;
}

void manageScore(long double number, struct score &st)
{
  int index;
  bool isOnVector = false;
  for (int i = 0; i < st.uniqueNumbers.size(); i++)
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

float calculateModa(struct score st)
{
  int bigestIndex = 0;
  for (int i = 0; i < st.totalViewed.size(); i++)
  {
    if (st.totalViewed[i] > bigestIndex)
    {
      bigestIndex = i;
    }
  }
  return st.uniqueNumbers[bigestIndex];
}

float calculateDev(struct score st, long int cont)
{
  float average = st.summedValues / cont;
  float variance = 0;
  for (int i = 0; i < st.uniqueNumbers.size(); i++)
  {
    variance += pow((st.uniqueNumbers[i] - average), 2.0);
  }
  return sqrt(variance / st.uniqueNumbers.size() - 1);
}

float calculateMediana(struct score st)
{
  //Primero se deben ordenar los valores
  int totalScores = st.uniqueNumbers.size();
  int halfIndex = totalScores / 2;
  sort(st.uniqueNumbers);
  if (totalScores % 2 == 0)
  {
    return (st.uniqueNumbers[halfIndex] + st.uniqueNumbers[halfIndex]) / 2;
  }
  else
  {
    return st.uniqueNumbers[halfIndex - 1];
  }
}

void sort(vector<float> &bar)
{
  if (bar.size() <= 1)
    return;

  int mid = bar.size() / 2;
  vector<float> left;
  vector<float> right;

  for (size_t j = 0; j < mid; j++)
    left.push_back(bar[j]);
  for (size_t j = 0; j < (bar.size()) - mid; j++)
    right.push_back(bar[mid + j]);

  sort(left);
  sort(right);
  mergeSort(left, right, bar);
}
void mergeSort(vector<float> &left, vector<float> &right, vector<float> &bars)
{
  int nL = left.size();
  int nR = right.size();
  int i = 0, j = 0, k = 0;

  while (j < nL && k < nR)
  {
    if (left[j] < right[k])
    {
      bars[i] = left[j];
      j++;
    }
    else
    {
      bars[i] = right[k];
      k++;
    }
    i++;
  }
  while (j < nL)
  {
    bars[i] = left[j];
    j++;
    i++;
  }
  while (k < nR)
  {
    bars[i] = right[k];
    k++;
    i++;
  }
}
