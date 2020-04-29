#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int num_aleatorio(int mayor, int menor)
{
  return (rand() % (mayor - (menor + 1)) + menor);
}

int main()
{

  srand((unsigned int)time(0));

  ofstream archivoFinal("promedio.csv");
  ofstream archivoSalida("puntajes.csv");

  for (int rut = 14916641; rut < 19679045; rut++)
  {
    int nem = num_aleatorio(750, 450),
        ranking = num_aleatorio(750, 450),
        matematica = num_aleatorio(750, 450),
        lenguaje = num_aleatorio(750, 450),
        ciencias = num_aleatorio(750, 450),
        historia = num_aleatorio(750, 450);

    archivoSalida << rut << ";";
    archivoSalida << nem << ";";
    archivoSalida << ranking << ";";
    archivoSalida << matematica << ";";
    archivoSalida << lenguaje << ";";
    archivoSalida << ciencias << ";";
    archivoSalida << historia << endl;

    int promedio = (nem + ranking + lenguaje + matematica + ciencias + historia) / 6;

    archivoFinal << rut << ";"
                 << "Promedio " << promedio << ";" << endl;
  }

  archivoSalida.close();
  archivoFinal.close();
}
