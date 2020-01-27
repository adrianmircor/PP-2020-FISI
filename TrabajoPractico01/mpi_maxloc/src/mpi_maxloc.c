/*
 ============================================================================
 Name        : mpi_maxloc.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Cada proceso esta representado por struct, donde se tiene un valor
 	 	 	 y el rank, se realiza la comparacion de cada proceso para saber cuál
			 de ellos tiene el valor maximo y que numero es.

 mpicc -g -Wall -o mpi_maxloc mpi_maxloc.c
mpirun -n <nro Procesos> ./mpi_maxloc

 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int rank;

	struct {
		double valor;
		int rank;
	} in, out;

	int root;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	in.valor = rank + 1; 	//1
	in.rank = rank; 		//0

	root = 0; //nodo hacia cual se va a enviar, para comparar.

	MPI_Reduce(&in, &out, 1, MPI_DOUBLE_INT, MPI_MAXLOC, root, MPI_COMM_WORLD);

	if (rank == root) {
		printf("Numero max =%.2f en el rank %d\n", out.valor, out.rank);
	}

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
}
