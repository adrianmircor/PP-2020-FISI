/*
 ============================================================================
 Name        : Pth_fibonacci.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que retorna el elemento hallado de
acuerdo a su posicion en la serie fibonacci.

 La serie fibonacci empieza en 1 1
 El PRIMER elemento hallado seria el 2: {1 1 (2)}
 El SEGUNDO elemento hallado seria el 3: {1 1 2 (3)}

 Cada hilo resolverá la misma cantidad de operaciones, por lo cual
 la posicion a ser hallada debe ser multiplo de la cantidad de hilos a utilizar.

 El usuario introduce que elemento(posicion) de la serie desea hallar

 Para compilar: gcc -g -Wall -o fibo Pth_fibonacci.c -lpthread -lm
 Para ejecutar: ./fibo <nro de hilos a utilizar>
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variable: */
int thread_count;
int fib[2] = {1,1};
int res = 0;
int posSerie;
int c;
pthread_mutex_t mutex;

/* Thread function */
void *fibonacci(void *rank);

int main(int argc, char* argv[]) {

	long thread; /* Use long in case of a 64 − bit system */
	pthread_t* thread_handles;

	/* Get number of threads from command line */
	printf("Serie fibonacci \n  ");
	printf("Nota:\nLa serie empieza en 1 1 \nEl PRIMER elemento HALLADO es 2: {1 1 (2)} \nEl SEGUNDO elemento HALLADO es 3: {1 1 2 (3)}\n");
	printf("\n");

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	printf("->Introduzca la posición del elemento que desea hallar (Multiplo a la cantidad de hilos: %d",thread_count);
	printf("): \n ");
	scanf("%d",&posSerie);

	pthread_mutex_init(&mutex, NULL);

	for (thread = 0; thread < thread_count; thread++){
		pthread_create(		&thread_handles[thread], //Arreglo de punteros de ID de los hilos
							NULL, //Null por defecto
							fibonacci, //Funcion a correr por el hilo
							(void*) thread	); //Argumento de la Funcion que debe retornar un void
	}

	//Une a los threads
	for (thread = 0; thread < thread_count; thread++){
		pthread_join(	thread_handles[thread],
						NULL	);
	}

	 printf("Resultado: %d \n", res);

	 pthread_mutex_destroy(&mutex);

	free(thread_handles); //libera memoria de array de punteros de los hilos
	return 0;
}/* main */

void* fibonacci(void* rank) {

	int my_rank = (long) rank;
	int m = posSerie / thread_count;

   pthread_mutex_lock(&mutex);
	for (int var = 0; var < m; var++) {
		res = fib[0] + fib[1];
		fib[0] = fib[1];
		fib[1] = res;
	}
   pthread_mutex_unlock(&mutex);

	return NULL;
}/* Hello */
