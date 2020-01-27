/*
 ============================================================================
 Name        : mpi_sum.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que realiza la suma de todos los valores
 	 	 	 	 que estan dentro de cada proceso.


  mpicc -g -Wall -o mpi_sum mpi_sum.c
mpirun -n <nro Procesos> ./mpi_sum
 ============================================================================
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {
	int ID;
	int Data = 0;
	int ReducedData = 0;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &ID);

   //each
   Data = (ID + 1)*10;

   if(ID == 0){
   	   printf("Antes de aplicar reduced");
   	   printf("SUM es: %d", ReducedData);

      }

   MPI_Reduce(&Data, &ReducedData, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

   if(ID == 0){
	   printf("Luego de aplicar reduced");
	   printf("SUM es: %d", ReducedData);

   }
   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */

