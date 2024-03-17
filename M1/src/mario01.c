#include <stdio.h>

int main(){

  int num;

  do{
    printf("Digit a positive integer(different than 0): ");
    scanf("%d", &num);
  } while(num < 1);

  for(int i = 0; i < num; i++){
    for(int j = 0; j < num; j++){
      if(i + j + 1 >= num) printf("#");
      else printf(" ");
    }
    puts("");
  }

  return 0;
}
