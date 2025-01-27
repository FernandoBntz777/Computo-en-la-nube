#include <iostream>
#include <omp.h>
#include <cstdlib> // Para atoi
using namespace std;

void imprimeArreglo(float *d, int mostrar);

int main(int argc, char *argv[]) {
    // Parámetros configurables
    int N = 1000;          // Tamaño del arreglo por defecto
    int chunk = 100;       // Chunk por defecto
    int mostrar = 10;      // Cantidad de valores a mostrar por defecto

    // Leer parámetros desde la línea de comandos
    if (argc > 1) N = atoi(argv[1]);
    if (argc > 2) chunk = atoi(argv[2]);
    if (argc > 3) mostrar = atoi(argv[3]);

    cout << "Sumando Arreglos en Paralelo!" << endl;
    cout << "Tamaño de los arreglos: " << N << ", Chunk: " << chunk
         << ", Mostrar: " << mostrar << endl;

    float *a = new float[N];
    float *b = new float[N];
    float *c = new float[N];

    // Inicialización de los arreglos
    for (int i = 0; i < N; i++) {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    // Suma en paralelo
    #pragma omp parallel for shared(a, b, c) schedule(static, chunk)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Imprimir resultados
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(a, mostrar);

    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
    imprimeArreglo(b, mostrar);

    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
    imprimeArreglo(c, mostrar);

    // Liberar memoria
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

void imprimeArreglo(float *d, int mostrar) {
    for (int i = 0; i < mostrar; i++) {
        cout << d[i] << " ";
    }
    cout << endl;
}