#!/bin/bash
for user in $(who | awk '{print $1}')
do
  echo "Logged in user: $user"
done
