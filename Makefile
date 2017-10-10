
CFLAGS = -Wall

all: dataset serial parallel randomized testserial

bindir:
	mkdir -p bin

dataset: bindir
	g++ $(CFLAGS) -o bin/create_dataset src/create_dataset.cpp  #src/dataset_creation.cpp src/file_procs.cpp

serial: bindir
	g++ $(CFLAGS) -o bin/run_serial src/run_serial.cpp #src/serial.cpp src/file_procs.cpp

parallel: bindir
	g++ $(CFLAGS) -fopenmp -o bin/run_parallel src/run_parallel.cpp #src/parallel.cpp src/file.procs.cpp

randomized: bindir
	g++ $(CFLAGS) -fopenmp -o bin/run_randomized src/run_randomized.cpp src/randomized.cpp src/parallel.cpp src/file_procs.cpp

testserial: bindir
	g++ $(CFLAGS) -o bin/test_serial src/test_serial.cpp
	
clean:
	rm -rf bin

