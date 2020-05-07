#ifndef DB_H
#define DB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <postgresql/libpq-fe.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DBSERVER "localhost"
#define DBPORT 5432
#define DBNAME "psudb"
#define DBUSER "psu"
#define DBPASSWORD "psu"

    PGconn* dbconnect(char* servidor, int puerto, char* nombredb, char* usuario, char* password);

    void dbclose(PGconn* conexion);

    PGresult* dbquery(PGconn* conexion, char* consulta);
    
    long dbnumrows(PGresult* resultado);
    
    char* dbresult(PGresult* resultado, int fila, int columna);
    
    void dbfree(PGresult *resultado);

#ifdef __cplusplus
}
#endif

#endif /* DB_H */

