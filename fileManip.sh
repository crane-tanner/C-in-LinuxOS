
#!/bin/bash

# i. go to home directory
cd "$HOME" || { echo "Error: Could not change to home directory." ; exit 1 ; }
echo "Current directory: $(pwd)"

# ii. make child directory mycode and go to 
mkdir "mycode" || { echo "Error: Could not create mycode directory (already exists?)." ; exit 1 ; }
cd mycode || { echo "Error: Could not change to mycode directory." ; exit 1 ; }
echo "Current directory: $(pwd)"

# iii. print all .c files from assignments to mycode
cp /home/tanner/Desktop/Assignments/*.c . || { echo "Warning: No .c files in /home/tanner/Desktop/Assignments or copy failed." ; }
cd .. || { echo "Error: Could not navigate up from mycode directory." ; exit 1 ; }

mkdir mycode2 || { echo "Error: Could not create mycode2 directory (already exists?)." ; exit 1 ; }
cp -r mycode/* mycode2/ || { echo "Error: Could not copy from mycode to mycode2." ; exit 1 ; }

mv mycode deadcode || { echo "Error: Could not rename mycode to deadcode." ; exit 1 ; }

rm -rf deadcode || { echo "Error: Could not remove deadcode directory." ; exit 1 ; }

echo "Script completed"




