#include <stdio.h>
#include <time.h>
#include "prog01.h"

#define N 20
#define YEAR 2016
#define MONTH 10
#define DAY 1

Record input(void);
void output(Record);
int getage(Record);

int main(){

  Record data[N];
  int i, datanum;

  time_t now;     /* 時刻を保持する型の変数を宣言 */
  struct tm now2; /* 年・月などに分割して時刻を保持する構造体型の変数を宣言 */
  
  time(&now);     /* 変数 now に現在時刻を得る */
  now2 = *localtime(&now); /* 得た時刻を構造体型の各要素に変換する */

  for(i = 0; i < N; i++){
    data[i] = input();
    if(data[i].gender == -1) break;
  }
  datanum = i;

  printf("--------データ出力--------\n");
  printf("年齢基準日：%d年%d月%d日\n",YEAR ,MONTH ,DAY);
  for(i = 0; i < datanum; i++){
    printf("%2d人目:",i + 1);
    output(data[i]);
  }

  return 0;
}

Record input(void){

  Record data;
  int status;

  status = scanf("%s", &data.name);
  scanf("%d",&data.birthday[0]);
  scanf("%d",&data.birthday[1]);
  scanf("%d",&data.birthday[2]);
  scanf("%d",&data.gender);

  if(status == EOF) 
    data.gender = -1;

  return data;
}

void output(Record data){

  printf("名前(姓): %-10s\t",data.name);
  printf("%d年%2d月%2d日生 ",data.birthday[0] ,data.birthday[1] ,data.birthday[2]);

  printf("年齢：%d ",getage(data));

  switch(data.gender){
  case 0: 
    printf(" 男性\n");
    break;
  case 1:
    printf(" 女性\n");
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
