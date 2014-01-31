/*
 ============================================================================
 Name        : Demo03-PlaySound.c
 Author      : Nicholas Outram
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>

// ******************************************
// 					CONSTANTS
// ******************************************

//Sample type
typedef unsigned char SAMPLE;

//Sampling rate (samples per second) - recommend 16000 or higher
#define SAMPLING_RATE 8000

//Duration in seconds
#define PLAY_DURATION 5

//Size of buffer
#define BUFFER_SIZE_IN_BYTES (SAMPLING_RATE*PLAY_DURATION*sizeof(SAMPLE))

// **************************************************
// 					     MAIN CODE
// **************************************************

int main(int argc, char** argv)
{
	//Record some data samples
	int iBytesWritten=0;

	//Create sample buffer
	SAMPLE buffer[BUFFER_SIZE_IN_BYTES];

	//Frequency sweep
	double f = 440.0;				//Start with middle A 440Hz
	double T = 1.0/SAMPLING_RATE;	//Sampling interval
	for (unsigned n=0; n<BUFFER_SIZE_IN_BYTES; n++) {
		double y = 120.0 * cos(2*3.1415926*n*f*T);
		buffer[n] = 127 + round(y);
		f*= 1.0001;	//Purposely alias over 4K to get the effect I want ;o)
	}

	//**************************************
	//Play audio using the aplay application
	//**************************************
	FILE* outputStream=NULL;		//Stream that represents the process pipe for read
	int fid;						//Corresponding fileid

	//Create child process and process pipe
	outputStream = popen("aplay -t raw -r 8000 -q","w");		//Open for write
	fid = fileno(outputStream);									//Get FileID for the stream
	iBytesWritten = write(fid, buffer, BUFFER_SIZE_IN_BYTES);	//Write data
	printf("Written %d bytes out of %d\n", iBytesWritten, BUFFER_SIZE_IN_BYTES);

	//Close pipes and unblock child process
   fid = pclose(outputStream);

   return (EXIT_SUCCESS);
}



