#!/usr/bin/env bash

i=0
while true
do
    echo $i
    ((++i))
    ./gen > in
    ./good < in > out1
    ./bad < in > out2
    diff out1 out2 || break
done