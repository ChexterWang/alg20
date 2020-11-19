#!/bin/bash

rm outputs/*
echo -n "" > $1 
n=(10 20 50 100 200 500 1000 2000 5000 10000 20000 50000 100000 150000 180000)
for i in "${n[@]}"; do
	# python3 utilities/in_gen.py $i "inputs/$i"
	echo "$i"
	echo -n "$i, " >> $1
	/usr/bin/time -f "%e, %U, %M" bin/mps "inputs/$i" "outputs/$i" &>> $1
done

