#include <stdio.h>
#include <stdlib.h>

#define CNUM 800
#define UNIT 10

int main(){
  int i, status;
  int carry;
  FILE *template_fp, *inputtext_fp;
  FILE *write_fp;

  /*書き込み先のファイルをオープン*/
  write_fp = fopen("prog06.html","w");
  if(write_fp == NULL){
    printf("Cannot open file prog06.html\n");
    exit(1);
  }
  /*ヘッダの書き込まれているファイルをオープン*/
  template_fp = fopen("header.txt","r");
  if(template_fp == NULL){
    printf("Cannot open file prog06.html\n");
    exit(1);
  }

  /*ファイルにヘッダを書き込む*/
  while(1){
    carry = fgetc(template_fp);
    fputc(carry,write_fp);
    if(carry == '\0') break;
  }    

  /*ヘッダのあるファイルをクローズ*/
  fclose(template_fp);
 
  return 0;
}
