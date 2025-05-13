#!/usr/bin/bash

MSG="aBcDeF"
echo "Upper case: ${MSG^^}"
echo "Lower case: ${MSG,,}"

MSG="Hello, Gavin!"
echo ${MSG//Gavin/Daphne}

MSG="I'm 23 years old!"
echo ${MSG//[a-zA-Z]/X}

MSG="The Rolling Stone"
echo ${MSG:4}
echo ${MSG:4:7}
echo ${MSG#The}
echo ${MSG%Stone}
