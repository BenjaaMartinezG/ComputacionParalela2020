# Taller 03 - Semana 04 CPD

Se solicita a cada grupo que desarrolle un programa, que usando el archivo de puntajes (disponible en moodle), calcule los siguientes elementos:
* Promedio.
* Desviación estándar.
* Moda.
* Mediana.

Para cada una de las siguientes columnas del archivo de entrada:
* Nem.
* Ranking.
* Matemática.
* Lenguaje.
* Ciencias.
* Historia.
### Implementacion
* Se necesita una implementación Secuencial en C/C++ .
* Se necesita una implementación Secuencial en Dart .
* Se necesita una implementación en C/C++ que use OpenMP .
* Se necesita una implementación en C/C++ que use (Open)MPI
### Nota: Se debe tener el archivo puntajes.csv para poder trabajar con él, si no lo tiene, se genera uno en main.cpp de la siguiente manera:
```
g++ main.cpp -o ./main
./main
```
## Secuencial
Comando para poder compilar y ejecutar el archivo Secuencial.cpp respectivamente (se debe conocer la ruta del archivo puntajes.csv para ingresarla en la ejecucion, se mostrará un ejemplo):
```
g++ Secuencial.cpp -o ./Secuencial
./Secuencial /media/Compartido/puntajes.csv
```
## DART
Comando para Compilar y ejecutar main.dart respectivamente:
```
dart ./main.dart /media/Compartido/puntajes.csv
```
## OpenMP
Comandos para Compilar y ejecutar el archivo openMP.cpp respectivamente:
```
g++ openMP.cpp -o ./openMP -fopenmp
./openMP /media/Compartido/puntajes.csv
```
## OpenMPI
Para esto se deben tener 3 maquinas funcionando, conectadas mediante ssh y ubicar este archivo en una carpeta compartida entre ellas, para luego ejecutar:
