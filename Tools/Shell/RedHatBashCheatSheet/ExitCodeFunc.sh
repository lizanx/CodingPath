#!/usr/bin/env bash

function PrintMsg() {
    if [ -z "$1" ]; then
        return 22
    else
        echo "Msg: $1"
    fi
}

PrintMsg
res=$?
echo "Result of first call: $res"

PrintMsg "hello"
res=$?
echo "Result of second call: $res"
