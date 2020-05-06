# ComputacionParalela2020

## Taller - Semana 01

#### Programacion openMP

Usando el archivo generado durante la actividad del día de hoy. Se solicita un programa en
C/C++ que leyendo desde la línea de argumentos, _use este argumento como ruta del archivo
para procesar_.
El archivo generado en clases, tiene la siguiente estructura:

- Rut, valor de rut.
- Nem, valor entre 475 y 750.
- Ranking, valor entre 475 y 750.
- Matemática, valor entre 475 y 750.
- Lenguaje, valor entre 475 y 750.
- Ciencias, valor entre 475 y 750.
- Historia, valor entre 475 y 750.

El archivo que genera el programa **simular-omp** (visto en clases), genera un archivo separado por
‘;’ similar al ejemplo dado:
**Salida de ejemplo**

```
19932382;618;706;723;523;618;599
19932383;537;741;732;523;543;508
19932384;731;613;542;580;727;653
19932385;571;707;561;503;670;661
19932386;603;674;745;493;738;744
19932387;730;727;702;550;621;691
19932388;675;529;530;658;578;718
19932389;538;680;703;605;511;681
19932390;629;727;640;715;482;561
19932391;748;730;486;744;748;596
```

Se solicita a cada grupo que desarrolle un programa, que para cada rut de los generados en el
archivo anterior, realice un promedio de los puntajes y lo vuelque en un nuevo archivo.
**Ejemplo de salida:**

```
19932382;631.17
19932383;597.33
```

- _Se necesita una implementación **Secuencial en C/C++**._
- _Se necesita una implementación **Secuencial en Dart**._
- _Se necesita una implementación en **C/C++ que use OpenMP**._
