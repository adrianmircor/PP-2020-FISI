/*
 ============================================================================
 Name        : mpi_max.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que halla el numero maximo de todos los procesos

 mpicc -g -Wall -o mpi_max mpi_max.c
mpirun -n 3 ./mpi_max
 ============================================================================
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {
	int ID;
	int Data = 0;
	int maxData = 0;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &ID);

   //each
   Data = (ID + 1)*10;

   if(ID == 0){
   	   printf("\nAntes de aplicar reduced");
   	   printf("\nEl maximo es: %d", maxData);

      }

   MPI_Reduce(&Data, &maxData, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

   if(ID == 0){
	   printf("\nLuego de aplicar reduced");
	   printf("\nEl maximo numero de todos los procesos es: %d", maxData);

   }
   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */

