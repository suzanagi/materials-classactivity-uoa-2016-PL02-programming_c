#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024
#define INITIAL_NUMBER 11//今回は[Wakamatsu]の文字数の11をいれておく

void initial_set(void);
void output(void);
int input(void);
void coming_brackets(int);
int check(int);
void insert_buffer(int);
void open_space_buff(int);

char buff[BUFFER];//出力する単語を保管しておく配列
int ccount = INITIAL_NUMBER;//buffに現在入っている文字数を保管しておく変数
char coming[BUFFER];//入力された挿入する単語を入れる配列

int main(){
  int insert, flag;
  initial_set();
  while(1){
    output();
    insert = input();
    flag = check(insert);
    if(flag == 1) continue;
    else{
      open_space_buff(insert);
      insert_buffer(insert);
    }
  }

  return 0;
}

void initial_set(void){//buffの初期値に[Wakamatsu]を入れる
  strcpy(buff, "[Wakamatsu]");
}

void output(void){//現在のbuffの内容を出力する
  printf("%s\n",buff);
}

int input(void){//入力を受け付け挿入する位置を返す
  int insert;//挿入する文字列のn番目を受け取る変数
  int i, status;
  int length;//受け取った文字列の大きさを格納する変数

  scanf("%d",&insert);//挿入する位置nを読み込む
  status = scanf("%s",coming);//挿入する文字列を読み込む

  coming_brackets(strlen(coming));

  if(status == EOF) exit(8);//入力がなかったらプログラムを終了
  else return insert;
}

void coming_brackets(int size){//受け取った単語の前後に'[',']'をつける
  int i;

  for(i = size; i >= 0; i--){//null文字も含め1文字ずつ後方にずらす
    coming[i + 1] = coming[i];
  }
  coming[size + 2] = coming[size + 1];//null文字をもう1文字分後方へ

  coming[0] = '[';
  coming[size + 1] = ']';
}

int check(int insert){//おもにエラーチェックなど行う
  int flag = 0;
  int buff_length = strlen(buff);
  int length = buff_length + strlen(coming);  

  if(length > BUFFER - 1){//挿入時に文字数が1023文字を越える場合
    flag = 1;
    printf("error\n");
  }
  else if(insert > buff_length){//insertが保持文字数よりも大きい場合
    flag = 1;
    printf("error\n");
  }
     
  return flag;
}

void insert_buffer(int insert){
  int i = 0, j = 0;
  int length = strlen(coming);
  int place = insert;

  //void open_space_buff(length);

  while(j < length){//空いたスペースに入力された単語を挿入する
    buff[insert + i] = coming[j];
    i++;
    j++;
  }
}

void open_space_buff(int insert){
  int buff_length = strlen(buff);
  int insert_length = strlen(coming);
  int i, j;
  /*確認用
  printf("buff:%d\n",buff_length);
  printf("coming:%d\n",insert_length);
  */

  for(i = insert_length; i > 0; i--){
    for(j = buff_length; j >= insert; j--){
      buff[j + 1] = buff[j];
      buff_length++;
    }
  }

  /*確認用
  printf("after : %s\n",buff);
  */
}
