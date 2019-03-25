#include <stdio.h>
#define N 100

int main(void){

  char str1[N], str2[N]; /*文字列用のバッファ*/
  int i = 0;/*必要に応じて変数宣言追加*/

  /*入力処理*/
  printf("input : ");
  scanf("%s",str1);

  /*入力確認
  printf("str1 : %s\n",str1);
  */

  /*str1に入力された文字列をstr2にコピーする処理*/
  while(1){
    str2[i] = str1[i];
    if(str1[i] == '\0') break;
    i++;
  }

  /*コピーした文字列を出力*/
  printf("[%s]\n",str2);

  return 0;
}
