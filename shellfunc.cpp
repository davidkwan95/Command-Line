#include "shellfunc.h"

//Nomor 1: Nampilin directory
char* Directory()
{
	long size;
	char *buf;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX); // Maximum number of bytes in a pathname
	
	if ((buf = (char *)malloc((size_t)size)) != NULL){
	    ptr = getcwd(buf, (size_t)size);
	    return ptr;
	}else
		printf("Error in getting current directory\n");
}

//Nomor 2: Ganti directory
void changeDir(char* input)
{
	int ret;
	if(strcmp(input, "~")==0)
		ret = chdir (getenv("HOME"));
	else
		ret = chdir (input);

	if (ret!=0) //Change directory fail
		cout<<"fail: No such directory"<<endl;
}

//Nomor 3 dan nomor 4
//Run Program secara sederhana
void RunProgram(char **argv){
	int ret;

	ret = execv(argv[0], argv);
	if(ret!=0){
		ret = execvp(argv[0], argv);
		if(ret!=0)
			cout<<"No such file or directory or command"<<endl;
	}
	
}

//Nomor 5 I/O Redirection
void RunProgram1(char **argv, int stats[], string filein, string fileout){
	int newstdin, newstdout;
	if(stats[0]==1){ //Input redirection on
		newstdin = open(filein.c_str(), O_RDONLY);
		close(0);
		dup(newstdin);
		close(newstdin);
	}

	if(stats[1]==1){ //Output redirection on
		newstdout = open(fileout.c_str(), O_WRONLY|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO);
		close(1);
		dup(newstdout);
		close(newstdout);
	}
		RunProgram(argv);
}

//Nomor 7
void Pipe(char ** argv, char ** argv2, int stats[], int stats2[], string filein, string fileout){
	int thePipe[2];
	pipe(thePipe);
	pid_t child_a=fork();

	//The child will send its output to the parent
	if (child_a==0) { //Child process a
		close (thePipe[0]);
		dup2(thePipe[1], 1);
		RunProgram1(argv, stats, filein, fileout);
		close(thePipe[1]);
	}
	
	else{ //Parent
		close(thePipe[1]);
		waitpid(child_a, NULL, 0);
		dup2(thePipe[0],0);
		RunProgram1(argv2, stats2, filein, fileout);
		close(thePipe[0]);
	}
}