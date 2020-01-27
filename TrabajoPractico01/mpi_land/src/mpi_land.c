/*
 ============================================================================
 Name        : mpi_land.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Tomamos como ejm querer comparar en una base de datos, los datos
 de una empresa que tiene 3 atributos,para este caso cada atributo estara en un proceso,
 cada proceso se encargara de buscar en una bd o tabla distinta

mpicc -g -Wall -o mpi_land mpi_land.c
mpirun -n 3 ./mpi_land

 ============================================================================
 */
#include <stdio.h>
#include <time.h>
#include <string.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {

	char atributo1[]="10";
	char atributo2[] = "Mondo Agit, S.L.";
	char atributo3[] = "c/ San Lamberto, 11; Madrid";

	int rank;
	int Data = 0;
	int landData = 0;

	/* Let the system do what it needs to start up MPI */
	MPI_Init(NULL, NULL);

	/* Get my process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//each

	if (rank == 0) {
		printf("\nAntes de aplicar reduced");
		printf("\nEl resultado de lAND es: %d", landData);

	}

	//Comparar lo q hara c/proceso

	switch (rank) {
	case 0:

		if (strcmp(atributo1, "10") == 0) {
			Data = 1;
		}
		break;
	case 1:

		if (strcmp(atributo2, "Mondo Agit, S.L.") == 0) {
			Data = 1;
		}
		break;
	case 2:
		if (strcmp(atributo3, "c/ San Lamberto, 11; Madrid")== 0) {
			Data = 1;
		}
		break;
	default:
		break;
	}

	MPI_Reduce(&Data, &landData, 1, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("\nLuego de aplicar reduced");
		printf("\nEl resultado de lAND de todos los procesos es: %d\n", landData);

		if(landData==0){
			printf("\nNO SE ENCUENTRA LA EMPRESA CON LOS DATOS BRINDADOS");

		}else if(landData==1){
			printf("\nSE ENCONTRÓ EXITOSAMENTE LA EMPRESA CON LOS DATOS BRINDADOS");

		}


	}
	/* Shut down MPI */
	MPI_Finalize();

	return 0;
} /*  main  */
