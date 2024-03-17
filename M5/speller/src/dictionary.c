// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 27
#define KEY 3

// Hash table
node *table[N * N * N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
  unsigned int num;
  num = hash(word);
  node *tmp = table[num];
  int value;
  if(tmp->word[0] != '\n'){
    do{
      value = strcasecmp(word, tmp->word);
      if(!value) return true;
      if(!tmp->next) break;
      tmp = tmp->next;
    } while(value >= 0);
  }
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
  unsigned int num = 0, factor = 1;
  if(strlen(word) >= KEY){
    for(int i = KEY - 1; i >= 0; i--){
      if(word[i] >= 'a' && word[i] <= 'z') num += (word[i] - 'a' + 1) * factor;
      else if(word[i] >= 'A' && word[i] <= 'Z') num += (word[i] - 'A' + 1) * factor;
      factor *= N;
    }
  }
  return num;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
  FILE *file = fopen(dictionary, "r");
  if(!file) return false;

  int j, last = -1;
  node *tmp = NULL, *pointer = NULL;
  unsigned int num;
  char *str = (char*) malloc(sizeof(char) * (LENGTH + 1));
  if(!str) return false;
  char c;

  for(int i = 0, size = pow_h(N, KEY); i < size; i++){
    table[i] = malloc(sizeof(node));
    table[i]->word[0] = '\n';
    table[i]->next = NULL;
  }
  while(1){
    j = 0;
    for(c = getc(file); c != EOF; c = getc(file)){
      if(c == '\n') break;
      str[j++] = c;
    }
    if(c == EOF) break;
    num = hash(str);
    if(num != last){
      last = num;
      tmp = table[num];
      if(tmp->word[0] != '\n'){
        while(1){
          if(!tmp->next){
            tmp->next = (node*) malloc(sizeof(node));
            tmp = tmp->next;
            tmp->next = NULL;
            break;
          }
          tmp = tmp->next;
        }
      }
    }
    else{
      tmp->next = (node*) malloc(sizeof(node));
      tmp = tmp->next;
      tmp->next = NULL;
    }
    for(int k = 0; k < j; k++) tmp->word[k] = str[k];
    for(int k = 0; k < LENGTH + 1; k++) str[k] = '\0';
  }
  fclose(file);
  free(str);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
  int i = 0, count = 0, size = pow_h(N, KEY);
  for(node *tmp = table[i]; i < size;){
    if(tmp->word[0] != '\n'){
      count++;
      if(tmp->next){
        tmp = tmp->next;
        continue;
      }
    }
    i++;
    tmp = table[i];
  }
  if(i == size) return count;
  return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
  int i = 0, size = pow_h(N, KEY);
  for(node *tmp = table[i], *last; i < size;){
    last = tmp;
    if(tmp->word[0] != '\n'){
      if(tmp->next){
        tmp = tmp->next;
        free(last);
        continue;
      }
    }
    i++;
    tmp = table[i];
    free(last);
  }
  if(i == size) return true;
  return false;
}

int pow_h(int base, unsigned int exp){
  if(!exp) return 1;
  else return base * pow_h(base, exp - 1);
}
