#!/usr/bin/env bash

# Conditional
function EvenOrOdd() {
    if [ $(expr $1 % 2) == 0 ]; then
        echo "Even value: $1"
    else
        echo "Odd value: $1"
    fi
}
EvenOrOdd 5
EvenOrOdd 12

input=$1
if [[ "$input" == *"like"* && "$input" != *"hate"* ]]; then
    echo "Nice input!"
else
    echo "Bad input!"
fi
