# A randomized algorithm for sparse addition

This is a C++ implementation of the randomized algorithm described in the *"Optimal parallel randomized algorithms for sparse addition and identification"* paper, written by Paul G.Spirakis.

The paper can be found at https://doi.org/10.1016/0890-5401(88)90039-9.

This was made for the "Advanced Algorithms and Parallel Programming" course at Politecnico di Milano.

## How to compile

On linux:

    make

You will need a fairly recent version of g++ and libtool.

## How to run

After compiling you will find a set of executables under the ```bin``` folder.

- ```create_dataset```: You can use this program to create a set of numbers to sum. You can specify the amount of numbers to create and the ratio of non-zero numbers among them.

- ```run_serial```, ```run_parallell```, ```run_randomized```: these will run the respective algorithms on a specified dataset, and will output the sum.

- ```test_serial```, ```test_parallel```, ```test_randomized```: these will run a benchmark of their respective algorithm's performance, using a specified dataset.

Run an executable without arguments to get more details about which parameters they need.

The ```benchmarks.py``` python script is also available to perform more extensive benchmarks. It can run batches of tests on any combinations of parameters, over all the algorithms.
