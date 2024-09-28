#!/bin/bash

function greet_user() {
  echo "Hello, $1!"
  echo "Welcome to the system."
  return 0
}

greet_user "Alice"
