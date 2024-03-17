#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define HEAD 44

typedef uint8_t BYTE;
typedef int16_t WAV;

int main(int argc, char *argv[]){

  char *extension = "vaw.";

  if(argc != 4){
    printf("Usage: <%s> <infile_name> <outfile_name> <factor>\n", *argv);
    exit(1);
  }

  int i;
  int n = strlen(extension);
  int insize = strlen(argv[1]);
  int outsize = strlen(argv[2]);
  for(i = 0; i < n; i++){
    if(extension[i] != argv[1][insize - 1 - i]) break;
    if(extension[i] != argv[2][outsize - 1 - i]) break;
  }
  if(i != n){
    puts("Invalid file!");
    exit(1);
  }

  char *infile_name = argv[1];
  char *outfile_name = argv[2];
  float factor = atof(argv[3]);

  FILE *infile = fopen(infile_name, "r");
  if(!infile){
    puts("The infile can't be open!");
    exit(2);
  }

  FILE *outfile = fopen(outfile_name, "w");
  if(!outfile){
    puts("The outfile can't be open!");
    fclose(infile);
    exit(3);
  }

  BYTE header[HEAD];

  for(int i = 0; i < HEAD; i++){
    fread(&header[i], sizeof(BYTE), 1, infile);
    fwrite(&header[i], sizeof(BYTE), 1, outfile);
  }

  int value;
  WAV buffer;
  do{
    fread(&buffer, sizeof(WAV), 1, infile);
    buffer *= factor;
    fwrite(&buffer, sizeof(WAV), 1, outfile);
    value = feof(infile);
  } while(!value);

  fclose(infile);
  fclose(outfile);

  return 0;
}
