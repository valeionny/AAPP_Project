
all: dataset serial parallel randomized testserial testparallel testrandomized

bindir:
	mkdir -p bin

dataset: bindir
	g++ -o bin/create_dataset src/create_dataset.cpp src/dataset_creation.cpp src/file_procs.cpp

serial: bindir
	g++ -o bin/run_serial src/run_serial.cpp src/serial.cpp src/file_procs.cpp

parallel: bindir
	g++ -fopenmp -o bin/run_parallel src/run_parallel.cpp src/parallel.cpp src/file_procs.cpp

randomized: bindir trng
	libtool --mode=link g++ -fopenmp -o bin/run_randomized -Ilibs/trng-installed/include src/run_randomized.cpp src/randomized.cpp src/file_procs.cpp libs/trng-installed/lib/libtrng4.a src/parallel.cpp

testserial: bindir
	g++ -o bin/test_serial src/test_serial.cpp src/serial.cpp src/file_procs.cpp src/time_benchmark.cpp

testparallel: bindir
	g++ -fopenmp -o bin/test_parallel src/test_parallel.cpp src/parallel.cpp src/file_procs.cpp src/time_benchmark.cpp

testrandomized: bindir
	libtool --mode=link g++ -fopenmp -o bin/test_randomized -Ilibs/trng-installed/include src/test_randomized.cpp libs/trng-installed/lib/libtrng4.a src/randomized.cpp src/parallel.cpp src/file_procs.cpp src/time_benchmark.cpp

trng: trng-extract
	if ! [ -d $(CURDIR)/libs/trng-installed ]; then cd libs/trng-4.19 && ./configure --prefix=$(CURDIR)/libs/trng-installed && make && make install; else echo "The TRNG libs have already been installed."; fi

trng-extract:
	if ! [ -d libs/trng-4.19 ]; then tar xzf libs/trng-4.19.tar.gz -C libs; else echo "The TRNG sources have already been extracted."; fi

clean:
	rm -rf bin 

clean-trng:
	rm -rf libs/trng-4.19
	rm -rf libs/trng-installed
