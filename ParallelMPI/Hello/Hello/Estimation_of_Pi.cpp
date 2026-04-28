#include <iostream>
#include <mpi.h>
#include <cstdlib>

using namespace std;

int main()
{
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int local_circlePoints = 0, local_totalPoints = 50;
    double x, y;
    for (int i = 0; i < local_totalPoints; i++)
    {
        x = (rand() % 100) / 100.0;
        y = (rand() % 100) / 100.0;
        if (x * x + y * y <= 1)
            local_circlePoints++;
    }

    int global_circlePoints;
    MPI_Reduce(&local_circlePoints, &global_circlePoints, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int global_totalPoints = local_totalPoints * world_size;
        double pi = 4.0 * global_circlePoints / global_totalPoints;
        cout << "Pi estimation = " << pi;
    }

    MPI_Finalize();
    return 0;
}