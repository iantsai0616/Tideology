#!/usr/bin/env bash
set -u
repo=${1:-.}
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
ulimit -s 65520 2>/dev/null || true
pass=0
fail=0
bad=""
while IFS= read -r test; do
  name=$(basename "$test" .cpp)
  printf '%s: ' "$name"
  if g++ -std=gnu++20 -O2 -Wall -Wfatal-errors -Wconversion \
       "$test" -o "$tmp/$name" && "$tmp/$name"; then
    pass=$((pass+1))
  else
    fail=$((fail+1)); bad="$bad\n$test"
  fi
done < <(find "$repo/stress-tests" -name '*.cpp' | sort)
echo "$pass/$((pass+fail)) tests passed"
if ((fail)); then
  printf 'failed:%b\n' "$bad"
  exit 1
fi
