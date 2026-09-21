#!/usr/bin/env bash
set -e
for f in gen good bad; do g++ -std=c++20 -O2 $f.cpp -o $f; done
while :; do
  ./gen > in
  ./good < in > out1
  ./bad < in > out2
  diff out1 out2 || break
done
