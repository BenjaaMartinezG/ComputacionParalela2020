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
#include "mpi.h"
#define LARGO 100

using namespace std;

//Structs
struct score
{
  //Vector que guardará los numeros que aparecen en el listado
  std::vector<float> uniqueNumbers;
  //Vector que guardará la cantidad de veces que se vio el numero en uniqueNumbers
  std::vector<int> totalViewed;
  //float que guarda la suma de todos los valores
  double summedValues;
};

//Functions
std::vector<std::string> split(std::string line, char delimiter);
void printScore(std::string name, int cont, struct score st);
void integrantes();
void manageScore(double number, struct score &st);
float calculateModa(struct score st);
float calculateDev(struct score st, int cont);
float calculateMediana(struct score st);
void sort(std::vector<float> &arr);
void mergeSort(vector<float> &left, vector<float> &right, vector<float> &bars);
float Stdev(const std::vector<float> &moments);

bool isAnyOk(bool *procesados, int largo) {
    bool result = false;
    for (int i = 0; i < largo; i++) {
        bool ok = procesados[i];
        if (ok) {
            result = true;
        }
    }
    return result;
}

int main(int argc, char** argv) 
{
    struct score nemScore, rankingScore, mathScore, LangScore, CienScore, HistScore;
    long int cont = 19932391 - 14916641;
    int mi_rango; /* rango del proceso    */
    int procesadores; /* numero de procesos   */
    int maestro = 0; /* Identificador maestro */
    int escritor = 1; /* Procesador escritor */
    int tag = 0; /* etiqueta del mensaje */
    MPI_Status estado; /* devuelve estado al recibir*/

    /* Este string se usara para detener los hilos paralelos */
    std::string parar("STOP");

    if (argc > 1) {
        /* Comienza las llamadas a MPI */
        MPI_Init(&argc, &argv);
        /* Averiguamos el rango de nuestro proceso */
        MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
        /* Averiguamos el número de procesos que estan 
         * ejecutando nuestro porgrama 
         */
        MPI_Comm_size(MPI_COMM_WORLD, &procesadores);
        if (procesadores < 3) 
        {
            fprintf(stderr, "\nLa implementación requiere al menos 3 procesadores\n");
            return EXIT_FAILURE;
        }
        if (mi_rango == 0) {
            std::ifstream inFile(argv[1]);
            if (inFile) {
                int procesador = 2;
                for (std::string line; getline(inFile, line);) {
                    if (!line.empty()) {
                        MPI_Send((char *) line.c_str(), line.length() + 1, MPI_CHAR, procesador, tag, MPI_COMM_WORLD);
                        procesador += 1;
                        if (procesador >= procesadores) {
                            procesador = 2;
                        }
                    }
                }
                std::cout << std::endl;
                for (procesador = 2; procesador < procesadores; procesador++) {
                    MPI_Send((char *) parar.c_str(), parar.length() + 1, MPI_CHAR, procesador, tag, MPI_COMM_WORLD);
                }
                inFile.close();
            }
            printScore("NEM", cont, nemScore);
            printScore("RANKING", cont, rankingScore);
            printScore("MATEMATICAS", cont, mathScore);
            printScore("LENGUAJE", cont, LangScore);
            printScore("CIENCIAS", cont, CienScore);
            printScore("HISTORIA", cont, HistScore);
            integrantes();
        } else if (mi_rango == 1) {
            bool procesados[procesadores];
            for (int i = 0; i < procesadores; i++) {
                procesados[i] = true;
            }
            procesados[0] = false;
            procesados[1] = false;

            while (isAnyOk(procesados, procesadores)) {
                for (int procesador = 2; procesador < procesadores; procesador++) {
                    if (procesados[procesador]) {
                        char* escritura = (char *) calloc(LARGO, sizeof (char));
                        MPI_Recv(escritura, LARGO, MPI_CHAR, procesador, tag, MPI_COMM_WORLD, &estado);
                        std::string texto(escritura);
                        if (parar.compare(texto) == 0 || texto.empty()) {
                            procesados[procesador] = false;
                        } else {
                            std::vector<std::string> splitedLine;
                            splitedLine = split(texto, ';');
                            manageScore(std::stoi(splitedLine[1]), nemScore);
                            manageScore(std::stoi(splitedLine[2]), rankingScore);
                            manageScore(std::stoi(splitedLine[3]), mathScore);
                            manageScore(std::stoi(splitedLine[4]), LangScore);
                            manageScore(std::stoi(splitedLine[5]), CienScore);
                            manageScore(std::stoi(splitedLine[6]), HistScore);
                        }
                        free(escritura);
                    }
                }
            }
        } else {
            /* Obtengo el mensajes */
            while (true) {
                char* mensaje = (char *) calloc(LARGO, sizeof (char));
                MPI_Recv(mensaje, LARGO, MPI_CHAR, maestro, tag, MPI_COMM_WORLD, &estado);
                std::string fila(mensaje);
                if (parar.compare(fila) == 0 || fila.empty()) {
                    // No hay datos, se debe salir del loop
                    MPI_Send((char *) parar.c_str(), parar.length() + 1, MPI_CHAR, escritor, tag, MPI_COMM_WORLD);
                    break;
                } else {
                    std::vector<std::string> splitedLine;
                    splitedLine = split(fila, ';');
                    nemScore.summedValues += std::stoi(splitedLine[1]);
                    rankingScore.summedValues += std::stoi(splitedLine[2]);
                    mathScore.summedValues += std::stoi(splitedLine[3]);
                    LangScore.summedValues += std::stoi(splitedLine[4]);
                    CienScore.summedValues += std::stoi(splitedLine[5]);
                    HistScore.summedValues += std::stoi(splitedLine[6]);
                    MPI_Send((char *) fila.c_str(), fila.length() + 1, MPI_CHAR, escritor, tag, MPI_COMM_WORLD);
                }
                free(mensaje);
            }


        }

        /* Termina con MPI. Recordemos que después de 
         * esta llamada no podemos llamar a funciones 
         * MPI, ni siquiera de nuevo a MPI_Init 
         */
        MPI_Finalize();
    }
    /**
     * 
     * Muestro los participantes.
     */


    return EXIT_SUCCESS;
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

void printScore(std::string name, int cont, struct score st)
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

void manageScore(double number, struct score &st)
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

float calculateDev(struct score st, int cont)
{
  float average = st.summedValues / cont;
  float variance = 0.0;
  for (int i = 0; i < st.uniqueNumbers.size(); i++)
  {
    variance += pow((st.uniqueNumbers[i] - average), 2.0);
  }
  return sqrt(variance / st.uniqueNumbers.size());
}

float calculateMediana(struct score st)
{
  //Primero se deben ordenar los valores
  int totalScores = st.uniqueNumbers.size();
  int halfIndex = totalScores / 2;
  sort(st.uniqueNumbers);
  if (totalScores % 2 == 0)
  {
    return (st.uniqueNumbers[halfIndex - 1] + st.uniqueNumbers[halfIndex]) / 2;
  }
  else
  {
    return st.uniqueNumbers[halfIndex];
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