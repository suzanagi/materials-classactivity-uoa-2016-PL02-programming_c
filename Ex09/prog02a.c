#include <stdio.h>
#include "prog01.h"

Record input(void);
void output(Record);

int main(){

  Record data;

  data = input();
  output(data);

  return 0;
}

Record input(void){

  Record data;

  printf("データを入力して下さい\n");
  printf("名前（姓）        -> ");
  scanf("%s", &data.name);
  printf("生まれた年（西暦） -> ");
  scanf("%d",&data.birthday[0]);
  printf("生まれた月        -> ");
  scanf("%d",&data.birthday[1]);
  printf("生まれた日        -> ");
  scanf("%d",&data.birthday[2]);
  printf("性別(0:男性,1:女性) -> ");
  scanf("%d",&data.gender);

  return data;
}

void output(Record data){

  printf("\n");

  printf("名前(姓): %s\n",data.name);
  printf("生年月日: %d年 %d月 %d日 ",data.birthday[0] ,data.birthday[1] ,data.birthday[2]);

  switch(data.gender){
  case 0: 
    printf("(男性)\n");
    break;
  case 1:
    printf("(女性)\n");
    break;
  default:
    break;
  }

}
