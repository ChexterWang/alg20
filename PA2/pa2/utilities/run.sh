#!/bin/bash

rm outputs/*
utilities/gen.sh
echo -n "" > log
for filename in ./inputs/*0; do
	echo -n "$(basename $filename), " >> log
	/usr/bin/time -f "%e" bin/mps "$filename" "outputs/$(basename $filename)" &>> log
done
