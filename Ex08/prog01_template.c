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
  /* 上2つの説明：                             */

  printf( "size of str3:    %d\n", sizeof(str3) );
  printf( "size of str4:    %d\n", sizeof(str4) );
  /* 上2つの説明：                              */

  printf( "size of str3[1]: %d\n", sizeof(str3[1]) );
  printf( "size of str4[1]: %d\n", sizeof(str4[1]) );
  /* 上2つの説明：                              */
  printf( "\n" );

  str5 = str4;        /* str5はstr4の先頭を指す */
  printf( "size of str5:    %d\n", sizeof(str5) );
  /* 説明：                                     */

  printf( "(*str5)[1]:      %c\n", (*str5)[1] );
  printf( "*str5[1]:        %c\n",  *str5[1] );
  /* 上2つの説明：                              */

  printf( "*(*str5+2):      %c\n", *(*str5+2) );
  printf( "**(str5+2):      %c\n", **(str5+2) );
  /* 上2つの説明：                              */
  printf( "\n" );

  arr2 = (int *) malloc( 5 * sizeof(int) );
  printf( "size of arr1:    %d\n", sizeof(arr1) );
  printf( "size of arr2:    %d\n", sizeof(arr2) );
  /* 上2つの説明：                              */

  free(arr2);
  return 0;
}
