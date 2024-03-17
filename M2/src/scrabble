#include <stdio.h>
#include <stdlib.h>

#define ABC 26
#define SIZE 100
#define PLAYERS 2

void upper_str(char*);
int compute_score(char*,int*);

int main(){

  int points[ABC] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

  char **words = NULL;
  char *rows = NULL;
  int *scores = NULL;
  int last_value = 0;

  if(!(words = (char**)malloc(sizeof(char*) * PLAYERS))) exit(1);
  if(!(rows = (char*)malloc(sizeof(char) * SIZE * PLAYERS))) exit(2);
  if(!(scores = (int*)malloc(sizeof(int) * PLAYERS))) exit(3);

  for(int i = 0; i < PLAYERS; i++){
    *(words + i) = (rows + i * SIZE);
    printf("Player %d: ", i + 1);
    scanf("%s", *(words + i));
    upper_str(*(words + i));
    *(scores + i) = compute_score(*(words + i), points);
    if(i){
      if(last_value > *(scores + i)) puts("Player 1 wins!");
      else if(*(scores + i) > last_value) puts("Player 2 wins!");
      else puts("Tie");
    }
    last_value = *(scores + i);
  }

  free(words);
  free(rows);
  free(scores);

  return 0;
}

void upper_str(char *str){
  for(int i = 0; *(str + i) != '\0'; i++){
    if(*(str + i) >= 'a' && *(str + i) <= 'z') *(str + i) -= 32;
  }
}

int compute_score(char *str, int *points){
  int score = 0;
  for(int i = 0; *(str + i) != '\0'; i++){
    if(*(str + i) >= 'A' && *(str + i) <= 'Z')
      score += *(points + *(str + i) - 'A');
  }
  return score;
}
