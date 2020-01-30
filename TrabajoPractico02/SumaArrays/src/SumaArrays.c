/*
 ============================================================================
 Name        : SumaArrays.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que suma arreglos A y B, ambos vectores tienen tamaño 100

 La suma consistira en dividir los arreglos en bloques iguales, estos bloques iran a cada
 procesador y realizara la suma, finlamente se agregaran al Procesador0 para dar solucion final.

  mpicc -g -Wall -o SumaArrays SumaArrays.c
mpirun -n 10 ./SumaArrays
 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {

	srand(time(NULL));

	int my_rank; /* rank of process */
	int num_procs; /* number of processes */
	MPI_Status status; /* return status for receive */

	int A[100];
	int B[100];
	int C[100];
	int tamVector = sizeof(B) / sizeof(int);
	int D[100];

	/* start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* find out number of processes */

	if (my_rank == 0) {

		//Llenado de valores del arreglo A
		for (int var = 0; var < tamVector; var++) {
			A[var] = rand() % 10;
			printf("\nA i: %d valor: %d", var, A[var]);
		}
		printf("\n");

		//Llenado de valores del arreglo B
		for (int var = 0; var < tamVector; var++) {
			B[var] = rand() % 10;
			printf("\nB i: %d valor: %d", var, B[var]);
		}
		printf("\n");

		//Se envia a todos los procesos excepto al 0
		for (int var = 1; var < num_procs; ++var) {
			MPI_Send(&A, tamVector, MPI_INT, var, 0, MPI_COMM_WORLD);
			MPI_Send(&B, tamVector, MPI_INT, var, 0, MPI_COMM_WORLD);

			printf("\nEnviando los vectores A y B a los Procesos: %d", var);
		}

		//El proceso 0 realiza la suma con los primeros 10 elementos de ambos arreglos
		for (int var = 0; var < tamVector / num_procs; var++) {
			C[var] = A[var] + B[var];
		}


	} else {
		//Los demas procesos reciben el tamaño REAL de los vectores
		MPI_Recv(&A, tamVector, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&B, tamVector, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		int f = 10 * my_rank;

		/*El vector D guardara de acuerdo al indice de la suma de A y B,
		 Por proceso se esta guardando 10 sumas de los elementos de A y B*/

		for (int var = 10 * my_rank;	var < (10 * my_rank) + (tamVector / num_procs); var++) {
			D[f] = A[var] + B[var];
			f++;
			//printf("\nSOY EL PROCESO %d - D i: %d valor: %d", my_rank, var,	D[var]);
		}

		/*Se envia el Vector D con indices especificos, para luego en el proceso 0
		 *se junte todos los vectores*/
		MPI_Send(&D, tamVector, MPI_INT, 0, 0, MPI_COMM_WORLD);

	}

	if (my_rank == 0) {

		//Vector resultante de las sumas de A y B
		int sumaVector[tamVector];

		//Recibe el vector C (primeros elementos sumados)
		for (int var = 0; var < (tamVector / num_procs); var++) {
			//printf("\n\nVECTOR C del Proceso 0 i: %d - valor: %d", var, C[var]);
			sumaVector[var] = C[var];
		}

		//Recibe del proceso 1
		MPI_Recv(&D, tamVector, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		for (int var = 10; var < 10+(tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Recibe del proceso 2
		MPI_Recv(&D, tamVector, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
		for (int var = 20; var < 20 + (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];

		}

		//Recibe del proceso 3
		MPI_Recv(&D, tamVector, MPI_INT, 3, 0, MPI_COMM_WORLD, &status);
		for (int var = 30; var < 30 + (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Recibe del proceso 4
		MPI_Recv(&D, tamVector, MPI_INT, 4, 0, MPI_COMM_WORLD, &status);
		for (int var = 40; var < 40+ (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Recibe del proceso 5
		MPI_Recv(&D, tamVector, MPI_INT, 5, 0, MPI_COMM_WORLD, &status);
		for (int var = 50; var < 50 + (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Recibe del proceso 6
		MPI_Recv(&D, tamVector, MPI_INT, 6, 0, MPI_COMM_WORLD, &status);
		for (int var = 60; var < 60 + (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Recibe del proceso 7
		MPI_Recv(&D, tamVector, MPI_INT, 7, 0, MPI_COMM_WORLD, &status);
		for (int var = 70; var < 70 + (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Recibe del proceso 8
		MPI_Recv(&D, tamVector, MPI_INT, 8, 0, MPI_COMM_WORLD, &status);
		for (int var = 80; var < 80 + (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Recibe del proceso 9
		MPI_Recv(&D, tamVector, MPI_INT, 9, 0, MPI_COMM_WORLD, &status);
		for (int var = 90; var < 90 + (tamVector / num_procs); var++) {
			sumaVector[var] = D[var];
		}

		//Unifica los valores de las sumas de los procesos anteriores
		for (int var = 0; var < tamVector; var++) {
			printf("\n\n-->VECTOR FINAL i: %d - valor: %d", var, sumaVector[var]);
		}

		//hacer algoritmo q mientras reciba de un proceso, vaya guardando su arreglo en otro

	}

	/* shut down MPI */
	MPI_Finalize();

	return 0;
}

