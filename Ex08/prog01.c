#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *str1= "EXERCISE";
  char str2[]="exercise";
  char *str3[]={"abc","lmnopqr","wxyz"};
  char str4[3][7]={"ABC","LMNOPQR","WXYZ"};
  char (*str5)[7];
  int  arr1[5];
  int  *arr2;

  printf( "size of str1:    %d\n", sizeof(str1) );
  printf( "size of str2:    %d\n", sizeof(str2) );
  /* 上2つの説明：
   * str1はポインタであり、solarisの環境での大きさは4biteである。
   * str2はchar型配列であり、大きさは'exersise'8文字とヌル文字1文字で9biteである。
   * 上2つはどちらもサイズを表すが、str1はポインタであるのに対しstr2は文字列である点で異なる。
   */

  printf( "size of str3:    %d\n", sizeof(str3) );
  printf( "size of str4:    %d\n", sizeof(str4) );
  /* 上2つの説明：
   * str3はchar型配列を示すポインタ配列であり、3つのポインタを含むことから大きさはsolarisでは4bite
   *が3つで12biteである。
   * str4は7x3の領域が確保されたchar型2次元配列であり、1biteが7x3個で21biteである。
   * 上2つはどちらもサイズを表すが、str3はポインタであるのに対しstr2は文字列である点で異なる。
   */

  printf( "size of str3[1]: %d\n", sizeof(str3[1]) );
  printf( "size of str4[1]: %d\n", sizeof(str4[1]) );
  /* 上2つの説明：
   * str3[1]はポインタ配列str3の1番目を示すから、大きさはポインタ1つ分でsolarisでは4biteである。
   * str4[1]はchar型文字配列str4の7bite確保された要素を示すから、大きさはbiteである。
   * 上2つは、str3が1つのポインタであるのに対しstr4はサイズを確保された文字列である点で異なる。
   */
  printf( "\n" );

  str5 = str4;        /* str5はstr4の先頭を指す */
  printf( "size of str5:    %d\n", sizeof(str5) );
  /* 説明：                                     
   * str5はポインタで4bite
   */

  printf( "(*str5)[1]:      %c\n", (*str5)[1] );
  printf( "*str5[1]:        %c\n",  *str5[1] );
  /* 上2つの説明：                             
   * (*str5)[1]はstr4の0番目の要素(ABC)の1文字目を示しているため、Bを出力する。
   * *str5[1]はstr4の1番目の要素(LMNOPQR)の先頭要素を指しているため、Lを出力する。
   * 上は()によって先頭を確定して列要素を指定しているのに対し、下は添字で行要素を指定している。
   */

  printf( "*(*str5+2):      %c\n", *(*str5+2) );
  printf( "**(str5+2):      %c\n", **(str5+2) );
  /* 上2つの説明：
   * *(*str5+2)はstr5(str4の先頭要素)に2を足したアドレスにあるCを出力している。
   * **(str5+2)はstr5+2(str4の2番目の要素WXYZ)の先頭要素であるWを出力している。
   * 上は*を()内に含むためstr5の示す二次配列str4の行要素を指定しているため+2は列要素を決めている。
   * 下は*が()外にあるためstr5+2は行要素がstr4の2番目の要素になりその先頭アドレスを示す。
   */
  printf( "\n" );

  arr2 = (int *) malloc( 5 * sizeof(int) );
  printf( "size of arr1:    %d\n", sizeof(arr1) );
  printf( "size of arr2:    %d\n", sizeof(arr2) );
  /* 上2つの説明：                              
   * arr1はint型配列で領域は5個分確保されているため、大きさは4biteが5つで20biteである。
   * arr2はint型ポインタであるため大きさはsolarisでは4biteである。
   * 上は領域の確保された配列であるのに対し下はポインタである点で異なる。
   */

  free(arr2);
  return 0;
}
