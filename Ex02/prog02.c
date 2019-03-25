#include <stdio.h>

/* マクロ定義 */
#define N 100
#define BLACK '1'
#define WHITE '0'

/* 外部変数の定義 */
char data[N][N];

/* 関数のプロトタイプ宣言 */
void init(void);
void draw(int, int);
void imgout(void);

int main() {
  int i,j;

  init();

  for(i = 0; i < N / 2; i++)//左上半分を描画
    {
      for(j = 0; j < N / 2; j++)
	{
	  if(i >= j) draw(i ,j); 
	}
    }

  for(i = N / 2; i < N; i++)//右上半分を描画
    {
      for(j = 0; j < N / 2; j++)
	{
	  if(i + j <= N) draw(i ,j);
	}
    }

  for(i = 0; i < N / 2; i++)//左下半分を描画
    {
      for(j = N / 2; j < N; j++)
	{
	  if(i + j >= N) draw(i ,j);
	}
    }

  for(i = N / 2; i < N; i++)//右下半分を描画
    {
      for(j = N / 2; j < N; j++)
	{
	  if(i <= j) draw(i ,j);
	}
    }

  imgout();
  return 0;
}

/* (0,0)から(N-1,N-1) すべての点を白くする  */
void init(void)
{
  int i, j;
  for(i = 0; i < N; i++)
    {
      for(j = 0; j < N; j++)
	{
	  data[i][j] = WHITE;
	}
    }
}

/* 引数で指示された座標を黒くする */
void draw(int x, int y)
{
  data[y][x] = BLACK;
}

/* Plain PBM形式で画像データを出力する */
void imgout(void)
{
  int i, j;

  /* PBM形式のためのおまじない */
  printf("P1\n");
  printf("%d %d\n", N, N);

  for(i = 0; i < N; i++)
    {
      for(j = 0; j < N; j++)
	{
	  printf("%c ",data[i][j]);
	}
      printf("/n");
    }
}
