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
    print '* Size {} *'.format(size)
    for perc in perc_list:
        print '* Nonzero Percentage {} *'.format(perc)
        # create dataset
        dataset_path = dataset_dir + 'dataset_' + str(size) + '_' + str(perc).replace('.', '') + '.txt'
        dataset_path = '{}/dataset_{}_{}.txt'.format(dataset_dir, size, str(perc).replace('.', ''))

        if not os.path.exists(dataset_path):
            check_call(['bin/create_dataset', str(size), str(perc), dataset_path])

        # run serial
        result_path = '{}/serial_{}_{}.csv'.format(result_dir, size, str(perc).replace('.', ''))
        check_call(['bin/test_serial', dataset_path, result_path, str(reps)])

        for threads in threads_list:
            print '* Threads: {} *'.format(threads)
            # run parallel
            result_path = '{}/parallel_{}_{}_t{}.csv'.format(result_dir, size, str(perc).replace('.', ''), threads)
            check_call(['bin/test_parallel', dataset_path, result_path, str(threads), str(reps)])

            # run randomized
            for k in k_list:
                print '* K: {} *'.format(k)
                result_path = '{}/randomized_{}_{}_k{}_t{}.csv'.format(result_dir, size, str(perc).replace('.', ''), k, threads)
                check_call(['bin/test_randomized', dataset_path, result_path, str(k), str(threads), str(reps)])

print 'Benchmarks complete!'
