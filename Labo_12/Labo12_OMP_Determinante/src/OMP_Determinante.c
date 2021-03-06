/*
 ============================================================================
 Name        : DeterminanteSecuencial.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que halla la determinante de una matriz 3x3
 usando la regla de Sarrus

 Donde cada hilo realizara la mitad de operaciones de la regla de sarrus.

 Compilar: gcc -g -Wall -fopenmp -o det OMP_Determinante.c
 Ejecutar: ./det
 ============================================================================
 */

#include <omp.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"

double sum_p1 = 0;
double sum_p2 = 0;

void generarMatriz(double **m, int n) {

	for (int i = 0; i < n; i++)
		m[i] = (double*) malloc(sizeof(double) * n);

	printf("MATRIZ GENERADA\n");

	srand(time(NULL));
	for (int y = 0; y < n; y++) {

		for (int w = 0; w < n; w++) {

			m[y][w] = rand() % 100;
			printf("%.0lf ", m[y][w]);
		}
		printf("\n");
	}

}

void modifMatriz(double **m, int n, double **matriz) {

	for (int i = 0; i < n; i++)
		matriz[i] = (double*) malloc(sizeof(double) * (2 * n - 1));
	//double matriz[n][n + (n - 1)];

	printf("\n");

	for (int y = 0; y < n; y++) {

		for (int w = 0; w < n; w++) {

			matriz[y][w] = m[y][w];
		}
	}

	//copiar resto de matriz
	for (int y = 0; y < n; y++) {

		for (int w = n; w < n + (n - 1); w++) {

			matriz[y][w] = m[y][w - n];
		}
	}

	//Matriz modificada
	printf("MATRIZ MODIFICADA PARA HALLAR EL DETERMINANTE\n");

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n + (n - 1); j++) {
			printf("%.0lf ", matriz[i][j]);
		}
		printf("\n");

	}
}

void detMatriz(double **matriz, int n, int hilo) {

	double p1, p2;

	int aux_i, aux_j;

	for (int jj = 0; jj < 2 * n - 1; jj++) {

		if (hilo == 0) {
			if (jj < n) {

				aux_i = 0, aux_j = jj;
				p1 = 1;

				while (aux_i < n) {
					p1 = p1 * matriz[aux_i][aux_j];

					aux_i++;
					aux_j++;
				}
				sum_p1 = sum_p1 + p1;
			}
		} else {
			if (jj >= n - 1) {

				aux_i = 0, aux_j = jj;
				p2 = 1;

				while (aux_i < n) {

					p2 = p2 * matriz[aux_i][aux_j];

					aux_i++;
					aux_j--;
				}
				sum_p2 = sum_p2 + p2;
			}
		}

	}
}
	int main() {

		int n = 3;
		double **m = (double**) malloc(sizeof(double) * n);
		double **matriz = (double**) malloc(sizeof(double) * n);

		int tid, nt = 2;
		double start, finish, elapsed;

		generarMatriz(m, n);
		modifMatriz(m, n, matriz);

		GET_TIME(start);

#pragma omp parallel num_threads(nt)
		{
			tid = omp_get_thread_num();
			detMatriz(matriz, n, tid);

		}

		printf("\nDeterminante (diferencia resultante de hilos): %.0lf\n",
				sum_p1 - sum_p2);

		GET_TIME(finish);

		elapsed = finish - start;
		printf("\nTiempo calculado : %.10lf", elapsed);

		return 0;

	}

