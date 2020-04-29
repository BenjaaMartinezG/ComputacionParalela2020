#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Funciones
int num_aleatorio(int mayor, int menor);

int score()
{

  srand((unsigned int)time(0));

  //ofstream archivoFinal("promedio.csv");
  //se inicializa y se abre el archivo
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
    archivoSalida << historia << ";" << endl;
  }

  archivoSalida.close();
  //archivoFinal.close();
}

int num_aleatorio(int mayor, int menor)
{
  return (rand() % (mayor - (menor + 1)) + menor);
}
