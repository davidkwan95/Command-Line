#include <iostream>	//Standard input output
#include <fcntl.h>	//open and close file
#include <unistd.h> //fork, pipe, etc
#include <cstdlib>	//malloc and free
#include <readline/readline.h>	//readline
#include <readline/history.h>	//add_history
#include <sys/wait.h>	//for wait
#include <cstring>
#include <string>

using namespace std;

//Nomor 1: Nampilin directory
char* Directory();

//Nomor 2: Ganti directory
void changeDir(char* input);

//Nomor 3 dan nomor 4
//Run Program secara sederhana
void RunProgram(char **argv);

//Nomor 5 I/O Redirection
void RunProgram1(char **argv, int stats[], string filein, string fileout);

//Nomor 7
void Pipe(char ** argv, char ** argv2, int stats[], int stats2[], string filein, string fileout);