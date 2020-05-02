### Taller 1: OpenMP


Clonar la carpeta
```
git clone 
```

Para compilar el archivo main se debe considerar el siguiente comando:
```
g++ main.cpp -o ./main
```
Tras esto se ha generado el csv correspondiente a **puntajes.csv**

## Secuencial
Comando de compilacion
```
g++ secuelcial.cpp -o ./secuencial
```
Comando para su ejecución
```
./secuencial file=puntajes.csv
```
## Dart

Comando de compilacion
```
g++ main.dart -o ./main
```
Comando para su ejecución
```
dart ./main file=puntajes.csv
```

## OpenMP

Comando de compilacion
```
g++ openMP.cpp -o ./openMP
```
Comando para su ejecución
```
./openMP file=puntajes.csv
```
---
# Nota: Se debe ejecutar main.cpp primeramente para que se genere el archivo .csv, y luego epecificarlo en la ruta del archivo para su posterior ejecución
