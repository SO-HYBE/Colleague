#include <mpi.h>
#include <iostream>
using namespace std;
int main() {
    int world_size,rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
// RING
'''
int token = rank;
int sum = 0;
do {
    MPI_Send(&token, 1, MPI_INT, (rank + 1) % world_size, 0, MPI_COMM_WORLD);
    if (rank != 0) {
        MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    sum += token;
    cout << "Process " << rank << " received token " << token << endl;

} while (token != rank);
cout << "Process " << rank << " finished execution with sum " << sum << endl;
'''
// PRODUCT
''' 
int global_datasize = 50;
int local_datasize = global_datasize / world_size;
int *numbers = new int[local_datasize];

int local_product = 1;
for (int i = 0; i < local_datasize; i++){
    local_product *= numbers[i];
}

int result;
MPI_Reduce(&local_product, &result, 1, MPI_INT, MPI_PROD, 1, MPI_COMM_WORLD);
if (myRank == 1) {cout << "The result is " << result << endl;}

'''
// AVERAGE &  SUM
'''
int global_datasize = 50;
int local_datasize = global_datasize / world_size;
int *numbers = new int[local_datasize];


int local_sum = 0;
for (int i = 0; i < local_datasize; i++){
    local_sum += numbers[i];
}


int global_sum;
MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 5, MPI_COMM_WORLD);

if (myRank == 5) { 
    double result = global_sum / global_datasize; 
    cout << "Global sum = " << global_sum;
    cout << "Avg = " << result; 
}
'''
// MAX
'''
int global_datasize = 50;
int local_datasize = global_datasize / world_size;
int *numbers = new int[local_datasize];

int local_max = numbers[0];
for (int i = 1; i < local_datasize; i++) {
    if (numbers[i] > local_max)
        local_max = numbers[i];
}

int global_max;
MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 3, MPI_COMM_WORLD);
if (rank == 3){cout << "The max is " << global_max;}
'''
//===================================integration ====================================================
'''

double f(double x){
    return (sin(x) / x);
}

double MidpointRule (int levels, double xleft, double xright, double(*f) (double)) {
    double rectanglesNo = pow(double (2), levels);
    double base = (xright - xleft) / rectanglesNo;
    double result = 0.0;
    for (int i = 0; i < rectanglesNo; i++){
        result += f(xleft + (i + 0.5) * base);
    }
    result *= base;
    
    return result;
}

double Global_a = -100;
double Global_b = 100;
int levels = 10;

double Local_a = Global_a + rank * (Global_b - Global_a) / world_size;
double Local_b = Global_a + (rank + 1) * (Global_b - Global_a) / world_size;
double Local_result = MidpointRule (levels, Local_a, Local_b, f);

double Answer;
MPI_Reduce(&Local_result, &Answer, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
if (rank == 0){cout << "The result is "<< Answer << endl;}

'''


//======================== cos and sin ====================================

'''
double f(double x) {
    return sin(2 * 22 / 7 *x);
}


double global_start = -1, global_end = 1;
double width = (global_end - global_start) / world_size;
int local_start = global_start + (rank * width);
int local_end = global_start + ((rank + 1) * width);


double local_sum = 0, point;
double step = (local_end - local_start) / 30;
for (int i = 0; i < 30; i++) {
    point = local_start + (i * step);
    local_sum += f(point);
}

double global_sum = NULL;
MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
if (rank == 0) { cout << "The result is" << global_sum;}
'''
MPI_Finalize();
return 0;
}



