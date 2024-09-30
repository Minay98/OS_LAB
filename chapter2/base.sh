echo "$a"
echo "The value of \"a\" is $a."
a=`echo Hello! # Assigns result of 'echo' command to 'a'
echo $a
a=`ls -l # Assigns result of 'ls -l' command to 'a'
echo "$a"
echo $a # Unquoted, however, it removes tabs and newlines.
# Assignment using 'let'
let a=16+5
echo "The value of a is now $a."
