#include <stdio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <mpi.h>

void helper(void *invec, void *inoutvec, int *len, MPI_Datatype *datatype){
    const long int *in = (const long int *)invec;
    double *out = (double *) inoutvec;

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(time(NULL)+rank);

    for(int i=0; i<*in; i++){
        if (i >=* len) break;
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            *out++;
        }
    }
}

double pi_calc(long int n) {
    long int count_inside_circle = 0;
    // Generate n random points
    MPI_Op count;
    MPI_Op_create(helper, 1, &count);

    MPI_Reduce(&n, &count_inside_circle, 1, MPI_LONG, count, 0, MPI_COMM_WORLD);

    // Calculate pi approximation: (points inside circle / total points) * 4
    double pi_estimate = 4.0 * count_inside_circle / n;
    // std::cout << count_inside_circle<<std::endl;
    ////////////////////////////////////////
    return pi_estimate;
}




