#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

void unzip(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		//printf(" -> %s\n", path);
		execl("/usr/bin/unzip", 
	      "/usr/bin/unzip",
	      path,
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

void del_folder(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		execl("/usr/bin/rm", //rm = remove
	      "/usr/bin/rm",
	      "-r", //delete recursive, jadi dir dan isinya
		  path, //delete folder
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

void make_dir(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		//printf(" -> %s\n", path);
		execl("/usr/bin/mkdir", 
	      "/usr/bin/mkdir",
	      path,
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

int split_string(){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
	/* print all the files and directories within directory */
	while ((ent = readdir (dir)) != NULL) {
		if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, "2a") != 0 && 
			strcmp(ent->d_name, "2a.c") != 0 && strcmp(ent->d_name, "pets.zip") != 0){
			//printf ("%s\n", ent->d_name);

			const char s[2] = ";";
			char *jenis, *nama, *usia;
			
			jenis = strtok(ent->d_name, s);
			nama = strtok(NULL, s);
			usia = strtok(NULL, s);
			usia[strlen(usia)-4] = 0; //menghapus jpg nya
			
			char *path = malloc(64*sizeof(char));
			sprintf(path, "./petshop/%s", jenis);

			//make_dir(path);
			printf("%s\n", path);
			free(path);
			//printf( " %s\n", jenis);
			// printf( " %s\n", nama);
			// printf( " %s\n", usia);
		}
	}
	closedir (dir);
	} else {
	/* could not open directory */
	perror ("");
	return EXIT_FAILURE;
	}
}

//rm -r */

int main(){
    //unzip("pets.zip");
	// del_folder("apex_cheats/");
	// del_folder("musics/");
	// del_folder("unimportant_files/");
    // //printf("success\n");
	split_string();
	//make_folder();
}