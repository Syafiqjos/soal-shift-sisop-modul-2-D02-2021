#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

// NOMOR A (Make Directory)
void make_directory(char *path){
	execl("/bin/mkdir", 
	      "/bin/mkdir",
	      path,
	      NULL);
}

// NOMOR B (Download image)
void download_image(char *url, char *path){
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
// First Child Forked Process
void make_date_directory_and_download_photos(){
	char *filename = get_current_formatted_time();

	pid_t child_id = fork();

	// if child then..
	if (child_id == 0) {
		make_directory(filename);
	}

	char *url = "https://picsum.photos/";
	sprintf(url + strlen(url), "%d\0", (int)time(NULL) % 1000);
	strcat(url, "/200");

	printf("%s\n", url);

	run_timer_download_photos(5, url, filename);

	free(url);
	free(filename);
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
		char *path = strcat(path, strcat("/", get_current_formatted_time()));
		download_image(url, path);
		free(path);
		exit(0);
	}
}

// NOMOR A (Timer to check wheter 40 seconds has passed)
void run_timer(int delta_time, int mode){
	int current_delta_time = delta_time;

	time_t prev_time = time(NULL);
	time_t now_time = time(NULL);
	
	bool first = true;

	while (true){
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
	int current_delta_time = delta_time;

	time_t prev_time = time(NULL);
	time_t now_time = time(NULL);
	
	int count_many_times = 0;
	int how_many_times = 10;

	bool first = true;

	while (true){
		now_time = time(NULL);

		current_delta_time = (int) difftime(now_time, prev_time);
		if (current_delta_time >= delta_time || first){
			prev_time = now_time;
			call_timer_download_photo_update(url, path);

			if (count_many_times >= how_many_times){
				break;
			}
			count_many_times++;
			first = false;
		}
	}
}

int main(int argc, char *argv[]){

	// Jika tanpa argumen maka menjalankan mode pertama
	int mode = 0;

	// Jika ada argumen yang diberikan
	mode = get_mode(argc, argv);

	run_timer(2, mode);

	return 0;
}
