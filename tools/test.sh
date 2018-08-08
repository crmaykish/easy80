#!/bin/sh

echo "Running all unit tests..."

for test_script in ./build/test_*; do
    ./"$test_script"
    echo ""
    echo ""
done