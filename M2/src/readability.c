#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int readability(const char*);

int main(){

  char *text;
  int index;

  if(!(text = (char*) malloc(sizeof(char) * SIZE))) exit(1);

  printf("Text: ");
  scanf("%1000[^\n]", text);

  index = readability(text);

  if(index < 1) puts("Before Grade 1");
  else if(index >= 16) puts("Grade 16+");
  else printf("Grade: %d\n", index);

  free(text);

  return 0;
}

int readability(const char *text){
  int letters = 0, words = 0, phrases = 0;
  float result;
  for(int i = 0; *(text + i) != '\0'; i++){
    if((*(text + i) >= 'a' && *(text + i) <= 'z') || (*(text + i) >= 'A' && *(text + i) <= 'Z')) letters++;
    else if((*(text + i) == '!') || (*(text + i) == '?') || (*(text + i) == '.')) phrases++;
    if((*(text + i) == ' ') || (*(text + i + 1) == '\0')) words++;
  }
  result = 0.0588 * (((float)letters/words) * 100) - 0.296 * (((float)phrases/words) * 100) - 15.8;
  return (result - (int)result > 0.5)?(int)result + 1:(int) result;
}
