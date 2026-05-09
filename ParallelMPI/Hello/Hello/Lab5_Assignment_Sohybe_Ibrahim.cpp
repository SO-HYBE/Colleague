#include <iostream>
#include <mpi.h>
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // ========================================================================
    // PROGRAM 1: Sin(2*pi*x) Evaluation and Even/Odd Comm Split
    // ========================================================================
    {
        if (rank == 0) {
            cout << "\n======================================================\n";
            cout << " RUNNING PROGRAM 1: Sin(x) Evaluation (Comm Split)\n";
            cout << "======================================================\n";
        }

        const int POINTS = 30;
        const double PI = 3.14159265358979323846;

        double sub_length = 2.0 / world_size;
        double start_x = -1.0 + (rank * sub_length);
        double dx = sub_length / POINTS;

        double local_x[POINTS];
        double local_y[POINTS];

        for (int i = 0; i < POINTS; i++) {
            local_x[i] = start_x + (i + 0.5) * dx;
            local_y[i] = sin(2.0 * PI * local_x[i]);
        }

        MPI_Comm group_comm;
        int color = rank % 2;
        MPI_Comm_split(MPI_COMM_WORLD, color, rank, &group_comm);

        int group_rank, group_size;
        MPI_Comm_rank(group_comm, &group_rank);
        MPI_Comm_size(group_comm, &group_size);

        vector<double> group_x;
        vector<double> group_y;

        if (group_rank == 0) {
            group_x.resize(POINTS * group_size);
            group_y.resize(POINTS * group_size);
        }

        MPI_Gather(local_x, POINTS, MPI_DOUBLE, group_x.data(), POINTS, MPI_DOUBLE, 0, group_comm);
        MPI_Gather(local_y, POINTS, MPI_DOUBLE, group_y.data(), POINTS, MPI_DOUBLE, 0, group_comm);

        if (group_rank == 0) {
            string group_name = (color == 0) ? "EVEN GROUP" : "ODD GROUP";

            cout << "\n=== " << group_name << " RESULTS ===" << endl;
            cout << "Total Processors in this group: " << group_size << endl;

            for (int i = 0; i < group_size * POINTS; i++) {
                cout << "x = " << group_x[i] << " \t| f(x) = " << group_y[i] << endl;
            }
        }

        MPI_Comm_free(&group_comm);
    }

    // Wait for all processors to finish Program 1
    MPI_Barrier(MPI_COMM_WORLD);

    // ========================================================================
    // PROGRAM 2: Group Creation via MPI_Group_incl (Requires exactly 6 procs)
    // ========================================================================
    {
        if (rank == 0) {
            cout << "\n======================================================\n";
            cout << " RUNNING PROGRAM 2: Group_incl (Needs 6 Processors)\n";
            cout << "======================================================\n";
        }

        if (world_size != 6) {
            if (rank == 0) {
                cout << "-> SKIPPING PROGRAM 2: This program requires exactly 6 processors. You are using " << world_size << ".\n";
            }
        }
        else {
            MPI_Group originalGroup;
            MPI_Comm_group(MPI_COMM_WORLD, &originalGroup);

            int evenRanks[] = { 0,2,4 }, oddRanks[] = { 1,3,5 };
            MPI_Group evenGroup, oddGroup;
            MPI_Group_incl(originalGroup, 3, evenRanks, &evenGroup);
            MPI_Group_incl(originalGroup, 3, oddRanks, &oddGroup);

            MPI_Comm evenComm, oddComm;
            MPI_Comm_create(MPI_COMM_WORLD, evenGroup, &evenComm);
            MPI_Comm_create(MPI_COMM_WORLD, oddGroup, &oddComm);

            int groupRank, sum, oddSum;
            if (rank % 2 == 0)
            {
                MPI_Group_rank(evenGroup, &groupRank);
                MPI_Reduce(&groupRank, &sum, 1, MPI_INT, MPI_SUM, 0, evenComm);
            }
            else
            {
                MPI_Group_rank(oddGroup, &groupRank);
                MPI_Reduce(&groupRank, &sum, 1, MPI_INT, MPI_SUM, 0, oddComm);

                if (groupRank == 0) {
                    MPI_Send(&sum, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
                }
            }

            if (groupRank == 0)
                printf("Process %d, sum= %d\n", rank, sum);

            if (rank == 0) {
                MPI_Recv(&oddSum, 1, MPI_INT, 1, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Sum of even processes= %d \nSum of odd processes %d\n", sum, oddSum);
            }

            MPI_Group_free(&evenGroup);
            MPI_Group_free(&oddGroup);
            MPI_Group_free(&originalGroup);
            if (evenComm != MPI_COMM_NULL) MPI_Comm_free(&evenComm);
            if (oddComm != MPI_COMM_NULL) MPI_Comm_free(&oddComm);
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