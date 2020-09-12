/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				Matthew Chorlian
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	int index = (image->cols * (row - 1)) + col - 1;
	Color* pixel = image->image[index];
	int blue = pixel->B;

	if ((blue & 1) == 1) {
		Color* changed = (Color*) malloc(sizeof(Color));
		if (!changed) {
			exit(-1);
		}
		changed->R = 255;
		changed->G = 255;
		changed->B = 255;
		return changed;
	} else {
		Color* changed = (Color*) malloc(sizeof(Color));
		if (!changed) {
			exit(-1);
		}
		changed->R = 0;
		changed->G = 0;
		changed->B = 0;
		return changed;
	}

}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image* secret = (Image*) malloc(sizeof(Image));
	if (!secret) {
		exit(-1);
	}
	Color** secret_arr = (Color**) malloc(image->rows * image->cols * sizeof(Color*));
	if (!secret_arr) {
		exit(-1);
	}

	int index = 0;
	for (int i = 1; i < image->rows + 1; i++) {
		for (int j = 1; j < image->cols + 1; j++) {
			Color* new_pixel;
			new_pixel = evaluateOnePixel(image, i, j);
			secret_arr[index] = new_pixel;
			index++;
		}
	}

	secret->cols = image->cols;
	secret->rows = image->rows;
	secret->image = secret_arr;

	freeImage(image);
		// neeed to free the malloc of Image* secret
	
	

	
	return secret;
}

/*
Loads a .ppm from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	int count = 0;
	while(argv[count]) {
		count++;
	} 

	if (!(count == argc)) {
		return -1;
	}

	Image* img = readData(argv[1]);

	Image* secret = steganography(img);

	writeData(secret);

	freeImage(secret);


	return 0;
}
