#include <mpi.h>
#include <cstdio>
#include <sstream>

using namespace std;

const int MAX_NUMBERS = 1000000 + 10;

int numbers_per_processor;
int numbers[MAX_NUMBERS];

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    if (argc != 2) {
        printf("Usage: %s numbers_per_processor", argv[0]);
        return -1;
    }
    istringstream argv_ss(argv[1]);
    argv_ss >> numbers_per_processor;

    int world_rank, world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // generate random numbers
    int local_sum = 0;
    for (int i = 0; i < numbers_per_processor; i++) {
        numbers[i] = rand() % 255;
        local_sum += numbers[i];
    }

    int global_sum;
    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    // printf("global_sum: %d\n", global_sum);

    double mean = double(global_sum) / (world_size * numbers_per_processor);
    double local_dev2 = 0, dev2;

    for (int i = 0; i < numbers_per_processor; i++) {
        local_dev2 += (numbers[i] - mean) * (numbers[i] - mean);
    }

    MPI_Reduce(&local_dev2, &dev2, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("%d numbers, mean is %lf, squared deviation is %lf\n", numbers_per_processor * world_size, mean, dev2);
    }

    MPI_Finalize();
    return 0;
}
