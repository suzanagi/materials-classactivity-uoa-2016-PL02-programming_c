#include <stdio.h>
#include <math.h>
double myexp(int,int);
double divx(int,int);

int main(){
  int x;
  int n;
  double ex;

  printf("xを入力して下さい ");
  scanf("%d", &x);
  printf("次数nを入力して下さい ");
  scanf("%d", &n);
  
  ex = myexp(x,n);
  printf("\nexp(%d,%d) =\t%20.15f\n",x,n,ex); /* 結果表示 */
  printf("exp(%d) =\t%20.15f\n",x,exp(x));    /* 数学関数 */

  return 0;
}

double myexp(int x, int n){
  double e;

  if(n == 0) e = 1;
  else e = divx(x, n) + myexp(x, n - 1);

  printf("depth(%3d) : exp(%d) = %20.15f\n", n, x, e );
  return e;
}

double divx(int x ,int n){
  double e;

  if(n == 0) e = 1;
  else e = (double)x / (double)n * divx(x, n - 1);

  return e;
}
