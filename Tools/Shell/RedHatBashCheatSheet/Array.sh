#!/usr/bin/bash

my_arr=("Hello" "Linux" "Bash" "Script")
echo ${my_arr[0]}
echo ${my_arr[3]}
unset my_arr[1]
echo ${my_arr[@]}
my_arr+=("NewValue")
echo ${my_arr[@]}
echo "Count of elements: ${#my_arr[@]}"
