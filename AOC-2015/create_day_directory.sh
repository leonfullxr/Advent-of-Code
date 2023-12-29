#!/bin/bash

# Check if a number is provided as an argument
if [ $# -eq 0 ]; then
    echo "Error: Please provide a number as an argument."
    exit 1
fi

# Extract the number from the argument
number=$1

# Create directory
directory="Day$number"
mkdir "$directory"

# Create input.txt file
touch "$directory/input.txt"

# Create day<number>.py file
touch "$directory/day$number.py"

echo "Directory '$directory' created with input.txt and day$number.py files."

