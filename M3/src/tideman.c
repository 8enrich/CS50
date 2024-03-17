#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 100
#define SIZE 100

typedef struct{
  char name[SIZE];
  unsigned short voted;
} candidate;

typedef struct{
  unsigned short winner;
  unsigned short loser;
  int difference;
} pair;

int vote(candidate*,char*,int);
void record_preference(int**,int,int,int**);
void add_pairs(pair*,int**,int,int);
void sort_pairs(pair*,int);
int lock_pairs(pair*,int,int);
void change_next(int*,int);

int main(int argc, char *argv[]){

  if(argc < 2 || argc > MAX_CANDIDATES + 1){
    printf("Usage: <%s> <name of candidate 1> <name of candidate 2> ... <name of candidate %d>\n", *argv, MAX_CANDIDATES);
    exit(1);
  }

  int size = argc - 1;
  candidate *people = NULL;

  if(!(people = (candidate*)malloc(sizeof(candidate) * size))) exit(2);

  for(int i = 0; i < size; i++){
    for(int j = 0; j < SIZE; j++)
      *((people + i)->name + j) = *(*(argv + i + 1) + j);
  }

  int voters;
  while(1){
    printf("Number of voters: ");
    scanf("%d", &voters);
    if(voters > MAX_VOTERS || voters < 1) puts("Invalid number of voters!");
    else break;
  }

  char *name = NULL;
  if(!(name = (char*)malloc(sizeof(char) * SIZE))) exit(3);

  int **preferences = NULL;
  int *rows = NULL;
  if(!(preferences = (int**)malloc(sizeof(int*) * size))) exit(4);
  if(!(rows = (int*)malloc(sizeof(int) * voters * size))) exit(5);

  for(int i = 0; i < size; i++)
      *(preferences + i) = (rows + i * voters);

  for(int i = 0; i < voters; i++){
    for(int k = 0; k < size; k++) (people + k)->voted = 0;
    for(int j = 0; j < size; j++){
      printf("Rank %d: ", j + 1);
      scanf("%s", name);
      *(*(preferences + j) + i) = (vote(people, name, size));
      if(*(*(preferences + j) + i) < 0){
        puts("Invalid, try again!");
        j--;
      }
      else (people + *(*(preferences + j) + i))->voted++;
    }
    puts("");
  }

  int **pairs = NULL;
  int *pairs_rows = NULL;

  if(!(pairs = (int**)malloc(sizeof(int*) * size))) exit(6);
  if(!(pairs_rows = (int*)calloc(size * size, sizeof(int)))) exit(7);

  for(int i = 0; i < size; i++){
    *(pairs + i) = (pairs_rows + i * size);
  }

  pair *fights = NULL;
  int num = 0, value = 0;
  for(int i = size - 1; i > 0; i--) num += i;

  if(!(fights = (pair*)malloc(sizeof(pair) * num))) exit(8);

  record_preference(preferences, voters, size, pairs);
  add_pairs(fights, pairs, size, voters);
  sort_pairs(fights, num);
  value = lock_pairs(fights, num, size);

  printf("%s\n", (people + value)->name);

  free(people);
  free(name);
  free(preferences);
  free(rows);
  free(pairs);
  free(pairs_rows);
  free(fights);

  return 0;
}

int vote(candidate *vector, char *name, int size){
  for(int i = 0; i < size; i++){
    if(!strcmp(name, (vector + i)->name) && !((vector + i)->voted)) return i;
  }
  return -1;
}

void record_preference(int **preferences, int voters,int size, int **pairs){
  for(int i = 0; i < voters; i++)
    for(int j = 0; j < size; j++)
      for(int k = j + 1; k < size; k++)
        pairs[preferences[j][i]][preferences[k][i]]++;
}

void add_pairs(pair *vector, int **pairs, int size, int voters){
  for(int i = 0, k = 0; i < size; i++){
    (vector + k)->difference = 0;
    for(int j = 0; j < size; j++){
      if(pairs[i][j] - (voters - pairs[i][j]) > 0){
        (vector + k)->difference = pairs[i][j] - (voters - pairs[i][j]);
        (vector + k)->winner = i;
        (vector + k)->loser = j;
        k++;
      }
    }
  }
}

void sort_pairs(pair *vector, int num){
  int change = 1;
  pair temp;
  while(change){
    num--;
    change = 0;
    for(int i = 0; i < num; i++){
      if((vector + i)->difference < (vector + i + 1)->difference){
        temp = *(vector + i);
        *(vector + i) = *(vector + i + 1);
        *(vector + i + 1) = temp;
        change = 1;
      }
    }
  }
}

int lock_pairs(pair *pairs, int num, int size){
  int highest = (pairs)->winner, lowest = (pairs)->loser;
  for(int i = 1; i < num; i++){
    if((pairs + i)->winner == lowest && (pairs + i)->loser != highest) lowest = (pairs + i)->loser;
    if((pairs + i)->loser == highest && (pairs + i)->winner != lowest) highest = (pairs + i)->winner;
  }
  return highest;
}

void change_next(int *vector, int next){
  if(*(vector + next + 1) < 0){
    *(vector + next) = *(vector + next) ^ *(vector + next + 1);
    *(vector + next + 1) = *(vector + next) ^ *(vector + next + 1);
    *(vector + next) = *(vector + next) ^ *(vector + next + 1);
  }
  else{
    change_next(vector, next + 1);
    change_next(vector, next);
  }
}

