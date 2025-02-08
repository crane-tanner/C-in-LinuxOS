#!/bin/bash

# --- Function to display usage information ---
usage() {
  echo "Usage: $0 <input_file> <group_name> <operation>"
  echo "  <input_file>: Path to the file containing user IDs and encrypted passwords (one user per line, space-separated)."
  echo "  <group_name>: The group to add/remove users from."
  echo "  <operation>: -a (add users) or -r (remove users)"
  exit 1
}

# --- Check for correct number of arguments ---
if [[ $# -ne 3 ]]; then
  echo "Error: Incorrect number of arguments."
  usage
fi

input_file="$1"
group_name="$2"
operation="$3"

# --- Check if input file exists and is readable ---
if [[ ! -f "$input_file" ]] || [[ ! -r "$input_file" ]]; then
  echo "Error: Input file '$input_file' does not exist or is not readable."
  exit 1
fi

# --- Check for valid operation flag ---
if [[ "$operation" != "-a" ]] && [[ "$operation" != "-r" ]]; then
  echo "Error: Invalid operation flag. Use -a (add) or -r (remove)."
  usage
fi

# --- Check if the group exists ---
if ! getent group "$group_name" >/dev/null 2>&1; then
  echo "Group '$group_name' does not exist. Creating..."
  groupadd "$group_name" || { echo "Error: Failed to create group '$group_name'."; exit 1; }
fi


# --- Process the input file ---
while IFS=' ' read -r username encrypted_password; do
  # Skip empty or blank lines
  if [[ -z "$username" ]] || [[ "$username" =~ ^[[:space:]]*$ ]]; then
    continue
  fi

  if [[ "$operation" == "-a" ]]; then
    # Add user
    echo "Adding user '$username' to group '$group_name'..."
    useradd -m -g "$group_name" -p "$encrypted_password" "$username" 2>&1 | tee -a user_add_errors.log
     if [ $? -eq 0 ];
     then
        echo "User '$username' added successfully."
     else
        echo "Error: Could not add User: '$username'."
     fi

  elif [[ "$operation" == "-r" ]]; then
    # Remove user
    echo "Removing user '$username'..."
    userdel -r "$username" 2>&1  | tee -a user_del_errors.log
     if [ $? -eq 0 ];
     then
        echo "User '$username' removed successfully."
     else
        echo "Error: Could not remove User: '$username'."
     fi

  fi
done < <(grep -v -E '^[[:space:]]*$' "$input_file")  # Improved empty line handling


echo "Operation completed."
exit 0
