#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bmp.h"
#include "../include/filters.h"
#include "../include/verification.h"
#include "../include/image.h"

#define SIZE 5

int main(int argc, char *argv[]){

  int filter, value;

  value = verification(argc, argv, &filter);

  if(value) exit(value);

  char *infile_name = argv[2];
  char *directory = "../filtered/";
  char *outfile_name = NULL;

  int n = strlen(directory);

  if(!(outfile_name = (char*)malloc(sizeof(char) * n * strlen(argv[3])))){
    puts("Not enough memory!");
    exit(5);
  }

  for(int i = 0; i < n; i++) outfile_name[i] = directory[i];

  strcat(outfile_name, argv[3]);

  FILE *infile;
  FILE *outfile;

  if(!(infile = fopen(infile_name, "r"))){
    printf("%s can't be open!\n", infile_name);
    fclose(infile);
    exit(6);
  }
  if(!(outfile = fopen(outfile_name, "w"))){
    printf("%s can't be open!\n", outfile_name);
    fclose(outfile);
    exit(7);
  }

  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, infile);
  BITMAPINFOHEADER bi;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, infile);

  if(bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
    bi.biBitCount != 24 || bi.biCompression != 0){
    fclose(outfile);
    fclose(infile);
    fprintf(stderr, "Unsupported file format.\n");
    exit(8);
  }

  long int height = abs(bi.biHeight);
  long int width = bi.biWidth;

  RGBTRIPLE **image = NULL;
  RGBTRIPLE *image_lines = NULL;

  image = allocate_matrix(image, image_lines, height, width);

  if(!image){
    fclose(outfile);
    fclose(infile);
    exit(9);
  }

  RGBTRIPLE **new_image = NULL;
  RGBTRIPLE *new_image_lines = NULL;

  new_image = allocate_matrix(new_image, new_image_lines, height, width);

  if(!new_image){
    fclose(outfile);
    fclose(infile);
    exit(10);
  }

  for(int i = 0; i < height; i++){
    fread(image[i], sizeof(RGBTRIPLE), width, infile);
  }

  void (*Fp[SIZE])(long int,long int,RGBTRIPLE**,RGBTRIPLE**) = {blur, edges, reflect, grayscale, sepia};

  Fp[filter](height, width, image, new_image);

  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outfile);
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outfile);

  for(int i = 0; i < height; i++){
    fwrite(new_image[i], sizeof(RGBTRIPLE), width, outfile);
  }

  fclose(infile);
  fclose(outfile);
  free(image);
  free(image_lines);
  free(new_image);
  free(new_image_lines);
  free(outfile_name);

  return 0;
}
