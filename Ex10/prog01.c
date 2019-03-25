#include <stdio.h>

typedef struct{
  int  id;       /* ID    */
  char name[20]; /* 名前   */
  int  score;    /* 点数   */
  char grade;    /* 成績 　*/
} Record;

void PrintData1(Record);
void PrintData2(Record *);

int main(){
  Record person1 = {
    1240234,
    "Yuta Nemoto",
    95,
    'A'
  };
  Record person2 = {
    1240000,
    "Sinzo Abe",
    79,
    'B'
  };

  Printdata1(person1);
  Printdata1(person2);

  Printdata2(&person1);
  Printdata2(&person2);

  return 0;
}

Printdata1(Record r){
  printf("%d %s\n",r.id ,r.name);
  printf("score:%d grade:%c\n",r.score ,r.grade);
  printf("\n");
}

Printdata2(Record *r){
  printf("%d %s\n",r->id ,r->name);
  printf("score:%d grade:%c\n",r->score ,r->grade);
  printf("\n");
}
