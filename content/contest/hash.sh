code=$(cpp -dD -P -fpreprocessed "$@") || exit 1
printf '%s' "$code" | tr -d '[:space:]' | md5sum | cut -c-6
