#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"

RGBTRIPLE **allocate_matrix(RGBTRIPLE **image, RGBTRIPLE *image_lines, long int height, long int width){
  if(!(image = (RGBTRIPLE**)malloc(sizeof(RGBTRIPLE*) * height))){
    fprintf(stderr, "Not enough memory to allocate image!\n");
    return NULL;
  }

  if(!(image_lines = (RGBTRIPLE*)malloc(sizeof(RGBTRIPLE) * height * width))){
    fprintf(stderr, "Not enough memory to allocate image!\n");
    return NULL;
  }

  for(int i = 0; i < height; i++) image[i] = &image_lines[i * width];

  return image;
}
