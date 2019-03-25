#include <stdio.h>
#include <math.h>

struct xy {
  double x;
  double y;
};

struct rect{
  struct xy p1;
  struct xy p2;
};

int main(){
  double vartical, side, diagonal;
  struct rect square = {{1.0,5.0},{4.0,1.0}};

  vartical = fabs(square.p1.y - square.p2.y);
  side = fabs(square.p2.x - square.p1.x);
  diagonal = sqrt((square.p2.x - square.p1.x) * (square.p2.x - square.p1.x) + (square.p2.y - square.p1.y) * (square.p2.y - square.p1.y));

  printf("Depth: %.2f\tWidth: %.2f\t diagonal length: %.2f\n",vartical ,side ,diagonal);
  printf("The area of the rectangle is %.2f\n",vartical * side);

  return 0;
}
