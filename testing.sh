#!/bin/bash

# Ask the user to input a number between 1 and 21
echo "Enter a number between 1 and 21:"
read number

# Check if the number is valid
if [[ $number -ge 1 && $number -le 21 ]]; then
    # Full path to the test input file
    filename="src/tests/test${number}.txt"
    
    # Check if the file exists
    if [[ -f "$filename" ]]; then
        time ./test < "$filename"
    else
        echo "Error: File '$filename' does not exist."
    fi
else
    echo "Invalid number. Please enter a number between 1 and 21."
fi
