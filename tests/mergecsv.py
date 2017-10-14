#!/bin/env python3
import sys, os

if len(sys.argv) < 2:
    print("No filename provided for output")
    exit(1)

output_name = sys.argv[1]
with open(output_name, 'w') as out:
    out.write("Algorithm;DatasetSize;NzPercentage;K;Threads;Time[ms]\n")
    files = os.listdir()
    for file in files:
        if file[-4:] == ".csv":
            with open(file, 'r') as csvin:
                data = csvin.read()
                data = '\n'.join(data.split('\n')[1:])  # remove first line
                out.write(data)
