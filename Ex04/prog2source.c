#include <stdio.h>
int main()
{
  int x=3, y=9; /* この行は変更しない */

  /* 課題では以下のprintf()の中をx,yを使わない形に書き換える */
  printf(" value 1: %d  (%p)\n", x, &x );
  printf(" value 2: %d  (%p)\n", y, &y );
  printf(" sum:     %d\n", x+y );
  printf(" product: %d\n", x*y );

  return 0;
}
