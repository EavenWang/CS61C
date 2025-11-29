/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				EW
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
		Image * image = (Image*)malloc(sizeof(Image));
    FILE *fp = fopen(filename,"r");
    if(fp != NULL){
			char buff[10];
			fscanf(fp,"%s",buff);
			int rank;
			uint32_t rows;
			uint32_t cols;
			fscanf(fp,"%u %u",&cols,&rows);
			fscanf(fp,"%d",&rank);
			image->cols = cols;
			image->rows = rows;
			image->image = (Color**)malloc(sizeof(Color*) * rows);
			for(int i = 0;i < image->rows;i++){
				Color * color = (Color*)malloc(sizeof(Color) * cols);
				for(int j = 0;j < image->cols;j++){
					uint8_t r,g,b;
					fscanf(fp,"%hhu %hhu %hhu",&r,&g,&b);
					color[j].R = r;
					color[j].G = g;
					color[j].B = b;
				}
				image->image[i] = color;
			}
			fclose(fp);
			return image;		
    }
		fclose(fp);
		return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%u %u\n",image->cols,image->rows);
	printf("255\n");
	uint32_t cols = image->cols;
	uint32_t rows = image->rows;
	for(int i = 0;i < rows;i++){
		for(int j = 0;j < cols;j++){
			printf("%3d %3d %3d",image->image[i][j].R,image->image[i][j].G,image->image[i][j].B);
			if(j != cols - 1) printf("   ");
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	if(image == NULL) return;
	if(image->image != NULL){
		uint32_t rows = image->rows;
		for(int i = 0;i < rows;i++){
				free(image->image[i]);
				image->image[i] = NULL;
		}
	}
	free(image->image);
	image->image = NULL;
	free(image);
	image = NULL;
}
