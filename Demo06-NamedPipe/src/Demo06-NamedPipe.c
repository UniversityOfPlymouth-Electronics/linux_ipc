/*
 ============================================================================
 Name        : Demo06-NamedPipe.c
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

//
// Demonstrates blocking using UNIX open, read, write, close
//

int main(void) {
	puts("Client");
	char* strMessage[] = {"Welcome", "to", "the", "module.", "This", "will", "now", "STOP"};

	//Open fifo for write
	int fd = open("/tmp/demo6_fifo", O_WRONLY);
	if (fd ==  -1) {
		perror("Cannot open fifo");
		return EXIT_FAILURE;
	}

	//Write each string in turn
	for (unsigned int n=0; n<8; n++) {
		char L = (char)strlen(strMessage[n]);
		write(fd, &L, 1);									//Send string length
		write(fd, strMessage[n], strlen(strMessage[n])); 	//Send string characters
	}

	//Tidy
	close(fd);
	return EXIT_SUCCESS;
}
