## Taller 1: OpenMP

Para clonar la carpeta
```
git clone https://github.com/BenjaaMartinezG/ComputacionParalela2020.git
```
Primero se debe compilar el archivo main considerando el siguiente comando:
```
g++ main.cpp -o ./main
```
Tras esto se ha generado el csv correspondiente a **puntajes.csv**

## Secuencial
Comando de compilacion
```
g++ secuencial.cpp -o ./secuencial
```
Comando para su ejecución
```
./secuencial file=puntajes.csv
```

## Dart
Comando de compilacion
```
dart main.dart
```
Comando para su ejecución
```
dart ./main file=puntajes.csv
```

## OpenMP
Comando de compilacion
```
g++ openMP.cpp -o ./openMP -fopenmp
```
Comando para su ejecución
```
./openMP file=puntajes.csv
```
---
#### Nota: Se debe ejecutar main.cpp primeramente para que se genere el archivo .csv, y luego epecificarlo en la ruta del archivo para su posterior ejecución
