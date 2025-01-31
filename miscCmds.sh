#!/bin/bash

# myName="Tanner"
# myAge=30
# echo $myName
# echo $myAge

IFS='-'

echo "File name: $0"
echo "First parameter: $1"
echo "Second parameter: $2"

echo "Quoted Values: $@"
echo "Quoted Values: $*"
echo "Total number of parameters: $#"
