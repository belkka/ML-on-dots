#/bin/bash

echo $1

g++ -oa Checker.cpp
./a < $1
