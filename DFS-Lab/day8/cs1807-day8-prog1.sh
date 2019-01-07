#!/usr/bin/env bash
touch prob1-output.txt
for i in 100 500 {1000..10000..1000}
do
    echo -n "$i "
    for j in {1..5}
    do
        ./prog1 $i >> prob1-output.txt
    done
    echo ""
done
