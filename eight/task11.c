/*
Задание: Измените программу так, чтобы при успешном завершении всех передач сообщений процесс 0 
посылал остальным процессам сообщение “SENDS COMPLETED” и они, получив получив это сообщение, выводили его.

mpicc task11.c -o task11
mpirun -np 4 ./task11


*/

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int i, index[4], count, remaining, a;
    int buffer[400];
    MPI_Request request[4];
    MPI_Status status[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size > 4)
    {
        printf("Please run with 4 processes.\n");fflush(stdout);
        MPI_Finalize();
        return 1;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    a=0; 

    // while (a != 1) {
    {
        if (rank == 0)
        {
            for (i=0; i<size * 100; i++)
                buffer[i] = i/100;
            for (i=0; i<size-1; i++)
            {
                MPI_Isend(&buffer[i*100], 100, MPI_INT, i+1, 123, MPI_COMM_WORLD, &request[i]);
            }
            remaining = size-1;
            while (remaining > 0)
            {
                MPI_Waitsome(size-1, request, &count, index, status);
                if (count > 0)
                {
                    printf("%d sends completed\n", count);
                    fflush(stdout);
                    remaining = remaining - count;
                }
                if (count == size-1) {
                    for (i=0; i<size-1; i++) {
                        buffer[0] = -1;
                        MPI_Isend(&buffer[0], 1, MPI_INT, i+1, 123, MPI_COMM_WORLD, &request[i]);                 
                    }
                }
            }
        }
        else
        {
            MPI_Recv(buffer, 100, MPI_INT, 0, 123, MPI_COMM_WORLD, &status[0]);

            printf("%d: buffer[0] = %d\n", rank, buffer[0]);
            fflush(stdout);

            MPI_Recv(buffer, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status[0]);
            if (buffer[0] == -1) {
                printf("%d: SENDS COMPLITED\n", rank, buffer[0]);
                fflush(stdout);
    
            }
            
        }
    }

    MPI_Finalize();
    return 0;
}

