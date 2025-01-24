#include <stdio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <mpi.h>


double pi_calc(long int n) {
    
    // Write your code below
    ////////////////////////////////////////
    
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(time(NULL) + rank);

    long int count_inside_circle = 0;

    // Generate n random points
    for (long int i = 0; i < n/size; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // Check if the point is inside the unit circle
        if (x * x + y * y <= 1.0) {
            count_inside_circle++;
        }
    }

    long int global_sum = 0;
    MPI_Reduce(&count_inside_circle, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // if (rank == 0) {
    //     printf("%ld\n", global_sum);
    // }
    // Calculate pi approximation: (points inside circle / total points) * 4
    double pi_estimate = 4.0 * (double)global_sum / (double)n;


    ////////////////////////////////////////
    return pi_estimate;
}
