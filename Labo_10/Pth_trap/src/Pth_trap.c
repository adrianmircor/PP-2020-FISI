/*
 ============================================================================
 Name        : Pth_trap.c
 Author      : Adrian
 Version     :
 Copyright   : Your copyright notice
 Description : Programa que calcula el area debajo de una curva (f(x) = sqrt((x*x-x))

 Para compilar: gcc -g -Wall -o trap Pth_trap.c -lpthread -lm
 Para ejecutar: ./trap <nro de hilos>

 Se ingresa la cantidad de trapecios a utilizar para hallar el area debajo de la curva,
 Se ingresa el limine inferior que es a y el lim superior que es b

Nota: Tomar en cuenta que el lim inferior de a debe ser >= 1 ya que la grafica
de sqrt(x*x-x) no cubre paraa a<1

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

/* Global variable: */
int thread_count;
double total_int = 0;
int n ;
double  a , b ;

/* Thread function */
void *oper(void *rank);
double Trap(double   /* in */, double  /* in */, int   /* in */, double    /* in */	);
double f(double );


int main(int argc, char* argv[]) {

	long thread; /* Use long in case of a 64 − bit system */
	pthread_t* thread_handles;

	/* Get number of threads from command line */
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	printf("Cuantos trapecios desea usar para hallar el area debajo de la curva?: ");
	scanf("%d", &n);
	printf("Valor de a: ");
	scanf("%lf", &a);
	printf("Valor de b: ");
	scanf("%lf", &b);

	for (thread = 0; thread < thread_count; thread++){
		pthread_create(		&thread_handles[thread], //Arreglo de punteros de ID de los hilos
							NULL, //Null por defecto
							oper, //Funcion a correr por el hilo
							(void*) thread	); //Argumento de la Funcion que debe retornar un void
	}

	//Une a los threads
	for (thread = 0; thread < thread_count; thread++){
		pthread_join(	thread_handles[thread],
						NULL	);
	}

	 printf("Resultado: %f \n", total_int);


	free(thread_handles); //libera memoria de array de punteros de los hilos
	return 0;
}/* main */

void* oper(void *rank){
	int my_rank = (long)rank;

	int  local_n;
	   double h, local_a, local_b;
	   double local_int;

	   h = (b-a)/n;
	   local_n = n/thread_count;

	   local_a = a + my_rank*local_n*h;
	   local_b = local_a + local_n*h;
	   local_int = Trap(local_a, local_b, local_n, h);

	   total_int = total_int+ local_int;

	   return NULL;
}

double Trap(double left_endpt /* in */, double right_endpt /* in */, int trap_count /* in */, double base_len /* in */	) {

   double estimate, x;
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
}

double f(double x) {

	double xx = sqrt(x*x-x);
    return xx;
}
