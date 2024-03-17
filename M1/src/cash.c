#include <stdio.h>

#define QTY 4

int main(){

  int values[QTY] = {25, 10, 5, 1};

  float num;
  do{
    printf("Digit the value payed: ");
    scanf("%f", &num);
  }while(num <= 0);

  num = 100 * num;

  int i = 0, count = 0;
  while(num > 0){
    if(num >= values[i]){
      num -= values[i];
      count++;
    }
    else i++;
  }

  printf("The numbers of coins needed is %d\n", count);

  return 0;
}
