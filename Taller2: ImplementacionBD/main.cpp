#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "db.h"

int main(int argc, char **argv)
{
  try
  {
    // Se inicializa la conexión a la DB
    PGconn *connection = dbconnect((char *)DBSERVER, DBPORT, (char *)DBNAME, (char *)DBUSER, (char *)DBPASSWORD);
    // Se obtiene el resultado de la query que calcula promedio
    PGresult *result = dbquery(connection, (char *)("select rut, cast(sum(nem+ranking+matematica+lenguaje+ciencias+historia) as decimal)/6 from puntajes group by rut"));
    // Numero de filas totales del resultado
    long totalRows = dbnumrows(result);
    int i = 0;
    // Inicializacion del archivo de salida
    std::ofstream outFile("promedios.csv");
    for (i = 0; i < totalRows; i++)
    {
      char *rut = dbresult(result, i, 0);     // La primera columna es el rut
      char *average = dbresult(result, i, 1); //La segunda columna es el promedio calculado
      // Se escribe en el archivo
      outFile << rut << ";" << average << std::endl;
    }
    // Se libera la conexión a la db
    dbfree(result);
    // Se cierra el archivo de escritura
    outFile.close();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}