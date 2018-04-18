CC=mpic++

run: mpi_reduce
	mpirun mpi_reduce 20

hello: hello.cc
	${CC} hello.cc -o hello

send_recv: send_recv.cc
	${CC} send_recv.cc -o send_recv

mpi_reduce: mpi_reduce.cc
	${CC} -o mpi_reduce mpi_reduce.cc

clean:
	rm -rf hello send_recv mpi_reduce