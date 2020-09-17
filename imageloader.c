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
	FILE *fp = fopen(filename, "r");
	Image *ptr = (struct Image*) malloc(sizeof(Image));
	int range;
	char format[20];

	fscanf(fp, "%s %d %d %d\n", format, &ptr->cols, &ptr->rows, &range);

	int product = ((ptr->cols) * (ptr->rows));
	Color** pixel_arr = (Color**) malloc(product * sizeof(Color*));

	for (int i = 0; i < ptr->cols*ptr->rows; i++) {
		Color* pixel = (Color*) malloc(sizeof(Color*));
		fscanf(fp, "%d %d %d\n" , &pixel->R, &pixel->G, &pixel->B);
		pixel_arr[i] = pixel;
	}

	ptr->image = pixel_arr;

	fclose(fp);

	return ptr;

}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("%d\n", 255);	


	int i = 0;
	for (int r = 0; r < image->rows; r++) {
		for (int c = 0; c < image->cols; c++) {
			if (c == image->cols - 1) {
				printf("%3d %3d %3d", image->image[i]->R, image->image[i]->G, image->image[i]->B);
			} else {
				printf("%3d %3d %3d   ", image->image[i]->R, image->image[i]->G, image->image[i]->B);
			}
			
			
			i++;
		}
		printf("\n");
		
	}
}

//Frees an image
void freeImage(Image *image)
{
	if (image) {
		int i = 0;
		while (i < image->cols*image->rows) {
			free(image->image[i]);
			i++;
		}
		free(image->image);
		free(image);
	}
	
}