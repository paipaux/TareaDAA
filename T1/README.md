# Tarea 1: Bulk-loading de R-trees

## Estructura del Proyecto

```
T1/
│
├── datasets/ # Archivos de los datasets (.bin)
│ └── europa.bin
│ └── random.bin
│
├── src/ # Código fuente (.c)
│ ├── arboles.h # Definición de las estructuras Hijo, Nodo y MBR
│ ├── comparaciones.c # Funciones auxiliares para comparar los puntos x e y
│ ├── construccion.c # Crea 4 R-trees mediante bulk-loading
│ ├── consultar.c # Función para realizar una consulta
│ ├── consultas.c # Consulta usando los 4 R-trees con 𝑁 = 2^(24) elementos que se construyeron
│ ├── crearNX.c # Función para crear un R-tree usando Nearest-X
│ ├── crearSTR.c # Función para crear un R-tree usando SortTileRecursive
│ ├── escribir.c
│
├── Makefile # Instrucciones simples de compilación
└── README.md # Este archivo
```

-----DE AQUI EN ADELANTE NO LO HE CAMBIADOOOO

## Compilación

Para compilar los programas, ejecuta:

```bash
make
```

Esto generará dos ejecutables en la raíz del proyecto:

- `create_tree`: Programa para crear y serializar el árbol de búsqueda binaria
- `search_value`: Programa para buscar un valor en el árbol de búsqueda binaria

## Uso

### 1. Crear y serializar el árbol

```bash
./create_tree
```

Este comando creará el archivo `tree.bin` en la raíz del proyecto.
Se puede modificar el árbol en el archivo `src/create_tree.cpp`.

### 2. Buscar un valor en el árbol BST

```bash
./search_value X
```

Donde `X` es el valor que deseas buscar en el árbol.

Por ejemplo, para buscar el valor `80`:

```bash
./search_value 80
```

Lo que debería imprimir:

```bash
Buscando valor 80:
Nodo: id=7, value=80
  No tiene hijo izquierdo
  Hijo derecho: id=9, value=90
```

## Limpieza

Para limpiar los archivos generados:

```bash
make clean
```
