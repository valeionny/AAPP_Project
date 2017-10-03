
# double compilation but whatever
all: dataset serial

dataset:
	mkdir -p bin
	g++ -o bin/create_dataset src/create_dataset.cpp src/dataset_creation.cpp src/file_procs.cpp 

serial:
	mkdir -p bin
	g++ -o bin/run_serial src/run_serial.cpp src/serial.cpp src/file_procs.cpp

clean:
	rm -rf bin

