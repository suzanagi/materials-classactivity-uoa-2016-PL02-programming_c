#include <stdio.h>
int main()
{
  double x, *p;
  p = &x;
  
  x = 3.14;
  printf("%f\n",x);
  printf("%f\n\n",*p);
  
  *p = 6.28;
  printf("%f\n",x);
  printf("%f\n\n",*p);

  return 0;
}
