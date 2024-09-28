#!/bin/bash

counter=0

while [ $counter -lt 10 ]
do
  echo "The counter is $counter"
  let counter=counter+1
done
