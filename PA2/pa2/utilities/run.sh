#!/bin/bash

rm outputs/*
echo -n "" > log
n=(10 20 50 100 200 500 1000 2000 5000 10000 20000 50000)
for i in "${n[@]}"; do
	python utilities/in_gen.py $i "inputs/$i"
	echo -n "$i, " >> log
	/usr/bin/time -f "%U" bin/mps "inputs/$i" "outputs/$i" &>> log
done

