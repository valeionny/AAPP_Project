#!/bin/env python3
import os

output_name = "combined.csv"
with open(output_name, 'w') as out:
    out.write("Algorithm;DatasetSize;NzPercentage;K;Threads;Time[ms]\n")
    files = os.listdir()
    for file in files:
        if file[-4:] == ".csv":
            with open(file, 'r') as csvin:
                data = csvin.read()
                data = '\n'.join(data.split('\n')[1:])  # remove first line
                out.write(data)
