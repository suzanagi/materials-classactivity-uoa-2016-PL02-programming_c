#include <stdio.h>
#include <stdlib.h>

#define N 15
#define BLACK '1'
#define WHITE '0'

typedef struct{
  int    x;
  int    y;
} XYdata;

void rev(XYdata);
void output(void);
void init(void);

char img[N][N];

int main(int argc, char *argv[]){

XYdata a = {12,12};
/*call*/
fprintf(stderr,"define of a completed\n");

init();
/*call*/
fprintf(stderr,"init() completed\n");

  rev(a);
/*call*/
fprintf(stderr,"rev(a) completed\n");

  output();
/*call*/
fprintf(stderr,"output() completed\n");

  return 0;
}

void rev(XYdata a)
{
  if(img[a.y][a.x] == WHITE){//白だったら黒に
    img[a.y][a.x] = BLACK;
  }
  else if(img[a.y][a.x] == BLACK){//黒だったら白に
    img[a.y][a.x] = WHITE;
  }
  else{//白でも黒でもない(エラー)
    printf("Exception Error!\n");
    exit(8);
  }
}

void output(void){
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

void init(void)
{
  int i, j;
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      img[i][j] = WHITE;
}
