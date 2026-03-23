#include <iostream>
#include <mpi.h>
using namespace std;
int main()
{
    MPI_Init(NULL, NULL);
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    cout << "Hello world from process " << rank << " out of " << worldSize;
    MPI_Finalize();
    return 0;
}