/*
Задание: Измените данную программу так, чтобы нулевой процесс не посылал сообщений и запустите её с числом процессов, 
равным номеру вашего варианта.

*/

#include <stdio.h>
#include "mpi.h"
void main(int argc,char * argv[])
{
  int ierr,size,rank,a,b;
  struct MPI_Status status;
  ierr=MPI_Init(&argc,&argv);
  // Получить размер коммуникатора MPI_COMM_WORLD
  // (общее число процессов в рамках задачи)
  ierr=MPI_Comm_size(MPI_COMM_WORLD, &size);
  // Получить номер текущего процесса в рамках 
  // коммуникатора MPI_COMM_WORLD
  ierr=MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  a=rank;
  b=-1;

  if (rank%2 == 0) { 
    if (rank != 0 && rank+1<size)
      ierr=MPI_Send(&a, 1, MPI_INT, rank+1, 5, MPI_COMM_WORLD);
  } else {
    if (rank != 1) {
      ierr=MPI_Recv(&b,1,MPI_INT,rank-1,5,MPI_COMM_WORLD,&status);
    }
  } 
  printf ("Process %i a = %i b = %i\n",rank,a,b) ;
  
  ierr=MPI_Finalize ();  
  
} 