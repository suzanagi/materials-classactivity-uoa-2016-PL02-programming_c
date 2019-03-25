typedef struct{
  double x;
  double y;
} Point;

typedef struct{
  Point vertex[3];
  double surface;
} Triangle;

/*prog04_3.c
 *三角形構造体のポインタを引数とし、3点の座標を直接格納する。
 *2番目の引数は1個目の三角形なら1,2個目の三角形なら2を渡す。(出力の都合)
 *正常な入力なら0、正常な入力がなかった場合-1を返す。
 */
int InputTriangle(Triangle *, int);

/*prog04_4.c
 *三角形構造体のポインタを引数とし、各点からそれが三角形になるか判定。
 *三角形になれば1、ならなければ0を返す。
 */
int IsTriangle(Triangle *);

/*prog04_5.c
 *三角形構造体のポインタを引数とし、各点から三角形の面積を求める。
 *求めた三角形の面積は受け取った構造体の要素surfaceに直接書き込む
 */
void GetTriangleArea(Triangle *);

/*prog04_6.c
 *三角形構造体のポインタを引数とし、各座標から三角形の重心を求める。
 *関数内で重心を格納するためのPoint型の構造体をひとつ宣言し、求めた重心を
 *そこに格納し戻り値とする。
 */
Point CalcTriangleCentroid(Triangle *);
