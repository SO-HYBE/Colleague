#include <iostream>
#include <mpi.h>
#include <cstdlib>

using namespace std;

int main()
{
    MPI_Init(NULL, NULL);
    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // ========================================================================
    // PROGRAM 1: Broadcast and Gather Timing
    // ========================================================================
    {
        if (rank == 0) {
            cout << "\n======================================================\n";
            cout << " RUNNING PROGRAM 1: Broadcast and Gather Timing\n";
            cout << "======================================================\n";
        }

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
            cout << "Time taken = " << end - start << " seconds\n";
        }

        // Clean up memory
        delete[] buffer;
        if (gatheringBuffer) delete[] gatheringBuffer;
    }

    // Force all processors to wait here until everyone is done with Program 1
    MPI_Barrier(MPI_COMM_WORLD);

    // ========================================================================
    // PROGRAM 2: Estimation of Pi
    // ========================================================================
    {
        if (rank == 0) {
            cout << "\n======================================================\n";
            cout << " RUNNING PROGRAM 2: Estimation of Pi\n";
            cout << "======================================================\n";
        }

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
            cout << "Pi estimation = " << pi << "\n";
        }
    }

    // Force all processors to wait here until everyone is done with Program 2
    MPI_Barrier(MPI_COMM_WORLD);

    // ========================================================================
    // PROGRAM 3: Ring Message Timing
    // ========================================================================
    {
        if (rank == 0) {
            cout << "\n======================================================\n";
            cout << " RUNNING PROGRAM 3: Ring Message Timing\n";
            cout << "======================================================\n";
        }

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
            cout << "Start= " << start << "\nEnd= " << end << "\nTime elapsed = " << end - start << "\n";
        }
    }

    if (rank == 0) {
        cout << "\n======================================================\n";
        cout << " ALL PROGRAMS COMPLETED.\n";
        cout << "======================================================\n";
    }

    MPI_Finalize();
    return 0;
}