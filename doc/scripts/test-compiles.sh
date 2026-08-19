#!/usr/bin/env bash
set -u
repo="$1"
file="$2"
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
printf '#include "%s/content/contest/template.cpp"\n#include "%s"\n' \
  "$(cd "$repo" && pwd)" "$(cd "$(dirname "$file")" && pwd)/$(basename "$file")" > "$tmp/test.cpp"
g++ -std=gnu++20 -O2 -Wall -Wextra -Wfatal-errors -Wconversion \
  "$tmp/test.cpp" -o "$tmp/test"
