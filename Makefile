
# double compilation but whatever
all: dataset serial

dataset:
	g++ -o bin/create_dataset src/create_dataset.cpp src/dataset_creation.cpp src/file_procs.cpp 

serial:
	g++ -o bin/run_serial src/run_serial.cpp src/serial.cpp src/file_procs.cpp

clean:
	rm bin/*

