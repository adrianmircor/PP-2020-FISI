/*
 ============================================================================
 Name        : Ej7.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que halla el factorial de cualquier numero (n)
Considerar por ello que el numero de factorial >= al numero de procesos
Ya que si es mayor el numero de procesos que n, seria baja la
eficiencia, porque se usaria mas recursos.

Se distribuye de forma ciclica los valores hasta donde se hallara el factorial,
supongamos que deseamos hallar el factorial de 7 y el numero de procesos es 4,
entonces la distribucion de los numeros seria asi:
P0 => 1 5
P1 => 2 6
P2 => 3 7
P3 => 4
Se calcula el producto de los valores de cada proceso, para que luego se envien
esos resultados parciales al proceso 0. Finalmente el proceso 0 los recibe y halla
el producto final.

Nota: n en el codigo puede variar pero siempre debe ser mayor o igual a p.

mpiruncc -g -Wall -o Ej7 Ej7.c
mpirun -n <numero de procesos p> Ej7


 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int rank; /* rank of process */
	int p; /* number of processes */
	int n = 18; //Se desea hallar el factorial de 18 (puede variar)
	double resultadoN = 1;
	MPI_Status estado;

	/* start up MPI */

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm_size(MPI_COMM_WORLD, &p);

	int data = rank + 1;
	double res = 1;

	if (n >= p) {

		//Distribucion a los procesos en forma ciclica de los valores de n!: 1 2 3 ... (n-1) n
		do {
			res = res * data;
			data = data + p;

		} while (data <= n);

		//Envio de producto parcial por parte del proceso rank
		MPI_Send(&res,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}

	if (rank == 0) {

		//Recepcion de los productos parciales de los demas procesos
		for(int i =0 ; i< p ; i++){

			MPI_Recv(&res,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&estado);
			resultadoN = resultadoN * res;
		}
		printf("\n\nEl resultado de %d! es: %.0f ",n, resultadoN);
	}

	/* shut down MPI */
	MPI_Finalize();

	return 0;
}
