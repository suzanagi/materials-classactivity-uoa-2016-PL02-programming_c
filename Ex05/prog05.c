#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255

int main(){
  char input[MAX];
  char hostname[10], hostaddress[16];
  int status, flag;
  FILE *fp_hosts;

  while(1){
    /*その都度ファイルをオープンする*/
    fp_hosts = fopen("stdhosts.txt","r");
    /*入力を受け付ける*/
    status = scanf("%s",input);
    if(status == EOF) exit(1);
    /*ファイルから文字列を読み込み、比較する*/
    //flagを1としておく
    flag = 1;
    status = 2;
    while(status == 2){
      status = fscanf(fp_hosts,"%s %s",hostaddress, hostname);
      /*ループ内確認
      printf("%s\n",hostname);
      */
      //一致したらflagを0とする
      if(strcmp(input,hostname) == 0){
	flag = 0;
	break;
      }
    }
    /*結果の出力*/
    printf("%s ",input);
    if(flag == 0){
      printf("%s\n",hostaddress);
    }
    else{
      printf("is not found\n");
    }
    /*その都度ファイルをクローズする*/
    fclose(fp_hosts);

  }

  return 0;
}
