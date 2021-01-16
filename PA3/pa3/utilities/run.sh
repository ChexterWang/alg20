#!/bin/bash

rm out/*
echo -n "" > $1 
for i in u1 u2 u3 u4; do
	echo "$i"
	echo -n "$i, $(sed -n 2p in/$i | tr -d '\n'), $(sed -n 3p in/$i | tr -d '\n'), " >> $1
	/usr/bin/time -f "%e, %U, %M" bin/cb "in/$i" "out/$i" &>> $1
done