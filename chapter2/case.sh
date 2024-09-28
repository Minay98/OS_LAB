read -p "Enter a day of the week: " day

case $day in
  "Monday")
    echo "Start of the work week."
    ;;
  "Friday")
    echo "Almost the weekend!"
    ;;
  "Saturday"|"Sunday")
    echo "It's the weekend!"
    ;;
  *)
    echo "Not a valid day."
    ;;
esac
