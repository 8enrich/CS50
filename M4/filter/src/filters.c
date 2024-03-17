#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"
#include "../include/filters.h"
#include <math.h>

#define SIZE 3

void blur(long int height, long int width, RGBTRIPLE **image, RGBTRIPLE **new_image){
  float colors[SIZE] = {0, 0, 0};
  RGBTRIPLE pixel;
  RGBTRIPLE *new_pixel;
  for(long int i = 0; i < height; i++){
    for(long int j = 0, x = -(SIZE/2), y = -(SIZE/2); j < width; ){
      if(i + x >= 0 && j + y >= 0 && i + x < height && j + y < width){
        pixel = image[i + x][j + y];
        colors[0] += pixel.rgbtBlue;
        colors[1] += pixel.rgbtGreen;
        colors[2] += pixel.rgbtRed;
      }
      y++;
      if(y > SIZE/2){
        x++;
        y = -(SIZE/2);
      }
      if(x > SIZE/2){
        new_pixel = &(new_image[i][j]);
        apply_blur(new_pixel, colors);
        for(int k = 0; k < SIZE; k++) colors[k] = 0;
        j++;
        x = -(SIZE/2);
      }
    }
  }
}

void edges(long int height, long int width, RGBTRIPLE **image, RGBTRIPLE **new_image){
  float colors_x[SIZE] = {0, 0, 0};
  float colors_y[SIZE] = {0, 0, 0};
  int Gx[SIZE][SIZE] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
  int Gy[SIZE][SIZE] = {{-1,-2,-1},{0,0,0},{1,2,1}};
  RGBTRIPLE pixel;
  RGBTRIPLE *new_pixel;
  for(long int i = 0; i < height; i++){
    for(long int j = 0, x = -(SIZE/2), y = -(SIZE/2); j < width; ){
      if(i + x >= 0 && j + y >= 0 && i + x < height && j + y < width){
        pixel = image[i + x][j + y];
        colors_x[0] += pixel.rgbtBlue * Gx[x + 1][y + 1];
        colors_y[0] += pixel.rgbtBlue * Gy[x + 1][y + 1];
        colors_x[1] += pixel.rgbtGreen * Gx[x + 1][y + 1];
        colors_y[1] += pixel.rgbtGreen * Gy[x + 1][y + 1];
        colors_x[2] += pixel.rgbtRed * Gx[x + 1][y + 1];
        colors_y[2] += pixel.rgbtRed * Gy[x + 1][y + 1];
      }
      y++;
      if(y > SIZE/2){
        x++;
        y = -(SIZE/2);
      }
      if(x > SIZE/2){
        new_pixel = &(new_image[i][j]);
        apply_edges(new_pixel, colors_x, colors_y);
        for(int k = 0; k < SIZE; k++){
          colors_x[k] = 0;
          colors_y[k] = 0;
        }
        j++;
        x = -(SIZE/2);
      }
    }
  }
}
void reflect(long int height, long int width, RGBTRIPLE **image, RGBTRIPLE **new_image){
  for(long int i = 0; i < height; i++)
    for(long int j = 0; j < width; j++)
      new_image[i][j] = image[i][width - j - 1];
}

void grayscale(long int height, long int width, RGBTRIPLE **image, RGBTRIPLE **new_image){
  float sum;
  RGBTRIPLE pixel;
  RGBTRIPLE *new_pixel;
  for(long int i = 0; i < height; i++){
    sum = 0;
    for(long int j = 0; j < width; j++){
      pixel = image[i][j];
      new_pixel = &(new_image[i][j]);
      sum = pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed;
      sum /= SIZE;
      sum = (sum - (int)sum > .5)?(int)sum + 1:(int)sum;
      (new_pixel->rgbtBlue) = sum;
      (new_pixel->rgbtGreen) = sum;
      (new_pixel->rgbtRed) = sum;
    }
  }
}

void sepia(long int height, long int width, RGBTRIPLE **image, RGBTRIPLE **new_image){
  float colors[SIZE] = {0,0,0};
  RGBTRIPLE pixel;
  RGBTRIPLE *new_pixel;
  for(long int i = 0; i < height; i++){
    for(long int j = 0; j < width; j++){
      pixel = image[i][j];
      new_pixel = &(new_image[i][j]);
      colors[0] = .272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue;
      colors[1] = .349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue;
      colors[2] = .393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue;
      for(int k = 0; k < SIZE; k++){
        colors[k] = (colors[k] - (int)colors[k] > .5)?(int)colors[k] + 1:(int)colors[k];
        if(colors[k] > 255) colors[k] = 255;
      }
      (new_pixel->rgbtBlue) = colors[0];
      (new_pixel->rgbtGreen) = colors[1];
      (new_pixel->rgbtRed) = colors[2];
      for(int k = 0; k < SIZE; k++) colors[k] = 0;
    }
  }
}

void apply_blur(RGBTRIPLE *new_pixel, float *colors){
  for(int i = 0; i < SIZE; i++){
    colors[i] /= (SIZE * SIZE);
    colors[i] = (colors[i] - (int)colors[i] > .5)?(int)colors[i] + 1:(int)colors[i];
  }
  (new_pixel->rgbtBlue) = colors[0];
  (new_pixel->rgbtGreen) = colors[1];
  (new_pixel->rgbtRed) = colors[2];
}

void apply_edges(RGBTRIPLE *new_pixel,float *colors_x, float *colors_y){
  float values[SIZE];
  for(int i = 0; i < SIZE; i++){
    values[i] = sqrt((colors_x[i] * colors_x[i]) + (colors_y[i] * colors_y[i]));
    values[i] = (values[i] - (int)values[i] > .5)?(int)values[i] + 1:(int)values[i];
    if(values[i] > 255) values[i] = 255;
  }
  (new_pixel->rgbtBlue) = values[0];
  (new_pixel->rgbtGreen) = values[1];
  (new_pixel->rgbtRed) = values[2];
}
