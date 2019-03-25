#include <stdio.h>

char grade_char(int);
int char_point(char);

int main()
{
  int score, unit, sum_unit = 0, gp = 0, total = 0; 
  double gpa = 0.0;
  //score:科目の点数 ,unit:受講科目の単位数 ,sum_unit:単位数の合計 
  //gp:評点 gpa:評価平均点 ,total:評点の合計
  char g;//g:評価
  int status;//ループを抜けるのに用いる 
  while(1)
    {
      printf("点数と単位数を入力してください。: ");
      status = scanf("%d%d",&score ,&unit);
      
      if(status == EOF) break;//C＾Dでループを抜ける

      sum_unit += unit;
      
      g = grade_char(score);
      gp = char_point(g);
      gpa += (double)(gp * unit);
      total += gp;
      printf("%d 点の評価は %c で、評点は %d 点です。(%d 単位)\n\n",score ,g ,gp ,unit);
     }

  printf("\n");
  total = (int)gpa;
  printf("評価平均点 (GPA): %.3f,  単位数: %d\n",gpa / (double)sum_unit ,sum_unit);
  return 0;
}

char grade_char(int score)
{
  if(score >= 0 && score <= 34) return 'F';
  else if(score >= 35 && score <= 49) return 'D';
  else if(score >= 50 && score <= 64) return 'C';
  else if(score >= 65 && score <= 79) return 'B';
  else if(score >= 80 && score <= 100) return 'A';
  else return 'Z';//Zをエラーとして扱う
}

int char_point(char c)
{
  int score;
  
  if(c == 'A') score = 4;
  else if(c == 'B') score = 3;
  else if(c == 'C') score = 2;
  else if(c == 'D') score = 1;
  else if(c == 'F') score = 0;
  else score = -1;//-1をエラーとして扱う

  return score;
}
