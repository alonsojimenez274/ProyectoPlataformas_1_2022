//Alonso Jiménez Villegas
//B94125
//Programación bajo plataformas abiertas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//En este primer Void lo que se va haciendo es mostrando la matriz del laberinto que se quiere
//resolver. Se definen i y j como filas y columnas.
void mostrar(char **matriz, int m, int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            printf("%c", *(*(matriz + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

//Aquí se hace la función "leer" para que el programa pueda leer el archivo en el que se
//encuentra el laberinto
void leer(char **lineas, char *archivo, int *ancho, int *largo, int *posicionY, int *posicionX){
    char array[2048];
    int col = 0;
    int fila = 0;
    FILE *texto;
    texto = fopen(archivo, "r");
    
    // Se utiliza un ciclo while para evaluar el archivo de principio a fin.
    // Mientras que no se encuentre el final del archivo.
    while (fscanf(texto, "%c", array) != EOF){
        if (*array == '\n'){
            lineas[fila][col] = *array;
            fila++;
            col = 0;
        }

        else{
            lineas[fila][col] = *array;
            col++;
        }
        *ancho = col;
    }
    *largo = fila;

    //Con esto se tiene una evaluación de los bordes del laberinto para ver
    //en donde es que se puede empezar a resolverlo.
    for (int i = 0; i < *largo; i++){
        for (int j = 0; j < *ancho; j++){
            if (lineas[i][j] == '1' && (j == *ancho - 1 || i == *largo - 1 || j == 0 || i == 0)){
                *posicionX = j;
                *posicionY = i;
            }
            break;
        }
        printf("%i", *posicionX);
        printf("%i", *posicionY);
    }

}



//Esta función es en la que se definirá el tamaño de la matriz donde se guardará el
//laberinto.
char **crear(int n, int m){
    int j;
    char **matriz = (char **)malloc(m * sizeof(char *));
    for (j = 0; j < m; j++){
        *(matriz + j) = (char *)malloc(n * sizeof(char));
    }
    return matriz;
}

//Se crea la función que ayudará a buscar el mejor camino para la resolución del laberinto.
void resolverlaberinto(char **matriz, int i, int j, int *ancho, int *largo){
    for (int i; i > *largo; i++){
        for (int j; j > *ancho; j++){
            if (j > *ancho){
                break;
            };
        }
        if (i > *largo){
            break;
        };
    }
    
    if (matriz[i][j] == '2' || matriz[i + 1][j] == '2' || matriz[i - 1][j] == '2' || matriz[i][j + 1] == '2' || matriz[i][j - 1] == '2'){
        printf("Se encontró el camino con la solución.\n");
    }
    else{
        //Con esto, cada vez que se va encontrando un 1, se deja un punto para indicar que ya se utilizó el camino anterior.
        //Esto se hace par acada una de las posiciones (arriba, abajo, izquierda y derecha).
        //Al usar el método recursivo (función recursiva), en cada una de las condiciones se vuelve a llamar a
        //la función "resolverlaberinto" para volver a definir la posición en la que se encuentra.
        if (matriz[i + 1][j] == '1'){
            matriz[i + 1][j] = '.';
            mostrar(matriz, *ancho, *largo);
            resolverlaberinto(matriz, i + 1, j, ancho, largo);
        }
        else{
            if (matriz[i - 1][j] == '1'){
                matriz[i - 1][j] = '.';
                mostrar(matriz, *ancho, *largo);
                resolverlaberinto(matriz, i - 1, j, ancho, largo);
            }
            else{
                if (matriz[i][j + 1] == '1'){
                    matriz[i][j + 1] = '.';
                    mostrar(matriz, *ancho, *largo);
                    resolverlaberinto(matriz, i, j + 1, ancho, largo);
                }
                else{
                    if (matriz[i][j - 1] == '1'){
                        matriz[i][j - 1] = '.';
                        mostrar(matriz, *ancho, *largo);
                        resolverlaberinto(matriz, i, j - 1, ancho, largo);
                    }
                    else{
                        if (matriz[i + 1][j] == '.'){
                            matriz[i][j] = ':';
                            mostrar(matriz, *ancho, *largo);
                            resolverlaberinto(matriz, i + 1, j, ancho, largo);
                        }
                        else{
                            //Luego, con la misma lógica, si por el camino se está encontrando un punto, indicando que ya se pasó por ahí,
                            //Se deja un ":" para indicar que ya se pasó por el mismo camino dos veces.
                            if (matriz[i - 1][j] == '.'){
                                matriz[i][j] = ':';
                                mostrar(matriz, *ancho, *largo);
                                resolverlaberinto(matriz, i - 1, j, ancho, largo);
                            }
                            else{
                                if (matriz[i][j + 1] == '.'){
                                    matriz[i][j] = ':';
                                    mostrar(matriz, *ancho, *largo);
                                    resolverlaberinto(matriz, i, j + 1, ancho, largo);
                                }
                                else{
                                    if (matriz[i][j - 1] == '.'){

                                        matriz[i][j] = ':';
                                        mostrar(matriz, *ancho, *largo);
                                        resolverlaberinto(matriz, i, j - 1, ancho, largo);
                                    }
                                    //Si al final nunca se encontró el 2 indicando la solución, el laberinto propuesto
                                    //no tiene una posible solución.
                                    else{
                                        printf("No se encontró solución al laberinto.");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


int main(int argc, char *argv[]){
    printf("%s", argv[0]);
    printf("%s", argv[1]);
    printf("%s", argv[2]);
    printf("\n");

    if (argc != 2){
        printf("Error: el código necesita recibir el archivo con el laberinto como primer argumento\nNo acepta más de un argumento\n");
    }
    else{
        int a, l, ogX, ogY;
        int *pa = &a;
        int *pl = &l;
        int *pogX = &ogX;
        int *pogY = &ogY;
        char **laberinto = crear(1000, 1000);
        leer(laberinto, argv[1], pa, pl, pogX, pogY);
        printf("\n");
        printf("Este es el laberinto a resolver:\n");
        mostrar(laberinto, a, l);
        resolverlaberinto(laberinto, ogX, ogY, pa, pl);
    }
}
