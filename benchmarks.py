# MIT License
#
# Copyright (c) 2017 Pietro Ferretti, Valentina Ionata
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
from subprocess import check_call

size_list = [100000, 1000000]
perc_list = [10, 1, 0.1, 0.01]
k_list = [1, 5, 10]
threads_list = [1, 2]

dataset_dir = 'datasets'
result_dir = 'tests'
reps = 100

# check directories
if not os.path.exists(dataset_dir):
    os.makedirs(dataset_dir)

if not os.path.exists(result_dir):
    os.makedirs(result_dir)

# perform benchmarks
for size in size_list:
    print ('* Size {} *'.format(size))
    for perc in perc_list:
        print ('* Nonzero Percentage {} *'.format(perc))
        # create dataset
        dataset_path = dataset_dir + 'dataset_' + str(size) + '_' + str(perc).replace('.', '') + '.txt'
        dataset_path = '{}/dataset_{}_{}.txt'.format(dataset_dir, size, str(perc).replace('.', ''))

        if not os.path.exists(dataset_path):
            check_call(['bin/create_dataset', str(size), str(perc), dataset_path])

        # run serial
        result_path = '{}/serial_{}_{}.csv'.format(result_dir, size, str(perc).replace('.', ''))
        check_call(['bin/test_serial', dataset_path, result_path, str(reps)])

        for threads in threads_list:
            print ('* Threads: {} *'.format(threads))
            # run parallel
            result_path = '{}/parallel_{}_{}_t{}.csv'.format(result_dir, size, str(perc).replace('.', ''), threads)
            check_call(['bin/test_parallel', dataset_path, result_path, str(threads), str(reps)])

            # run randomized
            for k in k_list:
                print ('* K: {} *'.format(k))
                result_path = '{}/randomized_{}_{}_k{}_t{}.csv'.format(result_dir, size, str(perc).replace('.', ''), k, threads)
                check_call(['bin/test_randomized', dataset_path, result_path, str(k), str(threads), str(reps)])

print ('Benchmarks complete!')
