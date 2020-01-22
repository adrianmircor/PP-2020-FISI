#include <stdio.h>
#include <string.h> /* For strlen 				*/
#include <mpi.h>	/* For MPI functions, etc 	*/

const int MAX_STRING = 100;
int main(void) {
	char greeting[MAX_STRING];
	int  comm_sz;  /* Numero de procesos 	*/
	int  my_rank;  /* Rank de mi proceso	*/

	MPI_Init(NULL, NULL);
	MPI_Comm_size(
			MPI_COMM_WORLD, //Comunicador
			&comm_sz		//Variable donde se guarda el numero de procesos
			);
	MPI_Comm_rank(
			MPI_COMM_WORLD, //Comunicador
			&my_rank		//Variable donde se guarda el rank del proceso actual
			);

	if(my_rank != 0){
	  sprintf(greeting, "i0 - Greetings from process %d of %d!", my_rank, comm_sz);
	  MPI_Send(
			  greeting, 			// Direccion del mensaje
			  strlen(greeting) + 1, // Tamaño del mensaje
			  MPI_CHAR,				// Tipo del mensaje
			  0,					// Destino
			  0, 					// Etiqueta
			  MPI_COMM_WORLD		// Comunicador
			 );
	}else {
	  printf("in - Greetings from process %d of %d!\n", my_rank, comm_sz);
	  for(int q = 1; q < comm_sz; q++){
		MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%s\n", greeting);
	  }
	}
	MPI_Finalize();
	return 0;
}
