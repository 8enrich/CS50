#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9
#define SIZE 100

typedef struct{
  char name[SIZE];
  int votes;
} candidate;

int vote(candidate*,char*,int);
void print_winner(candidate*,int);

int main(int argc, char *argv[]){

  if(argc < 2 || argc > MAX + 1){
    printf("Usage: <%s> <name of candidate 1> <name of candidate 2> ... <name of candidate 9>\n", *argv);
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
  printf("Number of voters: ");
  scanf("%d", &voters);

  char *name = NULL;
  if(!(name = (char*)malloc(sizeof(char) * SIZE))) exit(3);

  for(int i = 0; i < voters; i++){
    printf("Vote: ");
    scanf("%s", name);
    if(vote(people, name, size)) puts("Invalid vote!");
  }

  print_winner(people, size);

  free(name);
  free(people);

  return 0;
}

int vote(candidate *vector, char *name, int size){
  for(int i = 0; i < size; i++){
    if(!strcmp(name, (vector + i)->name)){
      ((vector + i)->votes)++;
      return 0;
    }
  }
  return 1;
}

void print_winner(candidate *vector, int size){
  int highest = 0;
  for(int i = 0; i < size; i++){
    if((vector + i)->votes > highest) highest = (vector + i)->votes;
  }
  for(int i = 0; i < size; i++){
    if((vector + i)->votes == highest) printf("%s\n", (vector + i)->name);
  }
}
