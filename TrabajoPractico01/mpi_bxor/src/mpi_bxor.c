/*
 ============================================================================
 Name        : mpi_bxor.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Operacion de 3 procesos, donde cada uno de ellos tiene 1 bit

 mpicc -g -Wall -o mpi_bxor mpi_bxor.c
mpirun -n 3 ./mpi_bxor

 ============================================================================
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {
	int ID;
	int resBXOR = 0;
	int nroBit;

	/* Let the system do what it needs to start up MPI */
	MPI_Init(NULL, NULL);

	/* Get my process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);

	//each

	if (ID == 0) {
		printf("\nAntes de aplicar reduced");
		printf("\nBXOR es: %d", resBXOR);

	}

	switch (ID) {
	case 0:
		nroBit = 1;
		break;
	case 1:
		nroBit = 0;
		break;
	case 2:
		nroBit = 0;
		break;
	default:
		break;
	}

	MPI_Reduce(&nroBit, &resBXOR, 1, MPI_INT, MPI_BXOR, 0, MPI_COMM_WORLD);

	if (ID == 0) {

		printf("\nLuego de aplicar reduced BXOR %d", resBXOR);

	}
	/* Shut down MPI */
	MPI_Finalize();

	return 0;
} /*  main  */

