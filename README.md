[WORK IN PROGRESS]

# **The team**
* Aleksandr Buzdin ([abuzdin](https://profile.intra.42.fr/users/abuzdin)/[baltsaros](https://github.com/baltsaros))
* Marius Thiry ([mthiry](https://profile.intra.42.fr/users/mthiry)/[ElMariuso](https://github.com/ElMariuso))

# **Project description** 
This project is about creating a simple shell. Bash was used as a reference.

## The shell should:
* > Display a prompt when waiting for a new command.
* > Have a working history.
* > Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
* > Not use more than one global variable. Think about it. You will have to explain its purpose.
* > Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
* > Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
* > Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
* > Implement redirections
* > Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
* > Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
* > Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
* > Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
* > Your shell must implement the following builtins (without options): echo (with -n), cd, pwd, export, unset, env, exit

## Bonus:
* > && and || with parenthesis for priorities  
* > Wildcards * should work for the current working directory  

## Allowed functions:
* readline and connected to it
* printf
* malloc, free
* write, open, read, close, unlink
* access
* fork
* wait, waitpid, wait3, wait4
* signal, sigaction, sigemptyset, sigaddset, kill
* exit
* getcdw, chdir, opendir, readdir, closedir
* stat, lstat, fstat
* execve
* dup, dup2
* pipe
* strerror, perror
* isatty, ttyname, ttyslot, ioctl
* getenv
* tcseattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs


# **How to use**
* *make* - to compile the executable file
* execute it with *./minishell*
* there are three user mods: *normal*, *secret* and *uwu*. Try them all!

# **Our approach**
* We splitted the project into seven parts: prompt, tokenization, token simplification (added later), parsing, execution, exit and signal. I (baltsaros) would say that tokenization is the most important, because it determines how other parts are done
* In our tokenization we read character by character and then create an according token (in a linked list). Main tokens that we used are WORD, WSPACE(for white spaces) and some special characters like _$_, _*_, _>_, etc. Values for the latter correspond to ther ASCII values or in case of double characters (like << or >>) to their ASCII value + 100
* We decided to expand _*_ in tokenization and _$_ in token simplification, since it was easier to do this at earlier stages
* In token simplification we fuse some tokens (mainly quotes) and remove others (like white spaces)
* In parsing we open files, initiate heredoc (if any) and creates future commands
* Then we do the execution! Before any _execve_ we check whether a current cmd is builtin or not. We also decided to wait for every child in case of pipe(s) in order to always have a proper output when all or some of the incoming cmds work with the same file. Without _waitpid_ output order or its content for cmds like _echo one > f1 | echo two >> f2 | echo three >> f3_ can be messed up
* We have several structures: one is integral (*t_input*) and is used almost in any other function. Another important structure is *t_cmd* that is actually a linked list. One command is one linked list that consists of command arguments, input and output fds (0 and 1 by default), input and output file names, delimiter (if any) and pipe flag. We also have two other linked lists: one for tokens and another one for envp. Envp are also saved in the _char**_ form in order to be able to send it into another _./minishell_

# **Testing**
Here are some tricky tests to do (compare with bash output):
## Signals
Make sure that you signals work correctly (in terms of behavior and exit code) in the following cases with reading from stdin:
* cat
* cat << end
* ls | cat << end
* cat |
* cat " (if you handle unclosed quotes)

## Redirection and pipes
* sleep 20 | ls
* cat | cat | ls (should display output for *ls* and then wait for input)
* cat > f1 | cat > f2 | ls (saves output only in f1; proper output for ls on stdout)
* caaaat | caaaat | ls (should display output for *ls* and two error messages)
* cat < Makefile > f1 | wc -l < f1 > f2 | echo done > f3
* echo "one two" > f1 | grep "one two" < f1 | wc -l

## Quotes
* echo hi"yo"hi
* echo '$PATH'
* echo '$'PATH
* echo $'PATH'
* echo "$PATH"
* echo "$"PATH
* echo '"$USER"'
* echo ""$USER""
* echo ""
* echo ''

## Builtins
* exit 9 9 (should not exit)
* exit a a (should exit)
* exit 1a (should exit)
* exit 1a 1 (should exit)
* exit 1 1a (should not exit)
* cd (should go to $HOME)
* check that cd updates $PWD and $OLDPWD
* cd [existing folder] [non existsing folder] (no error message, should go to the existing one)
* cd in this case should diplay an error:
> unset HOME  
> cd  
* echo one$?two
* echo "one$?two"
* echo -n one
* echo -nnnnnnnnnn one
* echo -n -n -n -n -n -n one
* echo -nnnnnnnnnnnnn -n -n -n -n -n one
* echo one -n -n -n -n -n -n one
* export one two=three four (if you use *env* after, it should display only envp with values)
* export =
* unset =
* pwd .
* pwd ..
* unset one two=three four (error message, but still should remove *one* and *four*)
* unset PATH (*ls* should display nothing after this)
* make sure that your builtin write in proper output (export, export > f1, echo one > f1 | echo two > f2 | echo three > f3)

## Other cases
* echo $$
* ""
* ''
* $NONEXISTING
* "$NONEXISTING"
*   ls (with spaces before a command)
* $$
* expansion for heredoc (should replace all valid $VAR with their values; if none, just a new line; test against bash):
> cat << EOF  
> $USER  
> "$USER"  
> '$USER'  
> $?$?  
> one$?two
> $  
PS: if eof is between double quotes, no expansion should happen. We did not implement that
* with export and a command (should execute the command if it exists):
> export TEST=echo  
> $TEST hello  
* <> nonexistingfile
* cat <> nonexistingfile
* cat f1 <> nonexistingfile
* cat f1 <> nonexistingfile f2 f3 f4


# **Attempts**
* 1st attempt: 0 % (segfaulted when there were spaces before a command)
* 2nd attempt: 0 % (segfaulted when $VAR does not exist)
* 3rd attempt: 106 % (-4 points because we forgot to revert changes in simple rediraction after debugging)

# **Folders**
**libft** - libft library
It is the only folder that is allowed by the subject

# **Useful resources**
* [Interactive tutorial](https://learngitbranching.js.org/) on git branching
* Tutorials on how to create basic shells: [one](http://www.dmulholl.com/lets-build/a-command-line-shell.html) and [two](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* Another cool [tutorail](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) on writing one's own shell that helped me (baltsaros) a lot!
* Bash manuals: [one](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) and [two](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html). I (baltsaros) prefer the second one
* [Wiki](https://en.wikipedia.org/wiki/Lexical_analysis) on lexer(tokenization)
* [Guide](https://ruslanspivak.com/lsbasi-part1/) on how to build a basic interpreter
* Big [collection](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c) of various links for minishell that I (baltsaros) forgot about :upside_down_face:
* [Dot art](https://emojicombos.com/dot-art-generator) :octocat:
* [Thread](https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux) about colors


# **Tips**
* Read through the subject with your partner and divide the parts
* Ask peers how they approached the project
* Learn about lexer and parser
* Don't be afraid to change your lexer/parsing
* Try to make functions as universal as possible in order to avoid many if conditions (this is one thing that we can improve in our minishell :D)
* Test)
