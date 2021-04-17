#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

//char *isi_ket;

void unzip(char *source, char *destination){
	pid_t child_id=fork ();
	if (child_id==0){
		execl("/usr/bin/unzip", 
	      "/usr/bin/unzip",
	      source,
		"-d",
		destination,
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
		execl("/bin/rm", //rm = remove
	      "/bin/rm",
	      "-r", //delete recursive, jadi dir dan isinya
		  "-d", 
		  path, //delete folder
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

void make_ket(char *filename, char *isi_ket){
	FILE *file = fopen(filename, "a");

	if (file){
		fprintf(file, "%s\n", isi_ket);
		fclose(file);
	}

}

void make_dir(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		//printf(" -> %s\n", path);
		execl("/bin/mkdir", 
	      "/bin/mkdir",
		  "-p",
	      path,
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

void del_file(char *path){
	pid_t child_id=fork ();
	if (child_id==0){
		execl("/bin/rm", //rm = remove
	      "/bin/rm",
		  path, //delete folder
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

void copy_file(char *source, char *destination){
	pid_t child_id=fork ();
	if (child_id==0){
		//printf(" -> %s\n", path);
		execl("/bin/cp", 
	      "/bin/cp",
	      source,
          destination,
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

int split_string(char *original, char *filename){
    const char s[2] = ";";
    char *jenis, *nama, *usia;
    
    jenis = strtok(filename, s);
    nama = strtok(NULL, s);
    usia = strtok(NULL, s);
    
    char *path = malloc(64*sizeof(char));
    sprintf(path, "./petshop/%s", jenis);

	char *isi_ket = malloc(64*sizeof(char));
    isi_ket[0] = 0;
 	sprintf(isi_ket, "nama\t: %s\numur\t: %s\n\n", nama, usia);

	char *path2 = malloc(64*sizeof(char));
	sprintf(path2, "./petshop/%s/keterangan.txt", jenis);

	make_dir(path);
	make_ket(path2, isi_ket);

    char *namafile = malloc(64*sizeof(char));
    sprintf(namafile, "./petshop/%s/%s.jpg", jenis,nama);

    copy_file(original, namafile);
    //printf("%s\n", path);
    free(path);
	free(namafile);
	free(isi_ket);
	free(path2);
}

int read_file(){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("./petshop")) != NULL) {
	/* print all the files and directories within directory */
	while ((ent = readdir (dir)) != NULL) {
		int length = strlen(ent->d_name);

		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0){
			continue;	
		}
		
		char *namapath = malloc(64*sizeof(char));
		sprintf(namapath, "petshop/%s", ent->d_name);

		struct stat statbuf;
		stat(namapath, &statbuf);

		if (S_ISDIR(statbuf.st_mode)){ //https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
			//delete

			    sprintf(namapath, "petshop/%s", ent->d_name);
			del_folder(namapath);
		}
		else if(length >= 4 && strcmp(ent->d_name + length - 4, ".jpg") == 0){
			    char *namafile = malloc(64*sizeof(char));

			    sprintf(namafile, "%s", ent->d_name);
			    namafile[strlen(namafile)-4] = 0;
			
			    char *hewan = strtok(namafile, "_");
			    char *hewan2 = strtok(NULL, "_");
			    //printf("%s\n", hewan);
			    if(hewan2 != NULL){
				//printf("%s\n", hewan2);
				split_string(namapath, hewan2);
			    }
			    split_string(namapath, hewan);

			    del_file(namapath);
			free(namafile);
		}
		free(namapath);
	}
	closedir (dir);
	} else {
	//kalau directory nya gabisa dibuka
	perror ("");
	return EXIT_FAILURE;
	}
}

int main(){
	make_dir("petshop");
	unzip("pets.zip", "petshop/");
	read_file();
}
