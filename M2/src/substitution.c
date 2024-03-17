#include <stdio.h>
#include <stdlib.h>

#define ABC 26
#define SIZE 100

void upper_str(char*);
int verify_key(char*, int);
void cipher(char*, char*);

int main(int argv, char *argc[]){

  if(argv != 2){
    printf("Usage: <%s> <key>\n", *argc);
    exit(1);
  }

  int valid;
  upper_str(*(argc + 1));
  valid = verify_key(*(argc + 1), ABC);

  if(valid){
    printf("Usage: <%s> <key>\n", *argc);
    exit(3);
  }

  char *text;

  if(!(text = (char*)malloc(sizeof(char) * SIZE))) exit(4);

  printf("Plaintext: ");
  scanf("%100[^\n]", text);

  cipher(text, *(argc + 1));

  printf("Ciphertext: %s\n", text);

  free(text);

  return 0;
}

void upper_str(char *str){
  for(int i = 0; *(str + i) != '\0'; i++)
    if(*(str + i) >= 'a' && *(str + i) <= 'z')
      *(str + i) -= 32;
}

int verify_key(char *str, int size){
  char *alphabet;

  if(!(alphabet = (char*)malloc(sizeof(char) * size))) exit(2);

  for(int i = 0; *(str + i) != '\0'; i++){
    if(*(str + i) < 'A' || *(str + i) > 'Z') return 1;
    else (*(alphabet + (*(str + i) - 'A')))++;
  }

  for(int i = 0; i < size; i++) if(*(alphabet + i) != 1) return 1;
  return 0;
}

void cipher(char *text, char *key){
  for(int i = 0; *(text + i) != '\0'; i++){
    if(*(text + i) >= 'A' && *(text + i) <= 'Z') *(text + i) = *(key + (*(text + i) - 'A'));
    else if(*(text + i) >= 'a' && *(text + i) <= 'z') *(text + i) = *(key + (*(text + i) - 'a')) + 32;
  }
}
