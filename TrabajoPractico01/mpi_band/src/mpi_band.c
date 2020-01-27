/*
 ============================================================================
 Name        : mpi_band.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que realiza la operacion AND de 3 numeros binarios
 	 	 	 	 En cada proceso esta un numero binario.

mpicc -g -Wall -o mpi_band mpi_band.c
mpirun -n 3 ./mpi_band

 ============================================================================
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

int main(void) {
	int ID;
	int resBAND = 0;
	int nroBit;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &ID);

   if(ID == 0){
   	   printf("\nAntes de aplicar reduced");
   	   printf("\nEl maximo es: %d", resBAND);

      }

   switch (ID) {
   	case 0:
   		nroBit=101;
   		break;
   	case 1:
   		nroBit=001;
   		break;
   	case 2:
   		nroBit=101;
   		break;
   	default:
   		break;
   	}

   MPI_Reduce(&nroBit, &resBAND, 1, MPI_INT, MPI_BAND, 0, MPI_COMM_WORLD);

   if(ID == 0){


	   if(resBAND == 1){
		   printf("\nAND en binario es: 00%d", resBAND);
	   }else if(resBAND == 10){
		   printf("\nAND en binario es: 0%d", resBAND);
	   }else if(resBAND == 0){
		   printf("\nAND en binario es: 00%d", resBAND);
	   }else{
		   printf("\nLuego de aplicar reduced %d", resBAND);
	   }

   }
   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */

