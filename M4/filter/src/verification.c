#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
#define QTY 4

int verification(int argc, char *argv[], int *filter){

  char filters[SIZE] = "bergs";
  char bmp[QTY] = "pmb.";

  if(argc != 4){
    printf("Usage: <%s> <filter> <infile_name.bmp> <outfile_name.bmp>\n", *argv);
    printf("Filters: ");
    for(int i = 0; i < SIZE; i++){
      printf("-%c ", filters[i]);
    }
    puts("");
    return 1;
  }

  if(strlen(argv[1]) != 2){
    puts("Invalid filter!");
    printf("Filters: ");
    for(int i = 0; i < SIZE; i++){
      printf("-%c ", filters[i]);
    }
    puts("");
    return 2;
  }
  else{
    if(argv[1][0] != '-'){
      puts("Invalid filter!");
      printf("Filters: ");
      for(int i = 0; i < SIZE; i++){
        printf("-%c ", filters[i]);
      }
      puts("");
      return 2;
    }
    int i;
    for(i = 0; i < SIZE; i++) 
      if(argv[1][1] == filters[i]){
        *filter = i;
        break;
      }
    if(i == SIZE){
      puts("Invalid filter!");
      printf("Filters: ");
      for(int i = 0; i < SIZE; i++){
        printf("-%c ", filters[i]);
      }
      puts("");
      return 2;
    }
  }

  for(int i = 0, n = strlen(argv[2]) - 1; i < QTY; i++, n--){
    if(argv[2][n] != bmp[i]){
      puts("Invalid infile name!");
      return 3;
    }
  }

  for(int i = 0, n = strlen(argv[3]) - 1; i < QTY; i++, n--){
    if(argv[3][n] != bmp[i]){
      puts("Invalid outfile name!");
      return 4;
    }
  }
  return 0;
}
