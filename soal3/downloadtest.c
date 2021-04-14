#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//https://stackoverflow.com/questions/33960385/how-to-download-a-file-from-http-using-c
//https://stackoverflow.com/questions/23010737/execute-a-bash-command-from-a-string-in-c-without-system

void download_image(char *url, char *path){
	execl("/usr/bin/wget", 
	      "/usr/bin/wget",
	      url,
	      "-O",
	      path,
	      NULL);
}

int main(void){
	//download_image("https://picsum.photos/200/200", "test.jpg");

	pid_t child_id = 0;

	int i = 0;
	for (;i < 4;i++){
		child_id = fork();
		if (child_id == 0){
			printf("BREAK CHILD -> %d\n", i);
			return 0;
		} else {
			printf("PARENT -> %d\n", i);
		}
	}

	printf("%d\n", child_id);

	if (child_id == 0){
		printf("CHILD\n");
	} else {
		printf("PARENT\n");
	}

	printf("ENDED\n");
}
