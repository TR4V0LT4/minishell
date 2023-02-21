
while [ 1 ]
do
leaks minishell | grep "leaked bytes"
sleep 1
clear
done

