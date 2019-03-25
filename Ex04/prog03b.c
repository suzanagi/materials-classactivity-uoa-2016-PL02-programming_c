#include <stdio.h>
#include <string.h>

int main()
{
/*比較する単語２つを文字配列に格納する*/
  char wrd1[] = "university";   /* 文字配列wrd1を"university"で初期化 */
  char wrd2[] = "aizu";   /* 文字配列wrd2を"aizu"で初期化 */
  char buf[100];   /* 単語読み取り用の文字配列 */

  /* 文字列の読み取りと置き換え        */
  /* 読取に成功している間は処理を続ける */
  while ( scanf("%s",buf) == 1 ){
    /*置き換え対象の文字と入力を比較し、
      一致したら先頭の文字を置き換える*/
    if ( strcmp(buf,wrd1) == 0 ){
      buf[0] = 'U';
    }
    else if ( strcmp(buf,wrd2) == 0 ){
      buf[0] = 'A';
    }

    printf( "%s ", buf );   /* 単語の間にスペースをひとつ入れて出力 */
  }
  printf("\n");

  return 0;
}
