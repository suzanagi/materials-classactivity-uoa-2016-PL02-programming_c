#include<stdio.h> //標準入出力をインクルード
#include<stdlib.h> //stdlibをインクルード

/*main関数*/
int main(){
  /*入力、出力に用いるファイルポインタを宣言*/
  FILE *fpin, *fpout;

  /*文字型で読み込みに用いる変数cを宣言*/
  char c;

  /*入力ファイルをオープンする*/
  fpin = fopen("read.dat","r");

  /*入力ファイルが存在しない、または開けないとき*/
  if(fpin == NULL){
    /*エラーメッセージを出力*/
    printf("read file open error\n");
    /*プログラムを終了*/
    exit(1);
  }

  /*出力ファイルをオープンする*/
  fpout = fopen("out.dat","w");
  /*出力ファイルが存在しない、または開けないとき*/
  if(fpout == NULL){
    /*エラーメッセージを出力*/
    printf("write file open error\n");
    /*入力ファイルをクローズする*/
    fclose(fpin);
    /*プログラムを終了*/
    exit(2);
  }
  
  /*入力ファイルからの入力がEOFでないとき(判定と一緒に文字を読み込む)*/
  while(fscanf(fpin,"%c",&c) != EOF){
    /*読み込んだ文字を出力ファイルに出力*/
    fprintf(fpout,"%c",c);
  }
  /*出力ファイルをクローズ*/
  fclose(fpout);
  /*入力ファイルをクローズ*/
  fclose(fpin);
  
  /*返り値は0*/
  return 0;
}
