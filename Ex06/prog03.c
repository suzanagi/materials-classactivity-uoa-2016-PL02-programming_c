#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int delnum(char *);

int main(int argc, char *argv[]){
  int i;//カウンタ変数
  int charnum;//文字数
  char *array;//動的メモリを確保したポインタ

  for(i = 1; i < argc; i++){
    /*動的メモリ領域の確保*/
    array = (char *)malloc(strlen(argv[i]) * sizeof(char) + 1);
         //+1はnull文字分

    /*確保したメモリ領域に文字列をコピー*/
    strcpy(array,argv[i]);

    /*文字列確認
     *printf("%s\t%p\n",array[i],array[i]);
     */

    /*取り除く前の長さを求め、数字をのぞく前の表示をする*/
    charnum = strlen(array);
    printf("%s(%d) -> ",array ,charnum);

    /*delnumで数字を取り除き長さを求める*/
    charnum = delnum(array);

    /*数字をのぞいたあとの表示をする*/
    printf("%s(%d)\n",array ,charnum);

    /*メモリ領域解放*/
    free(array);
  }
  
  return 0;
}

int delnum(char *arg){
  int i,j;

  for(i = 0; *(arg + i) != '\0'; i++){
    /*文字が数字かどうかの判定*/
    while(*(arg + i) > 47 && *(arg + i) < 58){
      /*文字を１つつめる*/
      for(j = i; *(arg + j) != '\0';j++){
	*(arg + j) = *(arg + j + 1);
      }
    }
  }

  return strlen(arg);
}
