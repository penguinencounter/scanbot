# (1) prompt user, and read command line argument
if [ "$1" == "" ]
then
    clear
    read -p "Push, pull, and prune ? " answer
else
    answer="$1"
    echo "command-line args: $answer"
fi

# (2) handle the command line argument we were given
while true
do
  case $answer in
   [yY]* ) git push
	   git pull
	   git remote prune origin
           break;;

   [nN]* ) echo "Canceled"
           exit;;

   * )     echo "Invalid input; canceled"; break ;;
  esac
done
