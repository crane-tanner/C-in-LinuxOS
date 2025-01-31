#!/bin/bash
# i. Echo current directory
echo "Current directory $(pwd)"
# ii. Change directory to home directory
cd "$HOME"
echo "Current directory (after cd to home) $(pwd)"

# iii. Change directory to child directory in home 
child_dir="C_programming"
if [ -d "$HOME" ]; then
	cd "$child_dir"
	echo "Current directory (after cd to $child_dir): $(pwd)"
	else 
	echo "Error: directory '$child_dir' not found in home/tanner directory"
	exit 1 
fi 
#iv. list all files ending with .c 

echo "Files ending with .c:"
find  . -maxdepth 1 -name "*.c" -print
#v. go back to home directory 
cd "$HOME"
echo "After cd to home: $(pwd)"

