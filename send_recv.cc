#include <mpi.h>
#include <cstdio>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    printf("rank: %d\n", world_rank);

    if (world_rank == 0) {
        string s = "Hello from rank 0";
        MPI_Send(s.c_str(), s.length() + 1, MPI_BYTE, 1, 233, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        char greeting[100];
        MPI_Recv(greeting, 100, MPI_BYTE, 0, 233, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%s\n", greeting);
    }

    MPI_Finalize();
    return 0;
}