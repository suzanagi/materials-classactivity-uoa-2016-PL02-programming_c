#include <stdio.h>

typedef struct{
  int id;
  char name[20];
  int score;
  char grade;
} Record;



int main(){
  Record data[2] = {
    {
      1240234,
      "Yuta Nemoto",
      95,
      'A'
    },
    {
      1240000,
      "Sinzo Abe",
      79,
      'B'
    },
  };

  Record *p = data;
  Record *q;
  int i;

  for(i = 0; i < 2; i++){
    printf("%d\n", (*(p + i)).id);
    printf("%s\n", (*(p + i)).name);
    printf("%d\n", (*(p + i)).score);
    printf("%c\n", (*(p + i)).grade);
  }

  printf("\n");

  for(i = 0; i < 2; i++){
    printf("%d\n", (p + i)->id);
    printf("%s\n", (p + i)->name);
    printf("%d\n", (p + i)->score);
    printf("%c\n", (p + i)->grade);
  }

  printf("\n");

  for(q = p; q < p + 2; q++){
    printf("%d\n", (*q).id);
    printf("%s\n", (*q).name);
    printf("%d\n", (*q).score);
    printf("%c\n", (*q).grade);
  }

  printf("\n");

  for(q = p; q < p + 2; q++){
    printf("%d\n", q->id);
    printf("%s\n", q->name);
    printf("%d\n", q->score);
    printf("%c\n", q->grade);
  }

  printf("\n");

  printf("sizeof(data):%d\t\taddress of data: %p\n",sizeof(data) ,&data);
  printf("sizeof(data[1]):%d\taddress of data[1]: %p\n",sizeof(data[1]) ,&data[1]);

  return 0;
}
