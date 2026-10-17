#!/usr/bin/env bash
for f in gen good bad; do g++ -std=c++20 -O2 $f.cpp -o $f || exit; done
i=1
while :; do
  echo $i
  ./gen $i > in
  ./good < in > out1
  timeout 2 ./bad < in > out2 || { echo "RE/TLE"; break; }
  diff out1 out2 || break
  ((++i))
done
