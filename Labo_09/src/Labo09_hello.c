#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count; //variable que guarda la cantidad de hilos, todos los hilos puedenb hacer uso

void *Hello(void *rank);

int main(int argc, char *argv[]){
	long thread;
	pthread_t* thread_handles;

	printf("argv[1]: %s \n", argv[1]);
	thread_count = strtol(argv[1], NULL, 10); //convierte string a long

	thread_handles = malloc (thread_count *sizeof(pthread_t));
	for (thread= 0; thread< thread_count; thread++) {
		pthread_create(
				&thread_handles[thread], //puntero de sallida, uso de mas de 1 thread
				NULL, //atributo de thread
				Hello, //funcion
				(void*) thread); //argumentos de la funcion
	}

	printf("hello from the main-------- thread\n");

	for (thread= 0; thread< thread_count; thread++) {
			pthread_join(thread_handles[thread],NULL);

		}

	free(thread_handles);

	return 0;
}

void *Hello(void *rank){
	long my_rank = (long) rank;

	printf("hello from thread %ld of %d\n", my_rank, thread_count);

	return NULL;
}
