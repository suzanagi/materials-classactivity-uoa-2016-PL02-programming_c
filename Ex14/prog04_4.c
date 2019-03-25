#include <stdio.h>
#include <math.h>
#include "prog04_1.h"

#ifdef DEBUG

int main(){

  Triangle tri = 
    {
      {{0,0},{1,0},{0,1}},
      0
    };

  printf("status: %d\n",IsTriangle(&tri));

  return 0;
}

#endif

int IsTriangle(Triangle *tri){
  /*3辺の長さを格納する変数*/
  double side[3];
  /*簡単のためx1-x0, x2-x1, x0-x2を求めておく。*/
  double x01,x12,x20;
  /*yについても同様にする。*/
  double y01,y12,y20;

  /*それぞれx座標の差を求める。*/
  x01 = tri->vertex[1].x - tri->vertex[0].x;
  x12 = tri->vertex[2].x - tri->vertex[1].x;
  x20 = tri->vertex[0].x - tri->vertex[2].x;

  /*同様にy座標の差を求める。*/
  y01 = tri->vertex[1].y - tri->vertex[0].y;
  y12 = tri->vertex[2].y - tri->vertex[1].y;
  y20 = tri->vertex[0].y - tri->vertex[2].y;

  /*座標の差が求まったため、それを用いて各辺の長さを求める。
   *長さl = √((x1-x0)^2+(y1-y0)^2)
   */
  side[0] = sqrt(x01 * x01 + y01 * y01);
  side[1] = sqrt(x12 * x12 + y12 * y12);
  side[2] = sqrt(x20 * x20 + y20 * y20);

  /*確認
  fprintf(stderr,"%f %f %f",side[0],side[1],side[2]);
  */

  /*三角形の条件は、辺aについて|b-c|<a , a < b+cが成り立っていればよい。*/
  if((side[2] - side[1]) * (side[2] - side[1]) < side[0] * side[0] && side[0] < side[1] + side[2])
    return 1;
  else return 0;
}
