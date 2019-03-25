#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 4

void reverse(char *);

int main()
{
  char *array[NUM] = {"abcd","efgh","lmnopqr","stuvw"};
  int i;

  for(i = 0; i < NUM; i++){
    printf("[%2d] : %s -> ", i, array[i]);
    reverse(array[i]);
    printf("\n");
  }

  return 0;
}

void reverse(char *str){
  char *revstr;

  if(*str == '\0') return;
  else{
    reverse(str + 1);
    printf("%c",*str);
  }
}
