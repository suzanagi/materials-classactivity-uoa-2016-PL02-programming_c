#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

int main() {
  int i;
  char c;
  FILE *fp;
  char buffer[MAXLEN];
  char query[MAXLEN];
  int status;
  int arg1, arg2;
  int in_len, buf_len;

  /* ファイルのオープン */
  fp = fopen("myeditor.in","r");
  if (fp == NULL) {
    printf("Cannot open input file.\n");
    exit(1);
  }
  /* データの読み出し 最後に'\0'を忘れない*/
  buf_len=0;
  while(1){
    c=fgetc(fp);
    if(c==EOF){
      buffer[buf_len++]='\0';
      break;
    }else{
      buffer[buf_len++]=c;
    }
  }
  fclose(fp);

  /* コマンド入力のためのループ */
  while(1){
    status = scanf("%s",query);
    if(status!=1) break;

    /* それぞれのコマンドのチェック */
    if(strcmp("print",query)==0){
      printf("%s\n",buffer);
      continue;
    }else if(strcmp("insert",query)==0){
      if(scanf("%d %s",&arg1,query)==2){
	printf("insert(%d, %s)\n",arg1,query);
	continue;
      }
    } /* else ..... と以下同様に他のコマンドもチェックする */
    else if(strcmp("cut",query)==0){
      if(scanf("%d %d",&arg1 ,&arg2)==2){

      }
    }
    else if(strcmp("space",query)==0){
    }
    else if(strcmp("enter",query)==0){
    }
    else if(strcmp("quit",query)==0){
      FILE *fp = fopen("myeditor.out","w");
      fprintf(fp,"%s",buffer);
      fclose(fp);
      exit(7);
    }
    else{
      /* 該当するコマンドが見付からないとき */
      printf("error\n");
      exit(1);
    }
   }

   return 0;
}
