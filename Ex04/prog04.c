#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARACTER 20 //予想される最大の文字数を設定

int reading(void);
void judge(int);
int search(void);
void output(int);

char str[CHARACTER];



int main(){
  int flag;

  while(1){
    printf("Input a word: ");
    flag = reading();
    judge(flag);
    flag = search();
    output(flag);
    printf("\n");
  }

  return 0;
}

int reading(void){//標準入力からstrへ読み込む
  int flag;
  flag = scanf("%s",str);
  return flag;
}

void judge(int flag){//Ctrl-Dが入力されたらプログラムを終了
  if(flag == EOF){
    printf("\n");
    exit(1);
  }
}

int search(void){//辞書のファイルの中身とstrの値を比較
  int flag = 0;
  char article[CHARACTER];
  FILE *word;

  word = fopen("words.txt","r");

  while(fscanf(word,"%s",article) != EOF){
    if(strcmp(str,article) == 0){
      flag = 1;
      break;
    }
  }

  fclose(word);

  return flag;
}

void output(int flag){
  printf("The word \"%s\" is ",str);
  if(flag == 1)printf("found.\n");
  else printf("NOT found.\n");
}
