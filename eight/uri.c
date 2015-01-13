#include  <stdio.h>
#include   "mpi.h"
void main(int argc,char * argv[])
{
  const int BUFSIZE=MPI_BSEND_OVERHEAD+4; 
  unsigned char buf[BUFSIZE]; 
  int rank,ierr,ibufsize,rbuf;
  struct MPI_Status status; 
  ierr=MPI_Init(&argc,&argv);
  ierr=MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank%2 == 0) {
     if (rank != 0) {
        ierr=MPI_Buffer_attach(buf,BUFSIZE);
        ierr=MPI_Bsend(&rank,1,MPI_INT,rank+1,5,MPI_COMM_WORLD);
        // sending variable rank
        ierr=MPI_Buffer_detach(&buf, &BUFSIZE);  
     }
    
  } else { 
    if (rank != 1) { 
      ierr=MPI_Recv(&rbuf,1,MPI_INT,rank-1,5,MPI_COMM_WORLD,&status);
      printf("Process %i received %i from process %i\n",rank, rbuf, status.MPI_SOURCE); 
    }
  }
  ierr=MPI_Finalize();
}