#include <stdio.h>
#include "prog04_1.h"

#ifdef DEBUG
/*デバッグ用にmain関数を用意。入力された座標と返り値を表示する。*/
int main(){
  Triangle tri;
  int i;

  printf("戻り値: %d\n",InputTriangle(&tri,1));

  for(i = 0; i < 3; i++)
    printf("x:%2.1f\ty:%2.1f\n",tri.vertex[i].x ,tri.vertex[i].y);

  return 0;
}

#endif

int InputTriangle(Triangle *tri, int n){
  int i;
  
  printf("Input triangle %d:\n",n);

  for(i = 0; i < 3; i++){
    switch(i){
    case 0:
      printf("1st");
      break;
    case 1:
      printf("2nd");
      break;
    case 2:
      printf("3rd");
      break;
    }
    printf(" vertex: ");
    /*入力をスキャンし、各点座標のxyふたつが入力されなかったら-1を返し終了*/
    if(scanf("%lf %lf",&tri->vertex[i].x ,&tri->vertex[i].y) != 2) 
      return -1;
  }

  /*入力された座標を確認表示する*/
  for(i = 0; i < 3; i++){
    printf("Vertex #%d: (%f, %f)\n",i+1 ,tri->vertex[i].x ,tri->vertex[i].y);
  }

  /*正常に3座標の入力ができたため0を返す*/
  return 0;
}
