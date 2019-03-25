#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(){
  char init[]="[Wakamatsu]"; /* 初期データ用文字列 */
  char *str;
  int n;
  char input[BUFSIZE];       /* 入力用文字列バッファ */
  /* その他の変数を宣言 */
  int i, j;
  int stringlength, buflength;
  char *temp;

  /* strの初期化 */
  str = init;

  /* strにinitの内容のコピーを保持させる */
  str = (char *)malloc(strlen(init) * sizeof(char));
  strcpy(str, init);

  while (1) {
    printf( "%s\n", str );
    if( scanf("%d %s", &n, input) != 2 ) break;

    /*inputとstrの文字数を調べる*/
    stringlength = strlen(str);
    buflength = strlen(input);

    /*inputの挿入位置に挿入可能かのチェック*/
    if(n > stringlength + 1){
      printf("error\n");
      continue;
    }

    /*inputの両端に括弧をつける*/
    for(i = buflength; i >= 0; i--)
      input[i + 1] = input[i];
    input[buflength + 2] = input[buflength + 1];//null文字を移動させる
    input[0] = '[';
    input[buflength + 1] = ']';

    /*inputの文字数を更新する*/
    buflength = strlen(input);

    /*tempにstrの値を渡しておく*/
    temp = (char *)malloc(stringlength * sizeof(char) + 1);
    strcpy(temp, str);

    /*strの領域を調整する*/
    str = (char *)malloc((stringlength + buflength + 1) * sizeof(char));
    if(str == NULL){
      printf("メモリ確保に失敗しました。\n");
      free(str);
      return -1;
    }

    /*strに文字を再挿入する*/
    strcpy(str, temp);

    /*tempの領域を解放する*/
    free(temp);

    /*inputを挿入するためのスペースをあける*/
    for(i = buflength; i > 0; i--){
      for(j = (stringlength + buflength); j >= n; j--){
	str[j + 1] = str[j];
      }
    }

    /*strにinputを挿入する*/
    for(i = 0; i < buflength; i++){
      str[n + i] = input[i];
    }

  }
  free(str);
  return 0;
}

