#!/usr/bin/env bash

function FileExists() {
    if test -f "$1"; then
        echo "$1 exists."
    else
        echo "$1 doesn't exist!"
    fi
}

FileExists Array.sh
FileExists ../Map.sh

for file in ./*.sh; do
    echo "file: $file"
done

for dir in ../../*; do
    echo "dir: $dir"
done
