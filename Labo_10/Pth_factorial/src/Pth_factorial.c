/*
 ============================================================================
 Name        : Pth_factorial.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description :  Programa que halla el factorial de cualquier numero (n)

Considerar que el numero del factorial a hallar debe ser >= al numero de hilos
Ya que si el numero de hilos es mayor, habrian hilos sin utilizar
con lo cual se desperdicia los recursos del sistema.

Se distribuye de forma ciclica los valores,
supongamos que deseamos hallar el factorial de 7 y el numero de hilos
a utilizar es 4,entonces la distribucion de los numeros seria asi:
h0 => 1 5
h1 => 2 6
h2 => 3 7
h3 => 4
Se calcula el producto de los valores de cada hilo, para que luego se guarden
en la variable global res.


 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variable: */
int thread_count;
int res=1;
int n;

/* Thread function */
void* factorial(void* rank);

int main(int argc, char* argv[]) {

	long thread; /* Use long in case of a 64 − bit system */
	pthread_t* thread_handles;

	/* Get number of threads from command line */
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	printf("Ingrese el Factorial que desee hallar: ");
	scanf("%d",&n);

	for (thread = 0; thread < thread_count; thread++){
		pthread_create(		&thread_handles[thread], //Arreglo de punteros de ID de los hilos
							NULL, //Null por defecto
							factorial, //Funcion a correr por el hilo
							(void*) thread	); //Argumento de la Funcion que debe retornar un void
	}

	//Une a los threads
	for (thread = 0; thread < thread_count; thread++){
		pthread_join(	thread_handles[thread],
						NULL	);
	}

	printf("El resultado del factorial es: %d",res);


	free(thread_handles); //libera memoria de array de punteros de los hilos
	return 0;
}/* main */

void* factorial(void* rank) {

	int my_rank= (long) rank;
	int data = my_rank + 1;

	do {
		res = res * data;
		data = data + thread_count;

	} while (data <= n);


	return NULL;
}/* Hello */
