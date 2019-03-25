#include<stdio.h>
#include "header02.h"

int main()
{
  int i;
  Triangle t;
  for(i = 0; i < 3; i++){
    scanf("%d %d",&t.p[i].x, &t.p[i].y);
  }
  printf("Area = %f\n",calcarea(t));

  return 0;
}

/* for component test */
#ifdef DEBUG
double calcarea(Triangle t)
{
  int i;
  for(i = 0; i < 3; i++){
    printf("%d %d\n",t.p[i].x,t.p[i].y);
  }
  return 0;
}
#endif
