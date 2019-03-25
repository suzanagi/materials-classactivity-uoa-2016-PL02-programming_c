#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BLACK '1'
#define WHITE '0'

#define PI 3.14159265358979323846264338
#define XMAX   240  /* 画像の幅   */
#define YMAX   180  /* 画像の高さ */
#define VNUM   5    /* 星の頂点数 */
#define VSKP   2    /* つなぐ頂点の間隔 */
#define RADIUS 50   /* 星の大きさ */

char  *odata;
char **img_alloc(int, int);
void   img_free(char **,int, int);
void   img_fill(char **, int, int, char);
void   img_write(char **, int, int);
void   img_line(char **, int, int, int, int, int, int, char);

int main(){
  char **img;
  int i;
  double sx[VNUM], sy[VNUM];

  /* 240x180の画像を確保する */
  img = img_alloc(XMAX,YMAX);
  img_fill(img, XMAX, YMAX, WHITE);

  /* VNUM(=5)角形の頂点の座標を求める       */
  /* 中心(XMAX/2, YMAX/2)、　               */
  /* 半径RADIUSの円を                       */
  /* 360/VNUM度ずつ角度を進めて頂点を求める */
  for(i=0; i<VNUM; i++){
    sx[i] = (int)(XMAX/2.0+RADIUS*sin(2.0*PI/VNUM*i)+0.5);
    sy[i] = (int)(YMAX/2.0-RADIUS*cos(2.0*PI/VNUM*i)+0.5);
  }
  /* 五(VNUM)芒星を書くために    */
  /* VSKP(=2)個先の頂点と線を引く*/
  for(i=0;i<VNUM;i++){
    img_line(img,XMAX,YMAX,sx[i],sy[i],
             sx[(i+VSKP)%VNUM],sy[(i+VSKP)%VNUM],BLACK);
  }
  /* 画像を書きだす */
  img_write(img,XMAX,YMAX);
  /* 画像領域の解放 */
  img_free(img,XMAX,YMAX);
  return 0;
}

char **img_alloc(int x, int y){
    char **data;
    int i, j;

    data = malloc(sizeof(char *) * y);
    if(data == NULL){
      free(data);
      return NULL;
    }

    
    for(i = 0; i < y; i++){
      data[i] = malloc(sizeof(char) * x);
      if(data[i] == NULL){
	free(data);
	free(data[i]);
	return NULL;
      }
    }

    /*
    int i;
     ２次元配列の作成 
    data = malloc(sizeof(char *) * y);
    if(data == NULL){
      return NULL;
    }
    odata = malloc(sizeof(char) * x * y);
     画素数が多すぎる場合 
    if (odata == NULL){
      free(data);
      return NULL;
    }
     ２次元配列の設定 
    for(i = 0; i < y; i++){
      data[i] = odata + i * x;
    }
    */
    return data;
}

void  img_free(char **img, int x, int y){
  int i;
  for(i = 0; i < y; i++)
    free(img[i]);
  free(img);
}

void img_fill(char **img, int x, int y, char col){
  int i,j;
  for(i=0;i<y;i++)
    for(j=0; j<x; j++)
      img[i][j]=col;
}

void   img_write(char **img, int x, int y){
  int i, j;

  /* 最初にP1とx,yの画素数を出力 */
  printf("P1\n");
  printf("%d %d\n", x, y);

  /* 実際のデータ出力 */
  for (i = 0; i < y; i++){
    for (j = 0; j < x; j++){
      printf("%c", img[i][j]);
    }
    printf("\n");
  }
}

/* 画像に線分を引く                         */
/* 始点と終点は画像の範囲を超えてはならない */
void   img_line(char **img, int x, int y,
                int x1, int y1, int x2, int y2, char col){
  int dx, dy, sign, i;
  float d;

  dx = x2 - x1;
  dy = y2 - y1;
  /* 点のとき */
  if(dx==0 && dy==0){
    img[y1][x1] = col;
    return;
  }
  /* 長いほうを基準に線を引く。傾きは１以下になる。*/
  if(abs(dx)>abs(dy)){
    d = (float)dy/dx;
    sign = (dx>0)-(dx<0);
    for(i=x1; i!=x2+sign; i+=sign)
      img[(int)(y1+d*(i-x1))][i]=col;
  } else {
    d = (float)dx/dy;
    sign = (dy>0)-(dy<0);
    for(i=y1; i!=y2+sign; i+=sign){
      img[i][(int)(x1+d*(i-y1))]=col;
    }
  }
}
