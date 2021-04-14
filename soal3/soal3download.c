#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>

// https://stackoverflow.com/questions/33960385/how-to-download-a-file-from-http-using-c

int ReadHttpStatus(int sock){
    char c;
    char buff[1024]="",*ptr=buff+1;
    int bytes_received, status;
    printf("Begin Response ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("ReadHttpStatus");
            return 0;
        }

        if((ptr[-1]=='\r')  && (*ptr=='\n' )) break;
        ptr++;
    }
    *ptr=0;
    ptr=buff+1;

    sscanf(ptr,"%*s %d ", &status);

    printf("%s\n",ptr);
    printf("status=%d\n",status);
    printf("End Response ..\n");
    return (bytes_received>0)?status:0;

}

//the only filed that it parsed is 'Content-Length' 
int ParseHeader(int sock){
    char c;
    char buff[1024]="",*ptr=buff+4;
    int bytes_received, status;
    printf("Begin HEADER ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("Parse Header");
            return 0;
        }

        if(
            (ptr[-3]=='\r')  && (ptr[-2]=='\n' ) &&
            (ptr[-1]=='\r')  && (*ptr=='\n' )
        ) break;
        ptr++;
    }

    *ptr=0;
    ptr=buff+4;
    //printf("%s",ptr);

    if(bytes_received){
        ptr=strstr(ptr,"Content-Length:");
        if(ptr){
            sscanf(ptr,"%*s %d",&bytes_received);

        }else
            bytes_received=-1; //unknown size

       printf("Content-Length: %d\n",bytes_received);
    }
    printf("End HEADER ..\n");
    return  bytes_received ;

}

bool download_image(char *domain, char *path, char *save_to){
    int sock, bytes_received;  
    char send_data[1024],recv_data[1024], *p;
    struct sockaddr_in server_addr;
    struct hostent *he;


    he = gethostbyname(domain);
    if (he == NULL){
       herror("gethostbyname");
       return false;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0))== -1){
       perror("Socket");
       return false;
    }

    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(80);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(server_addr.sin_zero),8); 

    printf("Connecting ...\n");
    if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
       perror("Connect");
       return false;
    }

    printf("Sending data ...\n");
    printf("-> %s -> %s\n", path, domain);

    snprintf(send_data, sizeof(send_data), "GET /%s HTTP/1.1 Host: %s\0", path, domain);

    if(send(sock, send_data, strlen(send_data), 0) == -1){
        perror("send");
        return false;
    }
    printf("Data sent.\n");
    printf("Recieving data...\n\n");

    int contentlengh;

    if(ReadHttpStatus(sock) && (contentlengh=ParseHeader(sock))){

        int bytes=0;
        FILE* fd=fopen(save_to,"wb");
        printf("Saving data...\n\n");

        while(bytes_received = recv(sock, recv_data, 1024, 0)){
            if(bytes_received==-1){
                perror("receive");
                return false;
            }


            fwrite(recv_data,1,bytes_received,fd);
            bytes+=bytes_received;
            printf("Bytes received: %d from %d\n",bytes,contentlengh);
            if(bytes==contentlengh)
            break;
        }
        fclose(fd);
    }



    close(sock);
    printf("\n\nDone.\n\n");
    return true;
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

// NOMOR A (Make Date Directory)
void make_date_directory(){
	time_t current_time = time(NULL);
	struct tm* ptr = localtime(&current_time);
	
	char filename[32];
	
	strftime(filename, 32, "%Y-%m-%d_%H:%M:%S", ptr);
	mkdir(filename, 0777);

	printf("%s\n", filename);
}

// NOMOR A (Refresh Update every 40 seconds)
void call_timer_update(){
	make_date_directory();
}

// NOMOR A (Timer to check wheter 40 seconds has passed)
void run_timer(int delta_time, int mode){
	int current_delta_time = 0;

	time_t prev_time = time(NULL);
	time_t now_time = time(NULL);
	
	while (true){
		now_time = time(NULL);

		current_delta_time = (int) difftime(now_time, prev_time);
		if (current_delta_time >= delta_time){
			prev_time = now_time;
			call_timer_update();
		}
	}
}

int main(int argc, char *argv[]){
	//download_image("picsum.photos", "200/200", "image.png");
	download_image("raw.githubusercontent.com","arsitektur-jaringan-komputer/Modul-Sisop/master/2021/Modul2/img/showps.png", "image.png");
	// printf("%d %d %d %d\n", (int) getppid(), (int) getpid(), (int) fork(), argc);

	// Jika tanpa argumen maka menjalankan mode pertama
	int mode = 0;

	// Jika ada argumen yang diberikan
	mode = get_mode(argc, argv);

	run_timer(1, mode);

	return 0;
}

//https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/tree/master/2021/Modul2#daftar-isi
