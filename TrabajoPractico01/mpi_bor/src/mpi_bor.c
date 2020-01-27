/*
 ============================================================================
 Name        : mpi_bor.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Calculo de OR de bits

mpicc -g -Wall -o mpi_bor mpi_bor.c
mpirun -n 3 ./mpi_bor
 ============================================================================
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {
	int ID;
	int resBOR = 0;
	int nroBit;

	/* Let the system do what it needs to start up MPI */
	MPI_Init(NULL, NULL);

	/* Get my process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);

	//each

	if (ID == 0) {
		printf("\nAntes de aplicar reduced %d", resBOR);

	}

	switch (ID) {
	case 0:
		nroBit = 0;
		break;
	case 1:
		nroBit = 1;
		break;
	case 2:
		nroBit = 0;
		break;
	default:
		break;
	}

	MPI_Reduce(&nroBit, &resBOR, 1, MPI_INT, MPI_BOR, 0, MPI_COMM_WORLD);

	if (ID == 0) {
		printf("\nLuego de aplicar reduced BOR %d", resBOR);

	}
	/* Shut down MPI */
	MPI_Finalize();

	return 0;

}
