#!/bin/bash

# Ask the user to input a number between 1 and 21
echo "Enter a number between 1 and 21:"
read number

# Check if the number is valid
if [[ $number -ge 1 && $number -le 21 ]]; then
    # Create the filename based on the user's input
    filename="tests/test${number}.txt"
    
    # Check if the file exists
    if [[ -f "$filename" ]]; then
        # Run the binary with the file as input using redirection
        time ./test < "$filename"
    else
        # If the file does not exist, show an error message
        echo "Error: File '$filename' does not exist."
    fi
else
    # If the number is invalid, show an error message
    echo "Invalid number. Please enter a number between 1 and 21."
fi