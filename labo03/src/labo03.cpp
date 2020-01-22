#include <stdio.h>

#include <string.h>

#include <mpi.h>

/* For strlen */
/* For MPI functions, etc */
const int MAX STRING = 100;
int main(void) {
  char greeting[MAX STRING];
  int  comm_sz;  /* Number of processes */
  int  my_rank;  /* My process rank*/

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI COMM WORLD, & comm sz);
  MPI_Comm_rank(MPI COMM WORLD, & my rank);
  if (my rank != 0) {
    sprintf(greeting, "Greetings from process %d of %d!",
      my_rank, comm_sz);
    MPI_Send(greeting, strlen(greeting) + 1, MPI CHAR, 0, 0,
      MPI COMM WORLD);
  } else {
    printf("Greetings from process %d of %d!\n", my rank,
      comm sz);
    for (int q = 1; q < comm sz; q++) {
      MPI Recv(greeting, MAX STRING, MPI CHAR, q,
        0, MPI COMM WORLD, MPI STATUS IGNORE);
      printf("%s\n", greeting);
    }
  }
}
MPI Finalize();
return 0;
/∗ main ∗/
