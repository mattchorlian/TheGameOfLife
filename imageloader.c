/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Matthew Chorlian
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"


//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	Image *ptr = (Image*) malloc(sizeof(Image));
	int range;
	char form[20];
	FILE *fp = fopen(filename, "r");

	fscanf(fp,"%s %d %d %d\n ", form, &ptr->cols, &ptr->rows, &range); 
	
	Color ** pixel_arr = (Color **) calloc(ptr->rows, sizeof(Color*));
	for (int i = 0; i < ptr->rows; i++) {
		*(pixel_arr + i) = (Color *) calloc(ptr->cols, sizeof(Color));
	}
	
	for (int j = 0; j < ptr->rows; j++) {
		for (int k = 0; k < ptr->cols; k++) {
			Color* this_pixel = (Color*) malloc (sizeof(Color));
			fscanf(fp, "%d %d %d", &this_pixel->R, &this_pixel->G, &this_pixel->B);
			pixel_arr[j][k] = this_pixel;
		}
	}

	ptr->image = pixel_arr;


	fclose(fp);

	return ptr;

}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("%s\n", P3);
	printf(//columns and rows//)
	printf(%i, "255\n");
	

}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	if (*image) {
		free(image);
	}
}