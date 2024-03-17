#include <stdio.h>

void sum_digits(int, long, int*, int*);

int main(){

  long num;

  do{
    printf("Digit a credit card number: ");
    scanf("%ld", &num);
  } while(num < 1000000000000);

  int sum = 0;
  int first_numbers;
  
  sum_digits(2, num, &sum, &first_numbers);
  sum_digits(1, num, &sum, &first_numbers);

  if(sum % 10) puts("Invalid");
  else if(first_numbers / 10 == 4) puts("Visa");
  else if(first_numbers >= 51 && first_numbers <= 55) puts("MasterCard");
  else if(first_numbers == 34 || first_numbers == 37) puts("Amex");
  else puts("Unknow card");

  return 0;
}

void sum_digits(int first, long temp, int *sum, int *first_numbers){
  int digit;
  for(int i = first; temp > 0; i++){
    if(i % 2){
      digit = first * (temp % 10);
      if(digit >= 10) *sum += digit % 10 + digit / 10;
      else *sum += digit;
    }
    temp /= 10;
    if(temp < 100 && temp > 10) *first_numbers = temp;
  }
}
