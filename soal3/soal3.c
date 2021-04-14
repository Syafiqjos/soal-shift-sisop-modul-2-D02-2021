#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

// NOMOR A (Make Directory)
void make_directory(char *path){
	printf("Creating Directory -> %s\n", path);
	execl("/bin/mkdir", 
	      "/bin/mkdir",
	      path,
	      NULL);
}

// NOMOR C (Make Zip)
void make_zip(char *filename, char *path){
	printf("Making Zip File -> %s from %s\n", filename, path);
	execl("/usr/bin/zip", 
	      "/usr/bin/zip",
	      "-rm",
	      filename,
	      path,
	      NULL);
}

// NOMOR B (Download image)
// Second Level Child Forked Process
void download_image(char *url, char *path){
	printf("Downloading -> %s into -> %s\n", url, path);
	execl("/usr/bin/wget", 
	      "/usr/bin/wget",
	      url,
	      "-O",
	      path,
	      NULL);
}

// NOMOR C (Caesar Cypher)
char *caesar_cypher(char *src, int shift){
	int len = strlen(src);
	printf("%d\n", len);
	char *dest = 0;
	int i = 0;

	dest = malloc(sizeof(char) * len);

	for (; i < len; i++){
		if (src[i] >= 'A' && src[i] <= 'Z'){
			dest[i] = 'A' + (src[i] - 'A' + shift) % 26;
		} else if (src[i] >= 'a' && src[i] <= 'z'){
			dest[i] = 'a' + (src[i] - 'a' + shift) % 26;
		} else {
			dest[i] = src[i];
		}
	}

	return dest;
}

// NOMOR E (What mode the program should use ?)
int get_mode(int argc, char *argv[]){
	// Jika tanpa argumen maka menjalankan mode pertama
	if (argc > 1) {
		if (strcmp(argv[1], "-z") == 0){
			// Menjalankan mode force stop process
			return 0;
		} else if (strcmp(argv[1], "-x") == 0){
			// Menjalankan mode soft stop process
			return 1;
		}
	}
	return 0;
}

char *get_current_formatted_time(){
	time_t current_time = time(NULL);
	struct tm* ptr = localtime(&current_time);
	
	char *filename = malloc(32 * sizeof(char));
	
	strftime(filename, 32, "%Y-%m-%d_%H:%M:%S", ptr);
	return filename;
}

// NOMOR A (Make Date Directory and Download Photos)
// First Level Child Forked Process
void make_date_directory_and_download_photos(){
	char *filename = get_current_formatted_time();
	printf("%s\n", filename);

	pid_t child_id = fork();

	// if child then..
	if (child_id == 0) {
		make_directory(filename);
	}

	char *url = malloc(64 * sizeof(char));

	int dt = (int)time(NULL) % 1000;
	sprintf(url, "https://picsum.photos/%d/50", dt);

	printf("TIMER START\n");
	run_timer_download_photos(5, url, filename);
	printf("TIMER END\n");

	char *status_path = malloc(64 * sizeof(char));
	char *status_write = malloc(64 * sizeof(char));
	
	sprintf(status_path, "%s/status.txt", filename);
	sprintf(status_write, "%s\n", caesar_cypher("Download Success", 5));

	// TODO : write file status.txt

	char *zip_filename = malloc(64 * sizeof(char));
	char *zip_path = malloc(64 * sizeof(char));

	sprintf(zip_filename, "%s.zip" ,filename);
	sprintf(zip_path, "./%s" ,filename);

	make_zip(zip_filename, zip_path);

	free(url);
	free(filename);
	free(status_path);
	free(status_write);
	free(zip_filename);
	free(zip_path);

	exit(0);
}

// NOMOR A (Refresh Update every 40 seconds)
void call_timer_update(){
	pid_t child_id = fork();
	// if child then..
	if (child_id == 0) {
		make_date_directory_and_download_photos();
		exit(0);
	}
}

// NOMOR B (Refresh Update every 5 seconds)
void call_timer_download_photo_update(char *url, char *path){
	pid_t child_id = fork();
	// if child then..
	if (child_id == 0) {
		char *p = malloc(64 * sizeof(char));
		sprintf(p, "%s/%s.jpg", path, get_current_formatted_time());
		download_image(url, p);
		free(path);
		exit(0);
	}
}

// NOMOR A (Timer to check wheter 40 seconds has passed)
void run_timer(int delta_time, int mode){
	int current_delta_time = 0;

	time_t prev_time = time(NULL);
	time_t now_time = time(NULL);
	
	bool first = true;

	bool is_running = true;

	while (is_running){
		now_time = time(NULL);

		current_delta_time = (int) difftime(now_time, prev_time);
		if (current_delta_time >= delta_time || first){
			prev_time = now_time;
			call_timer_update();
			first = false;
		}
	}
}

// NOMOR B (Timer to check wheter 5 seconds has passed)
void run_timer_download_photos(int delta_time, char *url, char *path){
	int current_delta_time = 0;

	time_t prev_time = time(NULL);
	time_t now_time = time(NULL);
	
	int count_many_times = 0;
	int how_many_times = 3;

	bool first = true;

	bool is_running = true;

	while (is_running){
		now_time = time(NULL);

		current_delta_time = (int) difftime(now_time, prev_time);
		if (current_delta_time >= delta_time || first){
			prev_time = now_time;
			call_timer_download_photo_update(url, path);

			count_many_times++;
			first = false;

			if (count_many_times >= how_many_times){
				is_running = false;
			}
		}
	}
}

int main(int argc, char *argv[]){
	// Jika tanpa argumen maka menjalankan mode pertama
	int mode = 0;

	// Jika ada argumen yang diberikan
	mode = get_mode(argc, argv);

	run_timer(40, mode);

	return 0;
}
