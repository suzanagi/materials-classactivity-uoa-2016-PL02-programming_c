#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main(){

  //カウンタ変数ほかの宣言
  int i = 0, flag = 0;

  //読み込んだ文字コードを入れる変数を宣言
  int rightdata, leftdata;

  //ファイルポインタの宣言
  FILE *right, *left;

  /*file open*/
  right = fopen("mydata.out","r");
  left = fopen("data.out","r");

  /*データの一致を確認*/
  while(1){
    rightdata = fgetc(right);
    leftdata = fgetc(left);

    i++;

    if(rightdata == EOF && leftdata == EOF) break;

    if(rightdata != leftdata){
      flag = 1;//データが一致しなかったらflagに1を入れてbreak
      break;
    }
  }

  /*データの一致不一致を出力*/
  if(flag == 0)printf("Two files are identical.\n");
  else printf("Two files are different at %d byte.\n",i);
  
  return 0;
}
