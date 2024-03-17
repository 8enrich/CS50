#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 100
#define SIZE 100

typedef struct{
  char name[SIZE];
  int votes;
  unsigned short eliminated;
  unsigned short voted;
} candidate;

int vote(candidate*,char*,int);
int print_winner(candidate*,int);
void tabulate(candidate*,int**,int,int);
int find_min(candidate*,int);
int is_tie(candidate*,int,int);
void eliminate(candidate*,int,int);

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

  int min, num;
  while(1){
    tabulate(people, preferences, size, voters);
    num = print_winner(people, size);
    if(!num) break;
    min = find_min(people, size);
    num = is_tie(people, size, min);
    if(num){
      puts("It's a tie!");
      break;
    }
    eliminate(people, size, min);
  }

  free(people);
  free(name);
  free(preferences);
  free(rows);

  return 0;
}

int vote(candidate *vector, char *name, int size){
  for(int i = 0; i < size; i++){
    if(!strcmp(name, (vector + i)->name) && !((vector + i)->voted)) return i;
  }
  return -1;
}

void tabulate(candidate *vector, int **preferences,int size, int voters){
  for(int i = 0; i < voters; i++)
    for(int j = 0; j < size; j++)
      if(!(vector + *(*(preferences + j) + i))->eliminated){
        (vector + *(*(preferences + j) + i))->votes++;
        break;
      }
}

int print_winner(candidate *vector, int size){
  for(int i = 0; i < size; i++)
    if((vector + i)->votes > (size/2) + 1){
      printf("%s\n", (vector + i)->name);
      return 0;
    }
  return 1;
}

int find_min(candidate *vector, int size){
  int lowest = vector->votes;
  for(int i = 1; i < size; i++)
    if((vector + i)->votes < lowest && !((vector + i)->eliminated)) lowest = (vector + i)->votes;
  return lowest;
}

int is_tie(candidate *vector, int size, int min){
  int quantity_min = 0;
  for(int i = 0; i < size; i++)
    if((vector + i)->votes == min && !((vector + i)->eliminated)) quantity_min++;
  if(quantity_min == size) return 1;
  return 0;
}

void eliminate(candidate *vector, int size, int min){
  for(int i = 0; i < size; i++){
    if((vector + i)->votes == min && !((vector + i)->eliminated)) (vector + i)->eliminated++;
  }
}
