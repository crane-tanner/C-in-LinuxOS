#!/bin/bash

# Use grep to find lines indicating session openings and then process them
grep --text 'session opened for user' auth.log.1 | 
while IFS= read -r line; do
    # Extract timestamp (first field)
    timestamp=$(echo "$line" | awk '{print $1}')

    # Extract username, handling variations in the log format.
    user=$(echo "$line" | awk -F'user ' '{print $2}' | awk '{print $1}' | cut -d'(' -f1)

    # Check if user extraction was successful
    if [[ -z "$user" ]]; then
        continue  # Skip to the next line if no user found
    fi

    # Convert timestamp to 24-hour format (HHMM)
    time=$(date -d "$timestamp" +%H%M)

    # Check if time is outside office hours (before 0800 or after 1700)
    if (( $(date -d "$time" +%s) < $(date -d "0800" +%s) )) || \
       (( $(date -d "$time" +%s) >= $(date -d "1700" +%s) )); then
        echo "$timestamp - User: $user logged in outside office hours."
    fi
done
