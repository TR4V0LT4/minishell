

➜ minishell echo $USER"$"$PWD'$$$$$$$$$$$'USER"$PWD"
wlahyani/Users/wlahyani/Desktop/ex$$$$$$$$$$$USER/Users/wlahyani/Desktop/ex
➜ minishell '                          "$PWD" '
minishell: syntax error unexpected token `\n'
➜ minishell echo '                          "$PWD" '
minishell: syntax error unexpected token `\n'
➜ minishell echo '                          "$PWD" ' '\
minishell: syntax error unexpected token `\n'
➜ minishell echo '                          "$PWD" ' '
minishell: syntax error unexpected token `\n'
➜ minishell echo '                          "$PWD"
minishell: syntax error unexpected token `\n'
➜ minishell echo "$PWD"
/Users/wlahyani/Desktop/ex
➜ minishell echo '"$PWD"'
"$PWD"
➜ minishell echo ' "$PWD"'
minishell: syntax error unexpected token `\n'
➜ minishell echo ' "$PWD" '
minishell: syntax error unexpected token `\n'
➜ minishell echo ' ›"$PWD" '




bash-3.2$ export a="ls  -la"
bash-3.2$ $a
total 2696
drwxr-xr-x  11 wlahyani  2019      374 Feb 16 23:42 .
drwx------   4 wlahyani  2019      136 Feb 16 22:47 ..
drwxr-xr-x  12 wlahyani  2019      408 Feb 16 22:48 .git
-rw-r--r--   1 wlahyani  2019     1525 Feb 16 23:21 Makefile
-rw-r--r--   1 wlahyani  2019      984 Feb 16 22:48 README.md
-rw-r--r--   1 wlahyani  2019  1307414 Feb 16 22:48 en.subject.pdf
drwxr-xr-x   3 wlahyani  2019      102 Feb 16 22:48 include
-rw-r--r--   1 wlahyani  2019     1514 Feb 16 22:48 install_brew.sh
drwxr-xr-x  83 wlahyani  2019     2822 Feb 16 23:21 lib_ft
-rwxr-xr-x   1 wlahyani  2019    53328 Feb 16 23:42 minishell
drwxr-xr-x  19 wlahyani  2019      646 Feb 16 23:42 src
bash-3.2$ echo "asdads" > $a
bash: $a: ambiguous redirect
bash-3.2$ cat $a
cat: ls: No such file or directory
cat: -la: No such file or directory


echo oui | echo non | echo something | grep something ==> oui expect  something


=> expand inside heredoc ✅
=> signlas          ✅
➜ minishell exit 288 ✅
[1]    18412 segmentation fault  ./minishell ✅
=> multiple pipes   ✅
=> heredoc  parse delimeter ✅
=> $? ✅
=> cat < l ✅

=> string parser "\0" 

=>export
=>env
=>builtins

=>➜ minishell ➜ minishell ctrl + c
=> ➜ minishell < scat  segv
<< l ls | < Makefile cat > file401 | << h ls >> file401 || << q open the heredocs before the syntax error
ls > file401 | cat file401 >> file401 hanging 
ls > file1 | cat file1
➜ minishell export | grep ads
adsvdv=(null)
➜ minishell export test==
bash-3.2$ export
unset 



=> exit status