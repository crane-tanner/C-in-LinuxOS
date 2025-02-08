#!/bin/bash

#get password from command-line argument
password="$1"

#initialize error flags ( 0 = pass, 1 = fail)
length_check=0
numeric_check=0
special_char_check=0
#Error message accumulation 
error_messages=""

#check length
if (( ${#password} < 8)); then 
	length_check=1
	error_messages+="Password must be at least 8 characters long.\n"
fi
#check for numeric char

if [[ ! "$password" =~ [0-9]  ]]; then 
	numeric_check=1
	error_messages+="Password must contain at least one numeric character.\n"
fi 
#check special char 
if [[ ! "$password" =~ [@#\$%\*\+=] ]]; then 
	special_char_check=1
	error_messages+="Password must contain at least one of the following special characters: @, #, $, %, *, +, = \n"
fi 

if (( length_check == 1 || numeric_check == 1 || special_char_check == 1 )); then
	echo "Password Validation failed"
	echo -e "$error_messages"
else 
	echo "Password meets all requirements."
fi
exit 0




