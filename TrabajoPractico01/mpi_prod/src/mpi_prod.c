/*
 ============================================================================
 Name        : mpi_prod.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que realiza la multiplicacion de todos los valores
 	 	 	 	 que estan dentro de cada proceso.

  mpicc -g -Wall -o mpi_prod mpi_prod.c
mpirun -n <nro Procesos> ./mpi_prod
 ============================================================================
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {

	int ID;
	int Data = 0;
	int prodData = 0;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &ID);

   //each
   Data = (ID + 1);

   if(ID == 0){
   	   printf("\nAntes de aplicar reduced");
   	   printf("\nEl producto es: %d", prodData);

      }

   MPI_Reduce(&Data, &prodData, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

   if(ID == 0){
	   printf("\nLuego de aplicar reduced");
	   printf("\nEl producto de todos los procesos es: %d\n", prodData);

   }
   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */
