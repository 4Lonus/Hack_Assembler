# Informe de Ensamblador de Hack

## Integrantes
El grupo esta compuesto unicamente por Juan Pablo López, quien escribió, probo y refinó el codigo en su totalidad. La inteligecia artificail no fue utilizada para escribir codigo excepto en `Hack_Assembler/ensamblador/Code.hpp`, donde fue utilizada para generar los codigos de las tablas. Por otro lado, el codigo fue revisado contsantemente por DeepSeek V4.1 flash con proposito de encontrar posibles fallas.

## Arquitectura

Se usó la arquitectura sugerida en la presentación de la clase 18, para ambos programas, tanto el ensamblador como el desensamblador. Todo escrito en C++ con modulos:

- **Parser**: analiza (parsea) cada linea del archivo de entrada.
- **Code**: genera la traducción de la instrucción, de asm a hack y biceversa.
- **Symbol Table**: utilizada de maneras similares pero fundametalmente diferentes entre ensamblador y des ensamblador. El ensamblador lo usa para anotar todas los simbolos de las instrucciones y etiquetas encontradas, mientras que el desensamblador lo usa exclusivamente para anotar las posibles etiquetas encontradas.

Ambos codigos (ensamblador y desensamblador) utilizan la misma logica de primero buscar por etiquetas, agregarlas a la tabla de simbolos y despues manejar el codigo. Aún así el desensamblador tambien se ve forzado a hacer una "pasada cero" en donde cuenta las lineas totales del programa para poder posteriormente decidir si una posible etiqueta deberia incluirse en la tabla de simbolos.

## Tabla de Simbolos

Se usó un mapa desordenado (`unordered_map`) para guardar cada simbolo y su valor en el ensamblador, donde un valor (int) podia ser representado por varios simbolos (string), por ejemplo `R0` y `SP` ambos representan 0, y `R1` y `LCL` representan 1. Por otro lado se utilizo un mapa (`map`) en el desensamblador, en donde solo un simbolo (string) puede ser representado por una dirección (int positivo de 16 bits, `uint16_t`). Esta distinsion se basa en que el ensamblador necesita poder traducir a un valor numerico cualquier simbolo, mientras que el desensamblador necesita saber que nombre de etiqueta debe poner.

## Generación de Simbolos

La generacion de etiquetas en el desenamblador es en escencia un juego de supocisiones, puesto que las instrucciones tipo Label no se traducen a hack. Por esto mismo debemos seguir una regla generalpara suponer donde hay etiquetas.

Esta regla es la siguiente: sea `n` la cantidad de total de lineas en el programa, sea `i` la instrucción actual que se esta analizando, sea `i-1` la ultima instrucción, y sea `v` el valor de la instrucción `i-1` en caso de que sea tipo A...

- *"Si `i` es una instrucción tipo C, `i-1` es tipo A, y `v` es menor a `n`: en `v` hay una etiqueta."*

Aqui simplemente ponemos el nombre L + numero del label, e.g.: L0, L1, ..., Ln.

Un ejemplo de esto son las instrucciones 5 y 6 en `Prueba3.hack`:

```hack
0000000000001010
1110001100000001
```

Se traduce a dos instrucciones, un a tipo A y otra tipo C:

```asm
@12
D;JGT
```

Pero cuando evaluamos la instrucción C 1). nos damos cuenta que tiene una instrucción Jump, 2). vemos que la instruccion anterior era tipo A, y 3). vemos que el valor de la instruccion A (`12`) es menor al numero total de instrucciones (`16`), por ende, añadimos una etiqueta en la direccion `12` a la tabla de Simbolos.

## Manejo de Errores

Los errores se manejan de manera local. Dentro de cada funcion del parser, o dentro del proceso del main, si hay una entrada invalida se envia un error personalizado, el cual para el programa y hace que se imprima.

## Pruebas

Por realizar...