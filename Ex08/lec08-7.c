#include <stdio.h>
#include <stdlib.h>

#define BLACK '1'
#define WHITE '0'

char **input_data(int *, int *);
void output_data(char**, int, int);
void invert_data(char**, int, int);
void fliplr_data(char**, int, int);
void outputrl_data(char**, int, int);

char *odata;

int main()
{
  char** img_data;
  int  i, x_size, y_size;

  /* データ読み込み  */
  img_data = input_data(&x_size, &y_size);

  /* マクロによる関数コール */
  #ifdef INV
    invert_data(img_data, x_size, y_size);
  #endif
  #ifdef FLIPLR
    fliplr_data(img_data, x_size, y_size);
  #endif
  #ifdef ROTL
    outputrl_data(img_data, x_size, y_size);
  #else
    output_data(img_data, x_size, y_size);
  #endif

  free(img_data);
  free(odata);

  return 0;
}

char **input_data(int *x_sizep, int *y_sizep){ /* データ入力 */

  int i, j, x_size, y_size;
  char **data;

  /* 最初にP1と書いていないものはデータ形式が違う */
  if (getchar() != 'P' || getchar() != '1'){
    fprintf(stderr, "データの形式が違います\n");
    exit(1);
  }

  /* x,yそれぞれの画素数を得る */
  scanf("%d", &x_size);
  scanf("%d", &y_size);

  /* ２次元配列の作成 */
  data = malloc(sizeof(char *) * y_size);
  odata = malloc(sizeof(char) * x_size * y_size);
  /* 画素数が多すぎる場合 */
  if (odata == NULL){
    fprintf(stderr, "データが大きすぎます\n");
    free(data);
    exit(2);
  }
  /* ２次元配列の設定 */
  for(i = 0; i < y_size; i++){
    data[i] = odata + i * x_size;
  }

  /* 実際のデータ入力 */
  for (i = 0; i < y_size; i++){
    for (j = 0; j < x_size; j++){
      /* scanf入力データがおかしいかＥＯＦになった場合             */
      /* この際、" %c"とすることで空白、改行、タブなどは読み飛ばす */
      if(scanf(" %c", &data[i][j]) != 1){
	       exit(3);
      }
      /* データが０／１じゃない場合 */
      if(data[i][j] != WHITE && data[i][j] != BLACK){
	      fprintf(stderr, "データが異常でした\n");
	      exit(4);
      }
    }
  }

  /* サイズの設定 */
  *x_sizep = x_size;
  *y_sizep = y_size;

  return data;
}

void output_data(char **data, int x_size, int y_size){ /* データ出力 */

  int i, j;

  /* 最初にP1とx,yの画素数を出力 */
  printf("P1\n");
  printf("%d %d\n", x_size, y_size);

  /* 実際のデータ出力 */
  for (i = 0; i < y_size; i++){
    for (j = 0; j < x_size; j++){
      printf("%c", data[i][j]);
    }
    printf("\n");
  }
}

void invert_data(char **data, int x_size, int y_size){ /* 白黒反転 */

  int i, j;

  for (i = 0; i < y_size; i++){
    for (j = 0; j < x_size; j++){
      data[i][j] = data[i][j] == BLACK ? WHITE : BLACK;
    }
  }
}

void fliplr_data(char **data, int x_size, int y_size){ /* 左右反転 */

  int i, j, x2;
  char c;

  x2 = x_size/2;

  for (i = 0; i < y_size; i++){
    for (j = 0; j < x2; j++){
      c = data[i][j];
      data[i][j] = data[i][x_size - j  - 1];
      data[i][x_size - j  - 1] = c;
    }
  }
}

void outputrl_data(char **data, int x_size, int y_size){ /* 左９０度回転 */

  int i, j;

  /* 最初にP1とx,yの画素数を出力(入れ換え) */
  printf("P1\n");
  printf("%d %d\n", y_size, x_size);

  /* 実際のデータ出力 */
  for (i = 0; i < x_size; i++){
    for (j = 0; j < y_size; j++){
      /* 回転の処理 */
      printf("%c",data[j][x_size - i - 1]);
    }
    printf("\n");
  }
}
