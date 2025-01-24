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
    
    srand(time(NULL));

    long int count_inside_circle = 0;

    // Generate n random points
    for (long int i = 0; i < n; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // Check if the point is inside the unit circle
        if (x * x + y * y <= 1.0) {
            count_inside_circle++;
        }
    }

    // Calculate pi approximation: (points inside circle / total points) * 4
    double pi_estimate = 4.0 * count_inside_circle / n;

    ////////////////////////////////////////
    return pi_estimate;
}
