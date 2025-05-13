#!/usr/bin/bash

declare -A score
score[A]=100
score[B]=80
score[C]=60
score[F]=0

echo "Keys: ${!score[@]}"
echo "Values: ${score[@]}"
echo "A - ${score[A]}"
unset score[B]
echo "Keys: ${!score[@]}"
echo "Count of elements: ${#score[@]}"
