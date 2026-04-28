#include <iostream>
#include <mpi.h>

using namespace std;

int main()
{
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    double start, end;
    int token = rank;
    int source = rank - 1;
    int dest = (rank + 1) % world_size;

    if (source < 0)
        source = world_size - 1;

    do {
        if (rank == 0 && token == 0)
            start = MPI_Wtime();
        if (rank == 1 && token == 0)
            end = MPI_Wtime();

        MPI_Send(&token, 1, MPI_INT, dest, 50, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, source, 50, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } while (token != rank);

    if (rank == 1)
        MPI_Send(&end, 1, MPI_DOUBLE, 0, 50, MPI_COMM_WORLD);
    else if (rank == 0) {
        MPI_Recv(&end, 1, MPI_DOUBLE, 1, 50, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Start= " << start << "\nEnd= " << end << "\nTime elapsed = " << end - start;
    }

    MPI_Finalize();
    return 0;
}