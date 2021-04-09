#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

char *isi_ket;

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
		  "-d", 
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
		execl("/usr/bin/rm", //rm = remove
	      "/usr/bin/rm",
		  path, //delete folder
	      NULL);
	}
    else{
        int status;
        waitpid(child_id, &status, 0);
    }
}

void make_ket(char *filename){
	FILE *file = fopen(filename, "w");

	if (file){
		fprintf(file, "%s\n", isi_ket);
		fclose(file);
	}

}

void copy_file(char *source, char *destination){
	pid_t child_id=fork ();
	if (child_id==0){
		//printf(" -> %s\n", path);
		execl("/usr/bin/cp", 
	      "/usr/bin/cp",
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

    make_dir(path);

    char *namafile = malloc(64*sizeof(char));
    sprintf(namafile, "./petshop/%s/%s.jpg", jenis,nama);

    sprintf(isi_ket+strlen(isi_ket), "nama\t: %s\numur\t: %s\n\n", nama, usia);

    copy_file(original, namafile);
    //printf("%s\n", path);
    free(path);
}

int read_file(){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
	/* print all the files and directories within directory */
	while ((ent = readdir (dir)) != NULL) {
		if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, "soal2") != 0 && 
			strcmp(ent->d_name, "soal2.c") != 0 && strcmp(ent->d_name, "pets.zip") != 0 && strcmp(ent->d_name, "keterangan.txt") != 0
            && strcmp(ent->d_name, "petshop") != 0){
			//printf ("%s\n", ent->d_name);
            char *namafile = malloc(64*sizeof(char));
            sprintf(namafile, "%s", ent->d_name);
            namafile[strlen(namafile)-4] = 0;
			
            char *hewan = strtok(namafile, "_");
            char *hewan2 = strtok(NULL, "_");
            //printf("%s\n", hewan);
            if(hewan2 != NULL){
                //printf("%s\n", hewan2);
                split_string(ent->d_name, hewan2);
            }
            split_string(ent->d_name, hewan);

            del_file(ent->d_name);
		}
	}
	closedir (dir);
	} else {
	//kalau directory nya gabisa dibuka
	perror ("");
	return EXIT_FAILURE;
	}
}

//rm -r */

int main(){
    isi_ket = malloc(10000*sizeof(char));
    isi_ket[0] = 0;
    unzip("pets.zip");
	del_folder("apex_cheats/");
	del_folder("musics/");
	del_folder("unimportant_files/");
    //printf("success\n");
	make_dir("petshop");
	read_file();
    make_ket("keterangan.txt");
    free(isi_ket);
}