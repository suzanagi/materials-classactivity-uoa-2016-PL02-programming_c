#include <stdio.h>
#include <math.h>

#define RAD M_PI_2

typedef struct {
  double  x; /* x座標 */
  double  y; /* y座標 */
} Point;

Point rotate_90_3(Point *);
void rotate_90_4(Point *);
void rotate_90_5(Point, Point);

Point p5;

int main()
{
  Point pc = {3.0, 1.0}, p = {4.0, 3.0}, p3, p4;
  /*3,4の回転対象として中心、回転対象を並べた配列を用意*/
  Point rotline[3];
  rotline[0] = pc;
  rotline[1] = p;

  /*3は条件の座標を条件の配列のアドレスで受け取り結果をPoint型で返す*/
  p3 = rotate_90_3(&rotline[0]);

  /*4は条件の座標を条件の配列のアドレスで受け取り結果を2番目の要素に入れる*/
  rotate_90_4(&rotline[0]);
  /*p4に配列に入ってる結果を代入する*/
  p4 = rotline[2];

  /*p5は条件の座標をそれぞれ受け取り結果を外部変数に記憶する*/
  rotate_90_5(pc, p);

  printf("rotate_90(3): %f %f\n",p3.x,p3.y);
  printf("rotate_90(4): %f %f\n",p4.x,p4.y);
  printf("rotate_90(5): %f %f\n",p5.x,p5.y);

  return 0;
}

/*
  中心が原点の場合
  90度回転後の座標(x', y')は
  x' = xcos90 - ysin90
  y' = xsin90 + ycos90
  で求められる
*/

/*二つの点を配列として受け取り、回転させた点を返す関数*/
Point rotate_90_3(Point *info){
  Point rot;
  rot.x = ((info[1].x - info[0].x) * cos(RAD) - (info[1].y - info[0].y) * sin(RAD)) + info[0].x;
  rot.y = ((info[1].x - info[0].x) * sin(RAD) + (info[1].y - info[0].y) * cos(RAD)) + info[0].y;

  return rot;
}

/*二つの点を配列として受け取り、回転させた点を要素２として代入する関数*/
void rotate_90_4(Point *info){
  info[2].x = ((info[1].x - info[0].x) * cos(RAD) - (info[1].y - info[0].y) * sin(RAD)) + info[0].x;
  info[2].y = ((info[1].x - info[0].x) * sin(RAD) + (info[1].y - info[0].y) * cos(RAD)) + info[0].y;

}

/*二つの点を受け取り、回転させた点を外部変数を介して返す関数*/
void rotate_90_5(Point center, Point p){

  p5.x = ((p.x - center.x) * cos(RAD) - (p.y - center.y) * sin(RAD)) + center.x;
  p5.y = ((p.x - center.x) * sin(RAD) + (p.y - center.y) * cos(RAD)) + center.y;
}
