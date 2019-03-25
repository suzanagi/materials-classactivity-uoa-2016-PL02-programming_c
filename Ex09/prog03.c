#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* マクロ定義 */
#define N     256
#define BLACK '1'
#define WHITE '0'

/* 構造体宣言 */
typedef struct{
  int    x;
  int    y;
} XYdata;

/* 関数のプロトタイプ宣言 */
void init(void);
void rev(XYdata);
void circle(XYdata, int);
void output(void);

/* 外部変数の定義 */
char img[N][N];

int main(int argc, char *argv[])
{
  XYdata base1, base2;
  int r1, r2;

  /*call*/
  //fprintf(stderr,"definition completed\n");
  
  /* コマンドラインから円の中心座標と半径を２組入力 */
  //base1 = {atoi(argv[1]) ,atoi(argv[2])};
  //fprintf(stderr,"argv[1]:%s\n",argv[1]);
  base1.x = atoi(argv[1]);
  base1.y = atoi(argv[2]);
  r1 = atoi(argv[3]);

  /*call*/
  //fprintf(stderr,"base1 structure completed\n");

  //base2 = {atoi(argv[4]) ,atoi(argv[5])};
  base2.x = atoi(argv[4]);
  base2.y = atoi(argv[5]);
  r2 = atoi(argv[6]);

  /*call*/
  //fprintf(stderr,"base2 structure completed\n");

  /* 画像初期化関数(すべて白くする)を呼ぶ */
  init();

  /*call*/
  //fprintf(stderr,"init() completed\n");

  /* 円の内部を白黒反転する */
  circle( base1, r1);
  circle( base2, r2);
  
  /* 表示 */
  output();
  return 0;
}

/* すべての点を白に初期化する関数 */
void init(void)
{
  int i, j;
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      img[i][j] = WHITE;
}

/* 引数で指示された座標の点一つを白黒反転する関数 */
void rev(XYdata a)
{
  if(img[a.y][a.x] == WHITE){//白だったら黒に
    img[a.y][a.x] = BLACK;
    /*call*/
    //fprintf(stderr,"WHITE -> BLACK\n");
  }
  else if(img[a.y][a.x] == BLACK){//黒だったら白に
    /*call*/
    //fprintf(stderr,"img[%d][%d] == %c\n",a.y ,a.x ,img[a.y][a.x]);

    img[a.y][a.x] = WHITE;
    /*call*/
    //fprintf(stderr,"BLACK -> WHITE\n");
  }
  else{//白でも黒でもない(エラー)
    printf("Exception Error!\n");
    exit(8);
  }
}

/* 引数で指示された座標を中心に,半径 r 以内の点を白黒反転する関数 */
void circle(XYdata c, int r)
{
  /* 円の方程式 x*x + y*y = r*rより dy=0～rの位置の
     円周の座標を求め、その座標間に線を引く */
  int i, j;
  double distance, rad;
  XYdata temp;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if((j - c.y) * (j - c.y) + (i - c.x) * (i - c.x) <= r*r){
	//fprintf(stderr,"中心との距離:%d\n",(int)distance);
	//fprintf(stderr,"半径内(%d,%d)\n値:%c\n",j,i,img[j][i]);
	temp.x = j;
	temp.y = i;
	rev(temp);
      }
    }
  }

}

/* PBM形式で画像データを出力する関数 */
void output(void)
{
  int i, j;
  printf("P1\n");
  printf("%d %d\n",N ,N);
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      printf("%c ",img[j][i]);
    }
    printf("\n");
  }
}
