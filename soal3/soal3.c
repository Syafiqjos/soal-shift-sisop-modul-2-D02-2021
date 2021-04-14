#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

void make_killer_exec(int);
void append_killer_exec(int);
void make_zip_file(char *);
void make_zip(char *, char *);
void make_status_file(char *);
void make_directory(char *);
void download_image(char *, char *);
char *caesar_cypher(char *, int);

char *get_current_formatted_time();
void make_date_directory_and_download_photos(int);
void call_timer_update(int);
void call_timer_download_photo_update(char *, char *);

void run_timer(int, int);
void run_timer_download_photos(int, char *, char *);

// NOMOR E (Create / Overwrite new Killer file)
void make_killer_exec(int mode){
	printf("Generating Killer..\n");

	FILE *killer_file = fopen("./Killer.sh", "w");
	if (mode == 1){
		// Argument -x
		fprintf(killer_file, "kill %d\n", getpid());
	} else {
		// edit this
		// Argument -z or else
		fprintf(killer_file, "kill %d\n", getpid());
	}
	fclose(killer_file);
}

// NOMOR E (Append child process to Killer file)
void append_killer_exec(int mode){
	if (mode != 1) {
		printf("Append more process to kill..\n");
		FILE *killer_file = fopen("./Killer.sh", "a");
		fprintf(killer_file, "kill %d\n", getpid());

		fclose(killer_file);
	}
}

// NOMOR C (Compress Directory into Zip File)
void make_zip_file(char *filename){
	char *zip_filename = malloc(64 * sizeof(char));
	char *zip_path = malloc(64 * sizeof(char));

	sprintf(zip_filename, "%s.zip" ,filename);
	sprintf(zip_path, "./%s" ,filename);

	make_zip(zip_filename, zip_path);

	free(zip_filename);
	free(zip_path);
}

// NOMOR C (Create Status File with Caesar Cypher)
void make_status_file(char *filename){
	char *status_path = malloc(64 * sizeof(char));
	char *status_write = malloc(64 * sizeof(char));
	
	char* caesar_data = caesar_cypher("Download Success", 5);

	sprintf(status_path, "%s/status.txt", filename);
	sprintf(status_write, "%s", caesar_data);

	FILE *status_file = fopen(status_path, "w");

	if (status_file){
		fprintf(status_file, "%s\n", status_write);
		fclose(status_file);
	}

	free(status_path);
	free(status_write);
	free(caesar_data);
}

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
	char *dest;
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

// Get Current Time Formatted
char *get_current_formatted_time(){
	time_t current_time = time(NULL);
	struct tm* ptr = localtime(&current_time);
	
	char *filename = malloc(32 * sizeof(char));
	
	strftime(filename, 32, "%Y-%m-%d_%H:%M:%S", ptr);
	return filename;
}

// NOMOR A (Make Date Directory and Download Photos)
// First Level Child Forked Process
void make_date_directory_and_download_photos(int mode){
	append_killer_exec(mode);

	char *filename = get_current_formatted_time();
	printf("%s\n", filename);

	pid_t child_id = fork();

	// if child then..
	if (child_id == 0) {
		make_directory(filename);
	}

	char *url = malloc(64 * sizeof(char));

	int dt = 50 + (int)time(NULL) % 1000;
	sprintf(url, "https://picsum.photos/%d/%d", dt, dt);

	printf("DOWNLOAD PHOTOS BATCH HAS STARTED\n");
	
	run_timer_download_photos(5, url, filename);
	
	printf("DOWNLOAD PHOTOS BATCH HAS ENDED\n");

	make_status_file(filename);
	make_zip_file(filename);

	free(url);
	free(filename);

	exit(0);
}

// NOMOR A (Refresh Update every 40 seconds)
void call_timer_update(int mode){
	pid_t child_id = fork();
	// if child then..
	if (child_id == 0) {
		make_date_directory_and_download_photos(mode);
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
			call_timer_update(mode);
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
	int how_many_times = 10;

	bool first = true;

	bool is_running = true;

	while (is_running){
		now_time = time(NULL);

		current_delta_time = (int) difftime(now_time, prev_time);
		if (current_delta_time >= delta_time || first){
			prev_time = now_time;

			if (count_many_times > how_many_times){
				is_running = false;
				break;
			}

			count_many_times++;
			first = false;

			call_timer_download_photo_update(url, path);
		}
	}
}

int main(int argc, char *argv[]){
	// Jika tanpa argumen maka menjalankan mode pertama
	int mode = 0;

	// Jika ada argumen yang diberikan
	mode = get_mode(argc, argv);

	make_killer_exec(mode);

	run_timer(40, mode);

	return 0;
}
