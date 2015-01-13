#include <stdio.h>
#include "mpi.h"
void main(int argc,char * argv[])
{
  int ierr,rank,size;
  int rankl, i;
  const int BUFSIZE=MPI_BSEND_OVERHEAD+4; 
  unsigned char buf[BUFSIZE]; 
  int ibufsize,rbuf;
  struct MPI_Status status; 
  MPI_Comm comm_revs;
  ierr=MPI_Init (&argc, &argv) ;
  ierr=MPI_Comm_size(MPI_COMM_WORLD,&size) ;
  ierr=MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  ierr=MPI_Comm_split(MPI_COMM_WORLD, 1, size-rank, &comm_revs) ;
  ierr=MPI_Comm_rank(comm_revs,&rankl);
  printf("Rank = %i, rankl = %i\n",rank,rankl);

  if (rank != 0)
  {
    ierr=MPI_Buffer_attach(buf,BUFSIZE);
    ierr=MPI_Bsend(&rankl,1,MPI_INT,0,5,MPI_COMM_WORLD);     
    ierr=MPI_Buffer_detach(&buf, &BUFSIZE);   
  }
  else
  {
      for (i = 1; i < size; i++) {
        ierr=MPI_Recv(&rbuf,1,MPI_INT,i,5,MPI_COMM_WORLD,&status);
        printf("Process %i has rankl: %i\n",i, rbuf, status.MPI_SOURCE); 
      }     
  }

  ierr=MPI_Finalize(); 
}