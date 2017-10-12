#!/bin/bash
if [ -z "$1" ]
then
	echo "No filename provided for output"
	exit 1
fi

echo "Algorithm;DatasetSize;NzPercentage;K;Threads;Time[ms]" > $1
for file in $( ls );
do
	if [[ $file == *".csv" ]]
	then
		(tail -n +2 $file) >> $1
	fi
done

