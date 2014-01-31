/*
 ============================================================================
 Name        : Demo02-KeyboardInput.c
 Author      : Nicholas Outram
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

char strName[65];
float fWeight;
float fHeight;

int main(void) {
	puts("Enter your name"); /* prints !!!Hello World!!! */
	scanf("%64s", strName);

	puts("Enter your weight in Kg");
	scanf("%f", &fWeight);

	puts("Enter your height in m");
	scanf("%f", &fHeight);

	float fBMI = fWeight / (fHeight*fHeight);
	printf("Hello %s, your approximate BMI = %4.1f\n", strName, fBMI);

	return EXIT_SUCCESS;
}
