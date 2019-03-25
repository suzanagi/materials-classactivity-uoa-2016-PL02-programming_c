#include <stdio.h>

int myatoi(char *);

int main(){

  char Wareki[3];
  int year = 0;

  printf("Input Wareki: ");
  scanf("%s",Wareki);

  switch(Wareki[0]){
  case 'H':
    year += 1988;
    break;
  case 'S':
    year += 1925;
    break;
  case 'T':
    year += 1911;
    break;
  case 'M':
    year += 1867;
    break;
  default:
    break;
  }

  year += myatoi(&Wareki[1]);

  printf("Year: %d\n",year);

  /*確認用
  printf("input:%s\n",year);
  */

  return 0;
}

int myatoi(char *str){
  int num = 0, minus;
  int i;
  /*空白を読み飛ばす(ポインタをすすめる)*/
  while(1){
    if(*str == ' ')
      str++;
    else break;
  }

  /*-があったらminusを1増やしておいて読み飛ばす*/
  if(*str == '-'){
    minus++;
    str++;
  }

  /*ポインタを進めながら、文字型を整数型に変える*/
  while(1){
    if('0' <= *str  && *str <= '9'){
      num = num * 10 + (int)(*str - '0');
      str++;
    }
    else if(*str == '+'){
      str++;
    }
    else break;
  }

  if(minus == 1) num *= -1;

  return num;
}
