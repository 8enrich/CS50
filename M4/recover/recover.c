#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SIZE 4
#define FAT 512

typedef uint8_t BYTE;

int main(int argc, char *argv[]){

  if(argc != 2){
    printf("Usage: <%s> <file_name>\n", *argv);
    exit(1);
  }

  FILE *infile = fopen(argv[1], "r");
  if(!infile){
    puts("The infile can't be open!");
    exit(2);
  }

  int vector[5] = {255,216,255,224,239};

  BYTE *line = NULL;

  if(!(line = (BYTE*)malloc(sizeof(BYTE) * FAT))){
    puts("Not enough memory to vector!");
    fclose(infile);
    exit(3);
  }

  char file_name[] = "./images/000.jpg";
  char *str = NULL;
  FILE *outfile = NULL;
  int value, i, count = 0;

  if(!(str =(char*)malloc(sizeof(char) * 2))){
    puts("Not enough memory to string!");
    fclose(infile);
    free(line);
    exit(4);
  }

  do{
    fread(line, sizeof(BYTE), FAT, infile);
    for(i = 0; i < SIZE; i++){
      if(i < SIZE - 1){
        if(line[i] != vector[i]) break;
      }
      else if(line[i] < vector[i] || line[i] > vector[SIZE]) break;
    }
    if(i == SIZE){
      if(outfile) fflush(outfile);
      if(count < 10) sprintf(str, "0%d", count);
      else sprintf(str, "%d", count);
      for(int j = strlen(file_name) - 1; j >= 0; j--){
        if(file_name[j + 1] == '.'){
          for(int k = 0, n = strlen(str) - 1; k <= n; k++) file_name[j - k] = str[n - k];
          break;
        }
      }
      outfile = fopen(file_name, "w");
      if(!outfile){
        puts("The outfile can't be open!");
        fclose(infile);
        fclose(outfile);
        free(line);
        free(str);
        exit(5 + count);
      }
      count++;
    }
    if(outfile) fwrite(line, sizeof(BYTE), FAT, outfile);
    value = feof(infile);
  } while(!value);

  free(line);
  free(str);
  fclose(outfile);
  fclose(infile);

  return 0;
}
