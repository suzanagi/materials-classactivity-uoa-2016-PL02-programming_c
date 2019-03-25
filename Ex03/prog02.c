#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

void toup(void);
void todown(void);
void modify(void);

int num;
char c[MAX];
FILE *fpin, *fpout;

int main(){
  
  int i, status;

  /*ファイルdata.inを読み込み用として開く*/
  fpin = fopen("data.in","r");
  if(fpin == NULL){
    printf("read file open error\n");
    exit(1);
  }

  /*prog02.outを書き込み用ファイルとして開く*/
  fpout = fopen("prog02.out","w");
  if(fpout == NULL){
    printf("write file open error\n");
    fclose(fpin);
    exit(2);
  }

/*data.inの内容を読み込み、文字配列に格納*/
  for(i = 0; i < MAX; i++)
    {
      status = fscanf(fpin,"%c",&c[i]);
      if(status == EOF){
	num = i;
	break;
      }
    } 

  toup();
  todown();
  modify();
  
  fclose(fpout);
  fclose(fpin);
  
  return 0;
}

void toup(void){
  int i;
  /*文字配列の内容を大文字を小文字に変換しながらprog02.outに書き込む*/
  for(i = 0; i < num; i++){
    if(c[i] > 64 && c[i] < 91) fputc(c[i] + 32,fpout);
    else fputc(c[i],fpout);
  }
  fputc('\n',fpout);
}

void todown(void){
  int i;
  /*次に、文字配列の内容を小文字を大文字に変換しながらprog02.outに書き込む*/
  for(i = 0; i < num; i++){
    if(c[i] > 96 && c[i] < 123) fputc(c[i] - 32,fpout);
    else fputc(c[i],fpout);
  }
  fputc('\n',fpout);
}

void modify(void){
  int i;
  /*さらに、文字配列の大文字は小文字に、小文字は大文字に入れ替えしながらprog02.outに書き込む*/
  for(i = 0; i < num; i++){
    if(c[i] > 64 && c[i] < 91) fputc(c[i] + 32,fpout);
    else if(c[i] > 96 && c[i] < 123) fputc(c[i] - 32,fpout);
    else fputc(c[i],fpout);
  }
  fputc('\n',fpout);

}
