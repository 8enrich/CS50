#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define CHAR 26

void cipher(char*, int);

int main(int argc, char *argv[]){

  if(argc != 2){
    printf("Usage: <%s> <key>\n", *argv);
    exit(1);
  }
  for(int i = 0; *(*(argv + 1) + i) != '\0'; i++){
    if((*(*argv + 1) + i) <= 48 && *(*(argv + 1) + i) >= 57){
      printf("Usage: <%s> <key>\n", *argv);
      exit(2);
    }
  }

  char *text;
  int key = atoi(*(argv + 1)) % CHAR;

  if(!(text = (char*) malloc(sizeof(char) * SIZE))) exit(3);

  printf("Plaintext: ");
  scanf("%100[^\n]", text);

  cipher(text, key);
  printf("Ciphertext: %s\n", text);

  free(text);

  return 0;
}

void cipher(char *text, int key){
  for(int i = 0; *(text + i) != '\0'; i++){
    if((*(text + i) >= 'a') && *(text + i) <= 'z')
      *(text + i) += (*(text + i) + key <= 'z')?key:key - CHAR;
    else if((*(text + i) >= 'A') && *(text + i) <= 'Z')
      *(text + i) += (*(text + i) + key <= 'Z')?key:key - CHAR;
  }
}
