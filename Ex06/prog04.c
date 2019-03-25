#include <stdio.h>
#include <stdlib.h>

char grade_char(int);

int main(int argc, char *argv[]){
  int i;
  char *score;

  if(argc < 2) exit(1);

  for(i = 1; i < argc; i++){
    score = argv[i];
    printf("Point %s: %c\n",score ,grade_char(atoi(score)));
  }

  return 0;
}

char grade_char(int score)
{
  if(score >= 0 && score <= 34) return 'F';
  else if(score >= 35 && score <= 49) return 'D';
  else if(score >= 50 && score <= 64) return 'C';
  else if(score >= 65 && score <= 79) return 'B';
  else if(score >= 80 && score <= 100) return 'A';
  else return 'Z';//Zをエラーとして扱う
}
