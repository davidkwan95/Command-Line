# Tubes-OS-1-Command-Line
A simple command line project for a better understanding of forking which runs in UNIX based Operating System.

# Features
1. Showing current working directory
2. Change current directory using cd <PATH>
3. Execute a program from a directory
4. Execute an external program from Environmental Path
5. Redirect STDIN and STDOUT, ex:
  ./main < input.txt > output.txt
6. Get histories of command by using up and down arrow key
7. Pipeline between two process, ex:
  cat out.txt | wc -l
8. A combination between STDIN/STDOUT redirection and pipeline

# Note
The get histories of command feature uses another library history.h, so further installation of this library is needed.
Main program is in shell.cpp, which do command processing.
shellfunc.cpp: Procedures/function in the features
To compile, please refer to "makefile.txt"

# Todo list
1. jobs: list all running process and its PID
2. fg: continuing process which is stopped with Ctrl+Z
3. kill: stopped a process which is running
4. Supporting multiple pipelines
5. A cleaner code, some functions have too many parameters
