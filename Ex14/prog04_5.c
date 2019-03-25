#include <stdio.h>
#include <math.h>
#include "prog04_1.h"

#ifdef DEBUG
/*デバッグ用にmain関数を用意する。*/
int main(){
  /*仮の三角形を宣言、初期化する。*/
  Triangle tri = 
    {
      {{0,0},{0,2},{3,0}},
      0
    };

  GetTriangleArea(&tri);

  printf("S = %f\n",tri.surface);

  return 0;
}

#endif

void GetTriangleArea(Triangle *tri){
  /*各点から三角形の3辺を求め、ヘロンの公式により面積を求める。*/
  /*3辺の長さを格納する変数*/
  double side[3];
  /*簡単のためx1-x0, x2-x1, x0-x2を求めておく。*/
  double x01,x12,x20;
  /*yについても同様にする。*/
  double y01,y12,y20;
  /*ヘロンの公式を使うため各辺の長さを足し合せる。後に半分にする。*/
  double s;
  int i;

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

  /*三角形の周の長さを求める。すべての辺の長さを足し合せる。*/
  for(i = 0; i < 3; i++)
    s += side[i];
  /*1/2する。*/
  s /= 2.0;

  /*以上を使いヘロンの公式から面積を求める。*/
  tri->surface = sqrt( s * (s - side[0]) * (s - side[1]) * (s - side[2]) );

  s = 0;
}
