#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


int main(){
  //double型で座標値と距離を保存する変数を用意し初期化
  double x = 0, y = 0, z = 0;
  double distance = DBL_MAX;

  //double型でファイルから座標値を読み出す変数を用意する
  double readx, ready, readz;

  //その他戻り値用の変数などを用意する
  int status;

  //ファイル操作
  FILE *fpin, *fpout;

  fpin = fopen("coord.in","r");
  if(fpin == NULL){
    printf("Cannnot open file coord.in.\n");
    exit(8);
  }

  //ファイルから座標を１つ読み込む
  fscanf(fpin, "%lf%lf%lf", &x, &y, &z);
  distance = sqrt(x*x + y*y + z*z);

  //ファイルから座標を読み込み最も近い点を選ぶ
  while(1){

    status = fscanf(fpin, "%lf%lf%lf",&readx ,&ready ,&readz);

    /*確認用コード
    printf("reading: x:%lf y:%lf z:%lf\n",readx ,ready ,readz);
    printf("status:%d\n",status);
    printf("nearest: x:%lf y:%lf z:%lf\n",x ,y ,z);
    */

    if(status == EOF) break;
    else if(status == 3){
      if(sqrt(readx*readx + ready*ready + readz*readz) < distance){
	x = readx;
	y = ready;
	z = readz;
	distance = sqrt(x*x + y*y + z*z);

      }

    }
    else{
      printf("Reading Error\n");
      break;
    }
  }

  //ファイル処理
  fclose(fpin);
  fpout = fopen("coord.out","w");

  //最も近かった座標とその距離をファイルに出力
  
  fprintf(fpout, "%3.1lf %3.1lf %3.1lf ",x ,y ,z);
  fprintf(fpout, "(%3.1lf)\n",distance);

  /*確認用コード
  printf("%3.1lf %3.1lf %3.1lf ",x ,y ,z);
  printf("(%3.1lf)\n",distance);
  */


  //ファイル処理
  fclose(fpout);


  return 0;
}
