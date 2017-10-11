#!/bin/bash
if [ -z "$1" ]
then
	echo "No filename provided for output"
fi

touch $1
for file in $( ls );
do
	if [[ $file == *".csv" ]]
	then
		(tail -n +2 $file) >> $1
	fi
done

