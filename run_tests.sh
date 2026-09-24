#!/usr/bin/env sh

set -eu

echo "Running unit tests:"

for test_binary in "$@"
do
    "$test_binary"
done

echo "All unit tests passed."
