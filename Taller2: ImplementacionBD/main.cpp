#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <db>

int main(int argc, char **argv)
{
  try
  {
    PGconn connection = dbconnect(DBSERVER, DBPORT, DBNAME, DBUSER, DBPASSWORD);
    PGresult result = dbquery(connection, "select rut, cast(sum(nem+ranking+matematica+lenguaje+ciencias+historia) as decimal)/6 from puntajes group by rut");
    long totalRows = dbnumrows(result);
    int i = 0;
    std::ofstream outFile("promedios.csv");
    for (i = 0; i < totalRows; i++)
    {
      // No se si empieza de la fila 0 y columna 0 *Probar
      char rut = dbresult(result, i, 0);
      char average = dbresult(result, i, 1);
      outFile << rut << ";" << avegare << endl;
    }
    dbfree(result);
    outFile.close();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}