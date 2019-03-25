#include <stdio.h>
#include "prog01.h"

#define MEM 2
#define YEAR 2016
#define MONTH 10
#define DAY 1

Record input(void);
void output(Record);
int getage(Record);

int main(){

  Record data[MEM];
  int i;

  printf("--------データ入力--------\n");
  for(i = 0; i < MEM; i++){
    printf("%d人目の",i + 1);
    data[i] = input();
    printf("\n");
  }

  printf("--------データ出力--------\n");
  printf("年齢基準日：%d年%d月%d日\n",YEAR ,MONTH ,DAY);
  for(i = 0; i < MEM; i++){
    printf("%d人目のデータ:",i + 1);
    output(data[i]);
    printf("年齢：%d\n",getage(data[i]));
    printf("\n");
  }

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

int getage(Record data){
  int age;

    if(MONTH < data.birthday[1]){//基準日より前の月だから、年齢は(西暦差-1)歳
      age = YEAR - data.birthday[0] - 1;
    }
    else if( MONTH == data.birthday[1]){//基準日と同じ月だから、日付で判断
      if(DAY >= data.birthday[2])//誕生日は基準日以降だから、年齢は(西暦差)歳
	age = YEAR - data.birthday[0];
      else//誕生日は基準日より前だから、年齢は(西暦差-1)歳
	age = YEAR - data.birthday[0] - 1;
    }
    else{//基準日より後の月だから、年齢は(西暦差)歳
      age = YEAR - data.birthday[0];
    }

  return age;
}
