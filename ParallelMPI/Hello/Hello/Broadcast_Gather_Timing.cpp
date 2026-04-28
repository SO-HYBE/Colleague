#include <iostream>
#include <mpi.h>

using namespace std;

int main()
{
    MPI_Init(NULL, NULL);
    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    double start = MPI_Wtime();

    //send a message to all processes
    float* buffer = new float[8];
    for (int i = 0; i < 8; i++) {
        buffer[i] = i;
    }
    MPI_Bcast(buffer, 8, MPI_FLOAT, 0, MPI_COMM_WORLD);

    //receive a message from all processes
    float* gatheringBuffer = nullptr;
    if (rank == 0) {
        gatheringBuffer = new float[8 * world_size];
    }
    MPI_Gather(buffer, 8, MPI_FLOAT, gatheringBuffer, 8, MPI_FLOAT, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0) {
        cout << "Time taken = " << end - start << " seconds";
    }

    MPI_Finalize();
    return 0;
}