#!/bin/bash

g++ gen.cpp -std=c++11 -o gen
g++ A.\ Copy\ \&\ Paste.cpp -std=c++11
javac Main.java

while [[ true ]]; do
    ./gen > input
    java Main < input
    ./a.out < input > my
    diff my output.txt 
    if [[ $? -ne 0 ]]; then
        break;
    fi
done