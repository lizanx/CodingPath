#!/usr/bin/env bash

for i in {2..5}; do
    echo "$i"
done

arr=("hello" "nice" "to" "meet" "you")
declare -A map
map[C++]="high-performance"
map[C#]="elegant-syntax"
map["Python"]="close-to-natural-language"

for element in ${arr[@]}; do
    echo "Array element: $element"
done

for key in ${!map[@]}; do
    echo "Map key: $key"
done

for val in ${map[@]}; do
    echo "Map value: $val"
done

x=2
while [ $x -le 6 ]; do
    echo "While loop: x = $x"
    ((x=x+1))
done
