#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 4

char *reverse(char *);

int main(){
char *array[NUM] = {"abcd","efgh","lmnopqr","stuvw"};
 int i;

 for(i = 0; i < NUM; i++)
   printf("[%2d] : %s -> %s\n",i ,array[i] ,reverse(array[i]));

  return 0;
}

char *reverse(char *str){
  char *revstr;
  int charnum, i;

  /*null文字の追加とループをまわすために文字列の文字数を求めておく(charnumはnullを含まない)*/
  charnum = strlen(str);
  /*mallocはstrの領域の大きさを用いて行う(nullを含むため)*/
  revstr = malloc(sizeof(str));

  for(i = 0; i < charnum; i++){
    /*null文字を除いてstrの後ろからi番目の文字をrevstrに入れる*/
    revstr[i] = str[charnum - i - 1];
  }

  /*revstrの最後にnull文字をつける*/
  revstr[charnum + 1] = '\0';

  return revstr;
}
