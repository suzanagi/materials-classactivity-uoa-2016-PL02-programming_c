#include <stdio.h>

int myatoi(char *);

int main()
{
  char str2[][20]={"  123.45  ","A123"," -13A","+123  45",""};
  int ival, i;

  for ( i=0; str2[i][0]!='\0'; i++ ){
    ival = myatoi( str2[i] );
    printf("string:%s\n", str2[i]);
    printf("value:%d\n", ival);
  }
  return 0;
}
/* この後に関数 myatoi を作成する */
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

  //確認printf("%s\n",str);
  //printf("%d\n",num);
  return num;
}
