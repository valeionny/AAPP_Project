
all: dataset serial parallel randomized testserial testparallel testrandomized

bindir:
	mkdir -p bin

dataset: bindir
	g++ -o bin/create_dataset src/create_dataset.cpp  #src/dataset_creation.cpp src/file_procs.cpp

serial: bindir
	g++ -o bin/run_serial src/run_serial.cpp #src/serial.cpp src/file_procs.cpp

parallel: bindir
	g++ -fopenmp -o bin/run_parallel src/run_parallel.cpp #src/parallel.cpp src/file.procs.cpp

randomized: bindir
	g++ -fopenmp -o bin/run_randomized src/run_randomized.cpp src/randomized.cpp src/file_procs.cpp # src/parallel.cpp

testserial: bindir
	g++ -o bin/test_serial src/test_serial.cpp

testparallel: bindir
	g++ -fopenmp -o bin/test_parallel src/test_parallel.cpp

testrandomized: bindir
	g++ -fopenmp -o bin/test_randomized src/test_randomized.cpp

clean:
	rm -rf bin

