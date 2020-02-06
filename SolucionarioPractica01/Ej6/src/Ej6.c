/*
 ============================================================================
 Name        : Ej6.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que luego de realizar la funcion Scatter, donde entrega
 a cada proceso la misma cantidad de elementos, realiza la busqueda de uno de ellos.
 Se busca en cada proceso el elemento, se aplica la funcion MPI_Reduce (MPI_SUM), y
 finalmente se le envia al proceso 0 la cantidad de veces que aparecio en cada proceso
 ese elemento a encontrar.

 Nota: El vector puede variar de longitud y elementos, pero debe ser divisible
 por la cantidad de procesos.

mpicc -g -Wall -o Ej6 Ej6.c
mpirun -n 3 Ej6 (puede ser 2,4,6,etc. Pero divisible por la longitud del array)


 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int rank; /* rank of process */

	int vectorOriginal[12] = { 1, 8, 4, 1, 0, 2, 1, 18, 20, 6, 1, 8 };

	int res = 0;
	int p; /* number of processes */

	/* start up MPI */

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm_size(MPI_COMM_WORLD, &p);

	//Array que sera asignado a cada proceso
	int vector[12/p];

	//Reparticion de los elementos a todos los procesos de forma equitativa
	MPI_Scatter(&vectorOriginal, 12 / p, MPI_INT,
				&vector, 12 / p, MPI_INT,
				0,MPI_COMM_WORLD);

	printf("Proceso %d", rank);
	printf(" tiene %d", (12 / p));
	printf(" valores: ");

	for (int i = 0; i < 12/p; i++) {
		printf("%d ", vector[i]);
	}

	printf("\n--------");

	//Buscar el elemento
	int acum = 0;
	for (int i = 0; i < 12 / p; i++) {

		if (1 == vector[i]) {
			acum++;
		}
	}

	//Todos los procesos envian al proceso 0 la cantidad de veces
	//que encontro a ese elemento
	MPI_Reduce(&acum, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0){
		printf("Numero de veces que aparecio el elemento 1: %d",res);
	}

	/* shut down MPI */
	MPI_Finalize();

	return 0;
}
