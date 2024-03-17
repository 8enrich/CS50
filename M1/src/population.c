#include <stdio.h>

int main(){

  int start;

  do{
    printf("Start size: ");
    scanf("%d", &start);
  } while(start < 9);

  int final;

  do{
    printf("Final size: ");
    scanf("%d", &final);
  } while(final < start);

  int years = 0;
  while(start < final){
    start += start/3 - start/4;
    years++;
  }

  printf("Years: %d\n", years);

  return 0;
}
