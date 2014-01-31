/*
 ============================================================================
 Name        : Demo06-NamedPipeServer.c
 Author      : Nicholas Outram
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(void) {
	puts("Server - listening");

	//Create fifo
	int code = mkfifo("/tmp/demo6_fifo", 0666);
	if (code == -1) {
		perror("mkfifo returned an error - file may already exist");
	}

	//Open read end
	int fd = open("/tmp/demo6_fifo", O_RDONLY);
	if (fd == -1) {
		perror("Cannot open FIFO for read");
		return EXIT_FAILURE;
	}
	puts("FIFO OPEN");

	//Read string (upto 255 characters)
	char stringBuffer[256];			//String buffer
	memset(stringBuffer, 0, 256);   //Fill with zeros

	/*
	while (strcmp(stringBuffer, "STOP") != 0) {
		char L;
		read(fd, &L, 1);							//Get string length
		read(fd, stringBuffer, L);					//Read string characters
		stringBuffer[L] = 0;						//Zero terminator
		printf("Server received: %s\n", stringBuffer);
	}
	*/
	int res;
	char Len;
	while(1) {
		res = read(fd, &Len, 1);
		if (res == 0) {
			break;
		}
		read(fd, stringBuffer, Len);					//Read string characters
		stringBuffer[(int)Len] = 0;						//Zero terminator
		printf("Server received: %s\n", stringBuffer);
	}

	puts("EOF found");

	//Tidy up
	close(fd);
	puts("FIFO Closed");

	return EXIT_SUCCESS;
}
