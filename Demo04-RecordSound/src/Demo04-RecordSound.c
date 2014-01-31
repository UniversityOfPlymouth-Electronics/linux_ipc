/*
 ============================================================================
 Name        : Demo04-RecordSound.c
 Author      : Nicholas Outram
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <math.h>

/*
Available formats for VMWare Audio:
- U8
- S16_LE
- S16_BE
- S32_LE
- S32_BE
- FLOAT_LE
- FLOAT_BE
- MU_LAW
- A_LAW
*/

// ******************************************
// 					CONSTANTS
// ******************************************
typedef int16_t SAMPLE;

//Sampling rate (samples per second) - recommend 16000 or higher
#define SAMPLING_RATE 16000

//Duration in seconds
#define PLAY_DURATION 2

//Size of buffer
#define BUFFER_SIZE_IN_BYTES (SAMPLING_RATE*PLAY_DURATION*sizeof(SAMPLE))


// **************************************************
// 					 GLOBAL VARIABLES
// **************************************************

//Buffer to hold the data
char buf[BUFFER_SIZE_IN_BYTES];

//Streams that represent the process pipes
FILE* outputStream=NULL;
FILE* inputStream=NULL;

//Corresponding fileid
int fidIn;
int fidOut;

//Bytes read/written
int iBytesRead=0;
int iBytesWritten = 0;

// **************************************************
// 					     MAIN CODE
// **************************************************

int main(int argc, char** argv)
{

	//Wait for a key press
	puts("Press return to record some data");
	getchar();

	//Record samples
	char strCommand[64];
	sprintf(strCommand, "arecord -q -c 1 -t raw -f S16_LE -r %u -D plughw:0,0", SAMPLING_RATE);
	printf("Issuing command %s\n", strCommand);
	inputStream = popen(strCommand,"r");
	if (inputStream == NULL) {
		perror("Cannot open child process for record");
		exit(1);
	}
	fidIn = fileno(inputStream);

	char* pBuffer = buf;
	int iSamplesRead;
	iBytesRead = 0;
	while (iBytesRead < BUFFER_SIZE_IN_BYTES) {
		//Grab 1000 samples
		iSamplesRead = read(fidIn, pBuffer, BUFFER_SIZE_IN_BYTES);			//4000 is max for one hit
		if (iSamplesRead > 0) {
			iBytesRead += iSamplesRead;
			pBuffer += iSamplesRead;
			printf("%d ", iSamplesRead);
		} else {
			break;
		}
	}
	pclose(inputStream);

	printf("Address of buffer: %p\nAddress of pointer: %p\nDelta = %d\n", buf, pBuffer, (pBuffer-buf));

	//Wait for a key press
	puts("Press return to play back the data");
	getchar();

	//Open process pipe for read only (pipe stream is uni-direction on Linux)
	sprintf(strCommand, "aplay -q -c 1 -t raw -f S16_LE -r %u", SAMPLING_RATE);
	printf("Issuing command %s\n", strCommand);
	outputStream = popen(strCommand,"w");
	if (outputStream == NULL) {
		perror("Cannot open child process");
		exit(1);
	}
   fidOut = fileno(outputStream);

   //Play audio
   iBytesWritten = 0;
   pBuffer = buf;
   int iSamplesWritten;
   fflush(outputStream);
   while (iBytesWritten < BUFFER_SIZE_IN_BYTES) {
	   iSamplesWritten = write(fidOut, pBuffer, BUFFER_SIZE_IN_BYTES);
	   if (iSamplesWritten > 0) {
		   iBytesWritten += iSamplesWritten;
		   pBuffer += iSamplesWritten;
		   printf("%d ", iSamplesWritten);
	   } else {
		   break;
	   }
   }
	//Close pipes and unblock child process
    pclose(outputStream);
    printf("Address of buffer: %p\nAddress of pointer: %p\nDelta = %d\n", buf, pBuffer, (pBuffer-buf));

   return (EXIT_SUCCESS);
}

