/*
 ============================================================================
 Name        : Demo05-GetKernerVersion.c
 Author      : Nicholas Outram
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *inputStream;

	//This time, I am going to use standard C functions
	inputStream = popen("uname -a", "r");
	if (!inputStream) {
		perror("Sorry - cannot open uname");
		exit(-1);
	}

	//Read third string
	char strBuffer[65];
	fscanf(inputStream, "%*s %*s %64s", strBuffer);	//Ignore first two string using '*'
	pclose(inputStream);

	//Display results
	printf("Kernel version: %s\n", strBuffer);
	return EXIT_SUCCESS;
}
