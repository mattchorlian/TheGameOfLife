/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Matthew Chorlian
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.




//returns true index in Image->image of pixel at row, col//
int wrapper(Image *image, int row, int col) {

	if ((row > 0 && row <= image->rows) && (col > 0 && col <= image->cols)) {
		return (image->cols * (row - 1)) + col - 1;
	}
	if (row > image->rows) {
		if (col > image->cols) {
			return 0;
		} else if (col <= 0) {
			return image->cols - 1;
		} else { // cols are in not out of boundary
			return col - 1;
		}
	} else if (row <= 0) {
		if (col > image->cols) {
			return (image->cols * (image->rows - 1));
		} else if (col <= 0) {
			return (image->cols * (image->rows - 1)) + image->cols - 1;
		} else { //col are in boundary
			return (image->cols * (image->rows - 1)) + col - 1;
		}
	} else {
		if (col <= 0) {
			return (image->cols * (row - 1)) + image->cols - 1;
		} else { //cols > image->cols
			return (image->cols * (row - 1));
		}
	}
}



Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	Color** neighbors = (Color**) malloc(8 * sizeof(Color*));
	int index = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!(i == 0 && j == 0)) {

				Color* cell;

				int pos = wrapper(image, row + i, col + j);

				cell = image->image[pos];

				neighbors[index] = cell;

				index ++;
			}
		}

	}


	// make space for new color to be returned
	Color* final = (Color*) malloc(sizeof(Color));
	final->R = 0;
	final->G = 0;
	final->B = 0;
	int array_index = (image->cols * (row - 1)) + col - 1;
	Color* this_pixel = image->image[array_index];


	//red bits and assign red value to new color
	int count = 0;
	for (int shiftred = 0; shiftred < 8; shiftred++) {
		for (int i = 0; i < 8; i++) {
			if ((((neighbors[i]->R) >> shiftred) & 1) == 1) {
				count ++;
			}
		}
		if ((((this_pixel->R) >> shiftred) & 1) == 1) { //this bit is ALIVE
			if ((rule >> (9 + count) & 1) == 1) {
				final->R += (1 << shiftred);
			}
		} else { //this bit is dead
			if (((rule >> count) & 1) == 1) {
				final->R += (1 << shiftred); //set bit of R to be 1
			}
		}
		count = 0;
	}
	

	//green bits 

	count = 0;
	for (int shiftg = 0; shiftg < 8; shiftg++) {
		for (int i = 0; i < 8; i++) {
			if ((((neighbors[i]->G) >> shiftg) & 1) == 1) {
				count ++;
			}
		}
		if ((((this_pixel->G) >> shiftg) & 1)== 1) { //this bit is ALIVE
			if (((rule >> (9 + count)) & 1) == 1) {
				final->G += (1 << shiftg);
			}
		} else { //this bit is dead
			if (((rule >> count) & 1) == 1) {
				final->G += (1 << shiftg); //set bit of R to be 1
			}
		}
		count = 0;
	}


	//blue bits
	count = 0;
	for (int shiftb = 0; shiftb < 8; shiftb++) {
		for (int i = 0; i < 8; i++) {
			if ((((neighbors[i]->B) >> shiftb) & 1) == 1) {
				count ++;
			}
		}
		if ((((this_pixel->B) >> shiftb) & 1) == 1) { //this bit is ALIVE
			if (((rule >> (9 + count)) & 1 )== 1) {
				final->B += (1 << shiftb);
			}
		} else { //this bit is dead
			if (((rule >> count) & 1 )== 1) {
				final->B += (1 << shiftb); //set bit of R to be 1
			}
		}
		count = 0;
	}

	free(neighbors);


	return final;
}



//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image* final = (Image*) malloc(sizeof(Image));
	if (!final) {
		exit(-1);
	}
	Color** new_arr = (Color**) malloc(image->rows*image->cols*sizeof(Color*));
	if (!new_arr) {
		exit(-1);
	}

	int index = 0;
	for (int i = 1; i < image->rows + 1; i++) {
		for (int j = 1; j < image->cols + 1; j++) {
			Color* new_cell;
			new_cell = evaluateOneCell(image, i, j, rule);
			new_arr[index] = new_cell;
			index++;
		}
	}

	final->rows = image->rows;
	final->cols = image->cols;
	final->image = new_arr;

	freeImage(image);

	return final;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	int count = 0;
	while(argv[count]) {
		count++;
	} 

	if (!(count == argc)) {
		/*printf("usage: ./gameOfLife filename rule \n
  				  filename is an ASCII PPM file (type P3) with maximum value 255. \n
   					 rule is a hex number beginning with 0x; Life is 0x1808.")*/
		return -1;
	}

	Image* img = readData(argv[1]);


	char* eptr;
	int rule = strtol(argv[2], &eptr ,16);

	Image* result = life(img, rule);

	writeData(result);

	freeImage(result);


	return 0;
}
