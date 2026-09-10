#!/usr/bin/env bash
set -u
repo=${1:-.}
scripts="$repo/doc/scripts"
skip="$scripts/skip_headers"
pass=0
fail=0
bad=""
while IFS= read -r test; do
  if grep -Fxq "$(basename "$test")" "$skip"; then
    echo "skip $(basename "$test")"
    continue
  fi
  printf '%s: ' "$(basename "$test")"
  if "$scripts/test-compiles.sh" "$repo" "$test"; then
    pass=$((pass + 1))
    echo ok
  else
    fail=$((fail + 1))
    bad="$bad\n$test"
    echo fail
  fi
done < <(find "$repo/content" -name '*.h' | sort)
echo "$pass/$((pass + fail)) tests passed"
if ((fail)); then
  printf 'failed:%b\n' "$bad"
  exit 1
fi
if ((pass == 0)); then
  echo "no headers found"
  exit 1
fi
echo "all headers compile"
