/* Description: A simple command shell */
/* Created by: 	David / 13513019
				Gerry Kastogi / 13513011
				Jessica Andjani / 13513086
*/
/*** Compile instruction: g++ shell.cpp -o shell -lreadline ***/

#include "shellfunc.h"	//Self-made

using namespace std;

string NextToken(string temp, int &i){
	string arg;

	//Ignore blank
	while(i<temp.length() && temp[i]==' '){
		i++;
	}

	//If first character encounter special delimiter
	if((temp[i]=='>' || temp[i]=='<' || temp[i]=='|') && i<temp.length()){
		arg=temp[i];
		i++;
	}
	else{ //Read command until found delimiter
		while(i<temp.length()){
			if (temp[i]=='>' || temp[i]=='<' || temp[i]==' ' || temp[i]=='|'){
				break;
			}
			else{
				arg+=temp[i];
				i++;
			}
		}
	}
	return arg;
}

int ReadCommand(string temp, int& i, char ** argv, int (&stats)[3], string& filein, string& fileout){
	string arg;
	char *cstr;
	int argc=0;
    do{
		arg=NextToken(temp, i);
		if(!arg.compare("<")){
			filein=NextToken(temp,i);
			stats[0]=1;
		}
		else if(!arg.compare(">")){
			fileout=NextToken(temp,i);
			stats[1]=1;
		}
		else if(!arg.compare("|")){	//Pipeline
			stats[2]=1;
			break;
		}
		else{
			cstr = new char[arg.size()];
			strcpy(cstr, arg.c_str());
			argv[argc] = cstr;
			argc++;
		}
	}
	while (i<temp.length());

	argv[argc] = NULL;

	return argc;
}

int ParseCommand(string temp, char ** argv, char ** argv2, int (&stats)[3], int (&stats2)[3], string& filein, string& fileout){
	int argc=0; //Argumen ke berapa
    int i=0;

    argc+=ReadCommand(temp, i,argv, stats, filein, fileout);
    if(stats[2]==1){	//Pipeline occured
    	argc+=ReadCommand(temp, i, argv2, stats2, filein, fileout);
    }
    return argc;
}

void RunCommand(char ** argv, char ** argv2, int stats[], int stats2[], string filein, string fileout){
	//Change Directory
	if(argv[0]==NULL){
		//Do Nothing
	}
	else if(strcmp(argv[0], "cd")==0)
		changeDir(argv[1]);
	//Exit Program
	else if(strcmp(argv[0], "quit")==0)
		exit(0);
	else{
		pid_t pid=fork();
		if(pid==0){ //Child Process
			if(stats[2]==1) //Pipeline
				Pipe(argv, argv2, stats, stats2, filein, fileout);
			else //Run Program Normally
				RunProgram1(argv, stats, filein, fileout);
		}
		else if (pid>0){
			waitpid(pid,NULL,0);
		}
	}
}

int main(){
	int argc;	//Jumlah argv yang terpakai
	char* argv[100];	//Menampung parameter
	char* argv2[100];	//Dipakai jika menggunakan pipeline
	string filein, fileout;	//Digunakan jika menggunakan redirect

	//Program terminalnya
	while (true){
		/*	stats[0]==1 jika menyimpan redirect in 	*/
		/*	stats[1]==1 jika menyimpan redirect out */
		/*	stats[2]==1 jika terjadi pipeline	*/
		int stats[] = {0, 0, 0};
		int stats2[] = {0, 0, 0};	//Digunakan jika memakai pipeline

		rl_bind_key('\t', rl_complete);	//Auto complete on
		char* buf;
		char* dir;
		strcpy(dir,"~"); strcat(dir, Directory()); strcat(dir,"> "); //Concat gak jelas
		
		buf = readline(dir);	//Baca input
		if(buf[0]!=0){
			add_history(buf);
			string temp = buf;
			//Parse
			argc= ParseCommand(temp, argv, argv2, stats, stats2, filein, fileout);
			//Jalanin command yang sudah di parse
			RunCommand(argv, argv2, stats, stats2, filein, fileout);
		}
		free(buf);
	}

	return 0;
}