#!/usr/bin/bash

function Greet() {
    echo "Hello, $1!"
}

Greet "Gavin"
Greet "Calvin"

function SetValue() {
    echo "Set Value to $1"
    Value=$1
}
Value="ANSI-C"
echo "Value: $Value"
SetValue "C++"
echo "Value: $Value"
