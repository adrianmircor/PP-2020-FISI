/*
 ============================================================================
 Name        : FirstOpenMP.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que calcula el promedio segun la cantidad de numeros
 generados aleatoriamente.

La distribucion de los elementos se hara en forma ciclica acorde al numero de hilos,
estos hilos debe ser menor o igual a la cantidad de numeros generados.

Para compilar: gcc -g -Wall -fopenmp -o prom OMP_Promedio.c
Para ejecutar: ./prom
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

	printf("\nCuantos numeros desea generar?\n");
	int num;

	scanf("%d",&num);
	double A[num];

	srand(time(NULL));
	for (int var = 0; var < num; var++) {
				A[var] = rand() % 10;
				printf("Valor %d : %.2f\n", var+1, A[var]);
		}

	printf("\nIngresar la cantidad de hilos a usar (menor a cantidad de # generados)\n");
	int nt;
	scanf("%d",&nt);
	omp_set_num_threads(nt);

	int longitud = sizeof(A) / sizeof(A[0]);
	double sum = 0;
	int i = 0;

	/* This constructor for parallel threads  */
	#pragma omp parallel num_threads(nt)
	{

		int id = omp_get_thread_num();
		printf("Hilo %d \n", id);
		i = id;

		do {
				sum = A[i] + sum;
				i = i + nt;

			} while (i < longitud);
	}

	sum = sum / longitud;

	printf("\nProm es: %.2f\n", sum);


	return 0;
}


