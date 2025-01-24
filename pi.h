#include <stdio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <mpi.h>

void helper(void *invec, void *inoutvec, int *len, MPI_Datatype *datatype){
    const long int *in = (const long int *)invec;
    long int *out = (long int *) inoutvec;

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(time(NULL)+rank);
    long int c = 0;
    for(int i=0; i<*in; i++){
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            c++;
        }
    }
    *out += c;
}

double pi_calc(long int n) {
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    long int points_per_process = n / size;
    long int count_inside_circle = 0;
    // Generate n random points
    MPI_Op count;
    MPI_Op_create(helper, 1, &count);

    MPI_Reduce(&points_per_process, &count_inside_circle, 1, MPI_LONG, count, 0, MPI_COMM_WORLD);

    MPI_Op_free(&count);

    // Calculate pi approximation: (points inside circle / total points) * 4
    double pi_estimate = 4.0 * count_inside_circle / n;
    ////////////////////////////////////////
    return pi_estimate;
}




