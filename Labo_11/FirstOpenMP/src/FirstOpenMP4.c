/*
 ============================================================================
 Name        : FirstOpenMP.c
 Author      : Herminio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 Indicate number of Threads 'n' in Code:
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

	printf("\n 01 Fuera de la region Paralela ...\n"
			"Ingresar la cantidad de hilos a usar\n");
	int n;

	scanf("%d",&n);

	omp_set_num_threads(n);

	/* This constructor for parallel threads  */
	#pragma omp parallel num_threads(n/2)
	{
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		printf("HW from thread number %d de un total %d \n", id,	nt);
	}

	printf("\n 02 Fuera de la region Paralela ...\n\n");

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		printf("HW from thread number %d de un total %d \n", id,	nt);
	}
	return 0;
}


