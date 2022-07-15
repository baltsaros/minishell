## **Project description** 
This project is about creating a simple shell. Bash was used as a reference.

The shell should:
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


Allowed functions:
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


## **How to use**
* *make* - to compile the executable file
* execute it with *./minishell*
* there are three user mods: *normal*, *secret* and *uwu*. Try them all!

## **Our approach**
* 

## **Testing**
The project was tested by us and peers

## **Attempts**


## **Folders**
**srcs** - source files

**include** - header

**libft** - libft library

## **Useful resources**
* []() 

## **Tips**
* Ask peers
* Google
* Keep going
* Test
* Rewrite
* Test
* 
