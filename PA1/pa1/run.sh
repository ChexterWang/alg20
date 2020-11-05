#!/bin/bash

echo "" > log
sorter=(-IS -MS -QS -HS)
for filename in ./inputs/*.in; do
    for i in "${sorter[@]}"; do
        echo "$(basename "$filename" .in) $i"
        echo "$(basename "$filename" .in) $i" >> log
        ./bin/NTU_sort $i "$filename" "outputs/$(basename "$filename" .in).out" >> log
        echo "$(utility/PA1_Result_Checker "$filename" "outputs/$(basename "$filename" .in).out")"
    done
done
