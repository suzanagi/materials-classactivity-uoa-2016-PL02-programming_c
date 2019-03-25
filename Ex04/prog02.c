#include <stdio.h>
int main()
{
  int x=3, y=9; /* この行は変更しない */
  int *p, *q;//ポインタの宣言

  p = &x;
  q = &y;

  /* 課題では以下のprintf()の中をx,yを使わない形に書き換える */
  printf(" value 1: %d  (%p)\n", *p, p );
  printf(" value 2: %d  (%p)\n", *q, q );
  printf(" sum:     %d\n", *p+*q );
  printf(" product: %d\n", *p**q );

  return 0;
}
