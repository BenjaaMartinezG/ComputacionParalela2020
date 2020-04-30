#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int num_aleatorio(int mayor, int menor);

int main(int argc, char **argv)
{
  srand((unsigned int)time(0));
  std::string pyc(";");

  std::ofstream archivoSalida("puntajes.csv");

#pragma omp parallel
  {

#pragma omp for
    for (unsigned long rut = 14916641; rut <= 19932391; rut++)
    {
      int nem = num_aleatorio(750, 450),
          ranking = num_aleatorio(750, 450),
          matematica = num_aleatorio(750, 450),
          lenguaje = num_aleatorio(750, 450),
          ciencias = num_aleatorio(750, 450),
          historia = num_aleatorio(750, 450);

      std::string linea;
      linea = std::to_string(rut) + pyc + std::to_string(nem) + pyc + std::to_string(ranking) + pyc + std::to_string(matematica) + pyc + std::to_string(lenguaje) + pyc + std::to_string(ciencias) + pyc + std::to_string(historia);

#pragma omp critical
      archivoSalida << linea << std::endl;
    }
  }
  archivoSalida.close();
}

int num_aleatorio(int mayor, int menor)
{
  return (rand() % (mayor - (menor + 1)) + menor);
}
