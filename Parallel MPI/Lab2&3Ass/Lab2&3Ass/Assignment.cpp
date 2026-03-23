#include <iostream>
#include <mpi.h>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int POINTS_PER_PROC = 50;

    double total_length = 2.0;
    double sub_length = total_length / size;

    double start_x = -1.0 + (rank * sub_length);
    double end_x = start_x + sub_length;

    vector<double> local_x(POINTS_PER_PROC);
    vector<double> local_y(POINTS_PER_PROC);

    double dx = sub_length / POINTS_PER_PROC;

    for (int i = 0; i < POINTS_PER_PROC; ++i) {
        local_x[i] = start_x + (i + 0.5) * dx;
        local_y[i] = cos(2.0 * M_PI * local_x[i]);
    }

    vector<double> global_x;
    vector<double> global_y;

    if (rank == 0) {
        global_x.resize(POINTS_PER_PROC * size);
        global_y.resize(POINTS_PER_PROC * size);
    }

    MPI_Gather(local_x.data(), POINTS_PER_PROC, MPI_DOUBLE,
        global_x.data(), POINTS_PER_PROC, MPI_DOUBLE,
        0, MPI_COMM_WORLD);

    MPI_Gather(local_y.data(), POINTS_PER_PROC, MPI_DOUBLE,
        global_y.data(), POINTS_PER_PROC, MPI_DOUBLE,
        0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Evaluating f(x) = cos(2 * pi * x) over [-1, 1]" << endl;
        cout << "Total Processors: " << size << endl;
        cout << "Total Points Evaluated: " << POINTS_PER_PROC * size << "\n" << endl;

        cout << left << setw(10) << "Rank"
            << setw(15) << "x value"
            << "f(x) value" << endl;
        cout << "------------------------------------------" << endl;

        for (int i = 0; i < size * POINTS_PER_PROC; ++i) {
            int source_rank = i / POINTS_PER_PROC;
            cout << left << setw(10) << source_rank
                << setw(15) << global_x[i]
                << global_y[i] << endl;
        }
    }

    MPI_Finalize();
    return 0;
}