#!/bin/bash

rm out/*
echo -n "" > $1 
for i in d1 d2 d3; do
	echo "$i"
	echo -n "$i, $(sed -n 2p in/$i | tr -d '\n'), $(sed -n 3p in/$i | tr -d '\n'), " >> $1
	/usr/bin/time -f "%e, %U, %M" bin/cb "in/$i" "out/$i" &>> $1
done
