#!/bin/bash

make

valgrind ./test < src/input.txt


make clean