#!/bin/bash
names=()
while IFS= read -r line; do 
	names+=("$line")
done < names.txt

sorted_names=($(printf "%s\n" "${names[@]}" | sort))
echo "Sorted names:"
for name in "${sorted_names[@]}"; do 
	echo "$name"
done 
desired_name="Joshua"
if [[ " ${sorted_names[*]} " == *" ${desired_name} "* ]]; then
echo "$desired_name found in the list."
else 
echo "$desired_name not found in the list."
fi 



