#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int max = 8;
	int v[] = {1,2,3,5,8,13,21,34};
	int u[] = {0,0,0,0,0,0,0,0};
	int w[] = {1,2,3,5,8,13,21,34};

	#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		int nthreads = omp_get_num_threads();
		int istart = id*max/nthreads;
		int iend = (id==nthreads-1)?((id+1)*max/nthreads):max;
		for ( int i= istart ; i<iend;++i){
			u[i] = v[i] + w[i];
		}
	}

	for(int i = 0; i < max; ++i){
		printf("%d. ", u[i]);
	}

	int v1[] = {1,2,3,5,8,13,21,34};
	int u1[] = {0,0,0,0,0,0,0,0};
	int w1[] = {1,2,3,5,8,13,21,34};

	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
		for(int i=0;i<max;++i){
			u1[i] = v1[i]+w1[i];
		}
	}

	printf("\n\n::::::::::::::::::::::::::\n\n");

	for(int i = 0; i < max; ++i){
		printf("%d. ", u1[i]);
	}


	return 0;
}


