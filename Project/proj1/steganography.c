/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
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
	Color * color = (Color*)malloc(sizeof(Color));
	color->R = image->image[row][col].R;
	color->G = image->image[row][col].G;
	color->B = image->image[row][col].B;
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image * ans = (Image*)malloc(sizeof(Image));
	ans->cols = image->cols;
	ans->rows = image->rows;
	ans->image = (Color**)malloc(sizeof(Color*) * image->rows);
	for(int i = 0;i < image->rows;i++){
		Color * color = (Color*)malloc(sizeof(Color) * image->cols);
		ans->image[i] = color;
	}

	for(int i = 0;i < image->rows;i++){
		for(int j = 0;j < image->cols;j++){
			uint8_t b = image->image[i][j].B;
			if((b & 0x1) == 0){
				ans->image[i][j].B = 0;
				ans->image[i][j].R = 0;
				ans->image[i][j].G = 0;
			}else{
				ans->image[i][j].B = 255;
				ans->image[i][j].R = 255;
				ans->image[i][j].G = 255;
			}
		}
	}
	return ans;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc < 2){
		return -1;
	}

	FILE * fp = fopen(argv[1],"r");
	if(fp == NULL) return -1;

	Image * image = readData(argv[1]);
	if(image == NULL) return -1;

  Image * out = steganography(image);
	writeData(out);
	freeImage(image);
	freeImage(out);
	fclose(fp);
	return 0;

}

