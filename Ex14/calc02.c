#include<stdio.h>
#include "header02.h"

#ifdef DEBUG
int main()
{
  Triangle t = {1,0,0,1,0,0};
  printf("Area = %f\n",calcarea(t));

  return 0;
}
#endif

double calcarea(Triangle t)
{
  double area;

  area = (double)((t.p[2].x -  t.p[1].x)*(t.p[0].y -  t.p[1].y) - 
         (t.p[2].y -  t.p[1].y)*(t.p[0].x -  t.p[1].x))/2.0;
  return myabs(area);
}
    
