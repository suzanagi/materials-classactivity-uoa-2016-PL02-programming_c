#include <stdio.h>
#include <math.h>

struct xy {
  double  x; /* x座標 */
  double  y; /* y座標 */
};

struct rect {
  struct xy p1;
  struct xy p2;
};

int main()
{
  struct rect  rect1 = {{1.0,5.0},{4.0,1.0}};
  double area;

  area = (double)fabs((rect1.p1.x - rect1.p2.x) * 
                     (rect1.p1.y - rect1.p2.y));
  printf("The area of the rectangle is %f\n",area);

  return 0;
}
