/*
 ============================================================================
 Name        : mpi_lor.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : El siguiente codigo se encarga de encontrar al menos a una aerolinea
 que haga el recorrido que desea el usuario (destinoBUscar)
 Cada proceso realizara una busqueda, que se podria extender a una busqueda mucho mas
 compleja en una base de datos distinta o tablas distintas.

 mpicc -g -Wall -o mpi_lor mpi_lor.c
 mpirun -n 3 ./mpi_lor


 ============================================================================
 */
#include <stdio.h>
#include <time.h>
#include <string.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

char *buscar(char *str1,char *str2);

int main(void) {

	char *aerolinea1 = "LAN: Lima-Huancayo, Lima-Tacna, Lima-Chimbote";
	char *aerolinea2 = "AEROPERU: Lima-Ica, Lima-Ilo, Lima-Tacna";
	char *aerolinea3 = "LATAM: Lima-Jauja, Lima-Piura, Lima-Chimbote";

	char *destinoBuscar = "Lima-Tacna";
	char *busquedaEncontrada;

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

		busquedaEncontrada = buscar(aerolinea1,destinoBuscar);

		if (busquedaEncontrada != NULL) {
			Data = 1;
		}else{
			Data = 0;
		}
		break;
	case 1:

		busquedaEncontrada = buscar(aerolinea2,destinoBuscar);

				if (busquedaEncontrada != NULL) {
					Data = 1;
				}else{
					Data = 0;
				}
		break;
	case 2:
		busquedaEncontrada = buscar(aerolinea3,destinoBuscar);

				if (busquedaEncontrada != NULL) {
					Data = 1;
				}else{
					Data = 0;
				}
		break;
	default:
		break;
	}

	MPI_Reduce(&Data, &landData, 1, MPI_INT, MPI_LOR, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("\nLuego de aplicar reduced");
		printf("\nEl resultado de LOR de todos los procesos es: %d\n",
				landData);

		if (landData == 0) {
			printf(
					"\nNO SE ENCONTRÓ NINGUNA AEROLINEA CON DISPONIBILIDAD DE %s", destinoBuscar);

		} else if (landData == 1) {
			printf(
					"\nSE ENCONTRÓ AL MENOS UNA AEROLINEA QUE TIENE DISPONIBLE EL VIAJE DE  %s", destinoBuscar);

		}

	}
	/* Shut down MPI */
	MPI_Finalize();

	return 0;
} /*  main  */

char *buscar(char *str1, char *str2) {
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i;
	char c;

	if (len2 > len1) {
		return NULL;
	} else {
		i = 0;
		c = str2[0];
		while (i < len1) {
			if (str1[i] == c) {
				if (strncmp(&str1[i], str2, len2) == 0) {
					return &str1[i];
				}
			}
			i++;
		}
		return NULL;
	}

}
