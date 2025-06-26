#!/bin/bash

make

valgrind ./test < input.txt


make clean