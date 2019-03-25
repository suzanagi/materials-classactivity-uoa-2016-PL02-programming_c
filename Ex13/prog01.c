#include <stdio.h>
#include <math.h>

#define RAD M_PI_2

typedef struct {
  double  x; /* x座標 */
  double  y; /* y座標 */
} Point;

Point rotate_90_1(Point, Point);
void  rotate_90_2(Point, Point *);

int main()
{
  Point pc = {3.0, 1.0}, p = {4.0, 3.0}, p1,p2;

  /*1は回転対象にPoint型を引数とする*/
  p1 = rotate_90_1(pc, p);

  /*2は回転対象に直接ポインタをいれる*/
  /*そのため座標pはp2に格納してもってく*/
  p2 = p;
  rotate_90_2(pc, &p2);

  printf("rotate_90(1): %f %f\n",p1.x,p1.y);
  printf("rotate_90(2): %f %f\n",p2.x,p2.y);

  return 0;
}

Point rotate_90_1(Point center, Point p)
{
  Point rot;
  /*
    中心が原点の場合
    90度回転後の座標(x', y')は
    x' = xcos90 - ysin90
    y' = xsin90 + ycos90
    で求められる
   */

  /*一旦中心座標を原点にし回転を計算してからx座標を基準に戻す*/
  rot.x = ((p.x - center.x) * cos(RAD) - (p.y - center.y) * sin(RAD)) + center.x;
  rot.y = ((p.x - center.x) * sin(RAD) + (p.y - center.y) * cos(RAD)) + center.y;

  return rot;
}

void rotate_90_2(Point center, Point *p)
{
  /*回転の処理でpを変更すると不都合なため演算結果の変数を用意*/
  Point rot;

  /*rotate_90_1と同様のことをポインタに置き換える*/
  rot.x = ((p->x - center.x) * cos(RAD) - (p->y - center.y) * sin(RAD)) + center.x;
  rot.y = ((p->x - center.x) * sin(RAD) + (p->y - center.y) * cos(RAD)) + center.y;

  /*引数として与えられたPoint型変数の値を回転した値にする*/
  *p = rot;
}
