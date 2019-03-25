#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define CLASS 4

typedef struct{
  char  sid[8];
  char  sname[10];
  int   score[5];
  char  grade;
  double ave;
} Record;

Record read(void);
void express_and_search(Record);
double average(Record);
char grade_char(int);

int main(int argc, char *argv[]){
  FILE *fpin;
  Record data[SIZE];
  int i,j,status,num,flag;
  char order[12];

  if(argc == 1){
    printf("Error!  Usage: ./a.out datafilename\n");
    exit(8);
  }

  fpin = fopen(argv[1],"r");
  if(fpin == NULL){
    printf("Error!  Can't find file: %s\n",argv[1]);
    exit(1);
  }

  for(i = 0; i < SIZE; i++){
    //sidとsnameを読み込み
    status = fscanf(fpin,"%s%s",data[i].sid ,data[i].sname);
    if(status != 2) break;
    
    for(j = 0; j < CLASS; j++){
      //scoreを読み込み
      fscanf(fpin,"%4d",&data[i].score[j]);
    }

    //aveを算出
    data[i].ave = average(data[i]);

    //gradeを算出
    data[i].grade = grade_char((int)data[i].ave);
  }
  num = i;

  //すべての人のデータを表示
  for(i = 0; i < num; i++){
    express_and_search(data[i]);
  }
  printf("\n");

  //リニアサーチ
  while(1){
    flag = 0;
    //IDまたはnameをうけとる
    printf("Input a student name/ID : ");
    status = scanf("%s",order);
    //Ctrl-Dなら終了
    if(status == EOF) break;
    //IDなのかnameなのか判定する
    if(order[0] > 64 && order[0] < 91){//キーがnameのとき
      //リニアサーチを実行する
      for(i = 0; i < num; i++){
	if(strcmp(data[i].sname,order) == 0){
	  express_and_search(data[i]);
	  flag = 1;
	}
      }
    }
    else if(order[0] > 96 && order[0] < 122){//キーがnameのとき
      //リニアサーチを実行する
      for(i = 0; i < num; i++){
	if(strcmp(data[i].sname,order) == 0){
	  express_and_search(data[i]);
	  flag = 1;
	}
      }
    }
    else if(order[0] > 47 && order[0] < 58){//キーがIDのとき　
      //リニアサーチを実行する
      for(i = 0; i < num; i++){
	if(strcmp(data[i].sid,order) == 0){
	  express_and_search(data[i]);
	  flag = 1;
	}
      }
    }
    else printf("Please search by Name or ID.\n");

  if(flag != 1) printf("This student does not exist !\n");
  }

  printf("\n");

  fclose(fpin);

  return 0;
}

void express_and_search(Record data){
  int i;
  //sidとsnameを出力
  printf("%s  %-8s",data.sid ,data.sname);
  
  //scoreを出力
  for(i = 0; i < CLASS; i++)
    printf("%-4d",data.score[i]);

  //aveを出力
  printf("%3.1f",data.ave);

  //gradeを出力
  printf("\t%c",data.grade);
  printf("\n");
}

double average(Record data){
  double average;
  
  int i;

  average = 0;

  for(i = 0; i < CLASS; i++)
    average += data.score[i];

  average /= CLASS;

  return average;
}

char grade_char(int score){
  if(score >= 0 && score <= 34) return 'F';
  else if(score >= 35 && score <= 49) return 'D';
  else if(score >= 50 && score <= 64) return 'C';
  else if(score >= 65 && score <= 79) return 'B';
  else if(score >= 80 && score <= 100) return 'A';
  else return 'Z';//Zをエラーとして扱う
}
