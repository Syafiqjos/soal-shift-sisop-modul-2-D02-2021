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
	
}
