#include <stdio.h>
#include <stdlib.h>

#define BLACK '1'
#define WHITE '0'

char **img_alloc(int, int);
void   img_free(char **,int, int);
char **img_read(int *, int *);
void   img_write(char **, int, int);
char **img_erode(char **, int, int);  /* エロージョンを行う関数 */
char **img_dilate(char **, int, int); /* ダイレーションを行う関数 */

int main(){
    char **img1, **img2;
    int ix,iy;
  int i,j,checkflag = 0;

  img1 = img_read(&ix,&iy);
  if(img1==NULL){
    fprintf(stderr,"Invlid image format.");
    exit(1);
  }

  #ifdef ERODE
  img2=img_erode(img1,ix,iy);
  img_free(img1,ix,iy);
  #elif DILATE
  img2=img_dilate(img1,ix,iy);
  img_free(img1,ix,iy);
  #else
  img2=img1;
  #endif

  /*call*/
  fprintf(stderr,"At main, something occured error.\n");

  /*ここから*/
  for(i = 0; i < iy; i++)
    for(j = 0; j < ix; j++)
      if(img2[i][j] == BLACK) checkflag = 1;

  if(checkflag == 0) printf("かかれてねえよ\n");
  /*ここまで*/

  /* 画像を書きだす */
  img_write(img2,ix,iy);
  /* 画像領域の解放 */
  img_free(img2,ix,iy);
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

    return data;
}

void  img_free(char **img, int x, int y){
  int i;
  for(i = 0; i < y; i++)
    free(img[i]);
  free(img);
}

char **img_read(int *x, int *y){

  int x_size, y_size;
  int i, j;
  char **data;

  if(getchar() != 'P' || getchar() != '1'){
    fprintf(stderr,"データの形式が違います\n");
    exit(1);
  }

  scanf("%d", &x_size);
  scanf("%d", &y_size);

  data = img_alloc(x_size, y_size);

  for(i = 0; i < y_size; i++){
    for(j = 0; j < x_size; j++){
      if(scanf(" %c", &data[i][j]) != 1){
	exit(3);
      }
      if(data[i][j] != WHITE && data[i][j] != BLACK){
	fprintf(stderr, "データが異常でした\n");
	exit(4);
      }
    }
  }

  *x = x_size;
  *y = y_size;
  return data;
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

char **img_erode(char **img, int x, int y){  /* エロージョンを行う関数 */
  int i, j, k;
  char around[4];
  char **writeimg;

  img = img_alloc(x, y);

  img_write(img,x,y);

  /*call*/
  fprintf(stderr,"At erode, before the loop, x:%d, y:%d\n",x,y);

  for(i = 0; i < y - 1; i++){
    for(j = 0; j < x - 1; j++){
      /*call*/
      fprintf(stderr,"At erode, now, point.(now i:%d,j:%d)\n",i,j);
      fprintf(stderr,"At erode, now, img[i][j] :%c\n",img[i][j]);

      if(i == 0 || j == 0 || i == y - 1 || j == x - 1){
	writeimg[i][j] = img[i][j];
	/*call*/
	fprintf(stderr,"At erode, substitution completed.\n");
	fprintf(stderr,"writeimg is now, \"%c\"\n",writeimg[i][j]);
      }
      else{
	//まわりがすべて黒なら結果は黒
	around[0] = img[j][i - 1];
	around[1] = img[j + 1][i];
	around[2] = img[j][i + 1];
	around[3] = img[j - 1][i];

	for(k = 0; k < 4; k++){
	  if(around[k] == WHITE){
	    writeimg[i][j] = WHITE;
	    break;
          }
        }

	/*call*/
	fprintf(stderr,"At erode, judgement completed.\n");
	fprintf(stderr,"At erode, writeimg[%d][%d] is now, \"%c\"\n",i ,j ,writeimg[i][j]);

      }
    }
  }
  return writeimg;
}

char **img_dilate(char **img, int x, int y){  /* ダイレーションを行う関数 */
  int i, j, k;
  char **writeimg;
  char around[4];
  writeimg = img_alloc(x, y);
  for(i = 0; i < y; i++){
    for(j = 0; j < x; j++){
      if(i == 0 || j == 0 || i == y - 1 || j == x - 1){
	writeimg[i][j] = img[i][j];
      }
      else{
	//まわりに１つでも黒があれば結果は黒
	around[0] = img[j][i - 1];
	around[1] = img[j + 1][i];
	around[2] = img[j][i + 1];
	around[3] = img[j - 1][i];

	for(k = 0; k < 4; k++){
	  if(around[k] == BLACK){
	    writeimg[i][j] = BLACK;
	    break;
	  }
	}
      }
    }
  }
  return writeimg;
}
