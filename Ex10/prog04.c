#include <stdio.h>
#include <math.h>

typedef struct{
  double x;
  double y;
  double z;
} Point;

typedef struct{
  Point center;
  Point p;
} Sphere;

int main(){
  Sphere object;
  double r;

  printf("球の中心座標(x,y,z)を入れて下さい\n");
  scanf("%lf%lf%lf",&object.center.x ,&object.center.y ,&object.center.z);
  //printf("%f%f%f\n",object.center.x ,object.center.y ,object.center.z);
  printf("球の表面上の点の座標(x,y,z)を入れて下さい\n");
  scanf("%lf%lf%lf",&object.p.x ,&object.p.y ,&object.p.z);

  printf("中心座標(%f, %f, %f)\n",object.center.x ,object.center.y ,object.center.z);
  printf("点の座標(%f, %f, %f)\n",object.p.x ,object.p.y ,object.p.z);
  r = sqrt((object.p.x - object.center.x) * (object.p.x - object.center.x) + (object.p.y - object.center.y) * (object.p.y - object.center.y) + (object.p.z - object.center.z) * (object.p.z - object.center.z));
  printf("半径%f\n",r);
  printf("表面積 %f, 体積 %f\n",4 * M_PI * r * r ,4 * M_PI * r * r * r / 3);

  return 0;
}
