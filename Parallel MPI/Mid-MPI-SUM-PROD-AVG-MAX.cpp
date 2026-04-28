#include <mpi.h>
#include <iostream>
using namespace std;

int main()
{
    int world_size, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // START OF PROBLEM SOLVING
    int global_datasize = 50;   // TOTAL NUMBER OF ELEMENTS
    int ROOT = 0;          // WHICH PROCESSOR WILL PRINT THE RESULT
    MPI_Op OPERATION = MPI_SUM;      // WHAT OPERATION TO PERFORM (MPI_SUM, MPI_PROD, MPI_MAX, etc.)
    int local_datasize = global_datasize / world_size;
    int *numbers = new int[local_datasize];
    
    // START OF local_result calculation //
    // SUM //
    int local_result = 0;
    for (int i = 0; i < local_datasize; i++) {
        local_result += numbers[i];
    }

    // PRODUCT //
    int local_result = 1;
    for (int i = 0; i < local_datasize; i++) {
        local_result *= numbers[i];
    }

    // MAX //
    int local_result = numbers[0];
    for (int i = 1; i < local_datasize; i++) {
        if (numbers[i] > local_result)
            local_result = numbers[i];
    }
    // END OF local_result calculation //
    
    int global_result;
    MPI_Reduce(&local_result, &global_result, 1, MPI_INT, OPERATION, ROOT, MPI_COMM_WORLD);
    if (rank == ROOT)
    {
        cout << global_result << endl;
        // AVG with SUM
        double avg = global_result / global_datasize;
        cout << avg << endl;
    }
    // END OF PROBLEM SOLVING

    MPI_Finalize();
    return 0;
}