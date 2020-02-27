#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int f(int x, int hilo){
	printf("\nIteracion: %d \n", x+1);
	printf("Hilo: %d \n", hilo);
	return hilo;
}

int g(int hilo){
	printf("\nBloque critico \n");
	printf("Hilo: %d \n", hilo);
	return 0;
}

int main (int argc, char *argv[]) {
	int hilos;
	printf("Ingresa numero de hilos: ");
	scanf("%d", &hilos);

	int max;
	printf("Ingresa max: ");
	scanf("%d", &max);

	#pragma omp parallel num_threads(hilos)
	{
		int hilo = omp_get_thread_num();
		for(int i = 0; i < max; i++){
			int x = f(i, hilo);
			#pragma omp critical
			{
				g(x);
			}
		}
	}
	return 0;
}


