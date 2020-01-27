/*
 ============================================================================
 Name        : mpi_min.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que halla el menor numero de todos los procesos

  mpicc -g -Wall -o mpi_min mpi_min.c
mpirun -n <nro Procesos> ./mpi_min
 ============================================================================
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {
	int ID;
	int Data = 0;
	int minData = 0;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &ID);

   //each
   Data = (ID + 1)*6;

   if(ID == 0){
   	   printf("\nAntes de aplicar reduced");
   	   printf("\nEl min es: %d", minData);

      }

   MPI_Reduce(&Data, &minData, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

   if(ID == 0){
	   printf("\nLuego de aplicar reduced");
	   printf("\nEl min numero de todos los procesos es: %d\n", minData);

   }
   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */
