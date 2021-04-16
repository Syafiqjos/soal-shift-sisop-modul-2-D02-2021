#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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
	else {
		int status=0;
		waitpid (child_id,&status,0);
	}
}

void download_drive(char *url, char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		char *url_new = malloc (128 * sizeof (char));
		sprintf (url_new,"https://drive.google.com/uc?id=%s&export=download", url); 
		printf("downloading drive -> %s\n", url);
		execl("/usr/bin/wget", 
	      	"/usr/bin/wget",
	      	"--no-check-certificate",
	      	url_new,
		"-O",
	      	path,
	      	NULL);
		free (url_new);
	      	exit (0);
	}
	else {
		int status=0;
		waitpid (child_id,&status,0);
	}
}

void unzip(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		printf("Unziping file -> %s\n", path);
		execl("/usr/bin/unzip", 
	      	"/usr/bin/unzip",
	      	path,
	      	NULL);
	      	exit (0);
	}
	else {
		int status=0;
		waitpid (child_id,&status,0);
	}
}

void move_files(char *source, char *destination){
	pid_t child_id=fork ();
	if (child_id==0){
		printf("Moving Files -> %s -> %s\n", source,destination);
		execl("/usr/bin/mv", 
	      	"/usr/bin/mv",
	      	source,destination,
	      	NULL);
	      	exit (0);
	}
	else {
		int status=0;
		waitpid (child_id,&status,0);
	}
}

void delete_files(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		printf("Deleting Files -> %s\n", path);
		execl("/usr/bin/rm", 
	      	"/usr/bin/rm",
	      	"-r",
	      	path,
	      	NULL);
	      	exit (0);
	}
	else {
		int status=0;
		waitpid (child_id,&status,0);
	}
}

void zip_files (char *path, char *source1, char *source2, char *source3){
	pid_t child_id=fork ();
	if (child_id==0){
		printf("zipping files -> %s\n", path);
		execl("/usr/bin/zip", 
	      	"/usr/bin/zip",
	      	"-r",
	      	path,
	      	source1,source2,source3,
	      	NULL);
	      	exit (0);
	}
	else {
		int status=0;
		waitpid (child_id,&status,0);
	}
}

int iteration_files(char *source, char *destination){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (source)) != NULL) {
	/* print all the files and directories within directory */
	while ((ent = readdir (dir)) != NULL) {
		if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
		char *path=malloc(64 * sizeof (char));
		strcat(path,source);
		strcat(path,"/");
		strcat(path,ent->d_name);
		move_files(path,destination);
		free (path);
			
			//printf ("%s\n", ent->d_name);

		}
	}
	closedir (dir);
	} else {
	/* could not open directory */
	perror ("");
	return EXIT_FAILURE;
	}
}

char *get_current_formatted_time(){
	time_t current_time = time(NULL);
	struct tm* ptr = localtime(&current_time);
	
	char *filename = malloc(32 * sizeof(char));
	
	strftime(filename, 32, "%Y-%m-%d_%H:%M:%S", ptr);
	return filename;
}

void run_timer(char *target_time){

	char *now_time = malloc (64 * sizeof(char));
	
	bool is_running = true;

	while (is_running){
		now_time = get_current_formatted_time ();
		printf("menunggu hingga -> %s -> %s\n", now_time,target_time);

		if (strcmp (now_time,target_time)==0 ){
			zip_files ("Lopyu_Stevany.zip","Musyik","Pyoto","Fylm");
			return ;
			
			
		}
	}
}
int main(){
	// no 1a
	make_directory ("Musyik");
	make_directory ("Fylm");
	make_directory ("Pyoto");
	
	//no 1b
	//"foto = https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view"
	//"musik = https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view"
	//"film = https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view"
	
	download_drive ("1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD","foto.zip");
	download_drive ("1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J","musik.zip");
	download_drive ("1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp","film.zip");
	
	//no 1c
	unzip ("foto.zip");
	unzip ("musik.zip");
	unzip ("film.zip");
	
	//no 1d
	
	iteration_files ("MUSIK","Musyik");
	iteration_files ("FILM","Fylm");
	iteration_files ("FOTO","Pyoto");
	
	//no 1e 
	//run_timer ("2022-04-09_16:22:00");
	run_timer ("2021-04-16_10:41:00");

	//no 1f
	delete_files ("Musyik");
	delete_files ("Fylm");
	delete_files ("Pyoto");
	delete_files ("MUSIK");
	delete_files ("FILM");
	delete_files ("FOTO");
	delete_files ("musik.zip");
	delete_files ("foto.zip");
	delete_files ("film.zip");

}
