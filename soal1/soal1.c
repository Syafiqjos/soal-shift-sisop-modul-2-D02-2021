#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void make_directory(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		printf("Creating Directory -> %s\n", path);
		execl("/bin/mkdir", 
	      	"/bin/mkdir",
	      	path,
	      	NULL);
	      	exit (0);
	}
}

int main(){
	// no 1a
	make_directory ("Musyik");
	make_directory ("Fylm");
	make_directory ("Pyoto");
	
	//no 2a
	//"foto = https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view"
	//"musik = https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view"
	//"film = https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view"
	
}
