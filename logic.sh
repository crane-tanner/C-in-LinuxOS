#!/bin/bash

# Check if an argument is provided
if [ -z "$1" ]; then
  echo "Please provide a number as an argument."
  exit 1
fi

# Get the number from the argument
number=$1

# Check the number against 50
if [[ $number -lt 50 ]]; then
  echo "The number $number is less than 50."
elif [[ $number -eq 50 ]]; then
  echo "The number $number is equal to 50."
else
  echo "The number $number is greater than 50."
fi
