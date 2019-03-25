#include <stdio.h>

#define MAX_ST_NUM 50                   /* 学生数の最大値 */
#define MAX_SCORE 110			/* 110点満点 */
int student_id[MAX_ST_NUM];             /* 学籍番号  */
int abs_score[MAX_ST_NUM];              /* 点数 (補正前) */
char abs_grade[MAX_ST_NUM];             /* 補正前の評価 (A - F) */
int rel_score[MAX_ST_NUM];              /* 点数 (補正後) */
char rel_grade[MAX_ST_NUM];             /* 補正後の評価 (A - F) */
int grade_dist[2][5];                   /* 評価の分布 [0]:補正前, [1] 補正後 */
                                        /* 例 grade_dist[0][0] 補正前の Fの人数 */
char cgrade[5]={'F','D','C','B','A'};   /* 評価文字（評価点数と対応している） */
int num_student;                        /* 実際に成績を読み込んだ学生の数 */
double abs_ave=0.0;                     /* 平均点（補正前） */
double rel_ave=0.0;                     /* 平均点（補正後） */


void adjust_score(void);
int calib(int); 
/* 満点の補正を行う。内部では実数で計算し、小数点第１位で四捨五入した整数を返す */
void print_grade(void);/*学生番号と補正前後の点数、評価を出力する*/
char grade_char(int);/*点数から評価を算出する*/
void print_stat(void);/*算出された平均点と評価を出力する*/
void calc_avg(void);/*平均点の算出に用いる*/
void count_distribution(void);/*評価の分布の算出に用いる*/

int main()
{
  int i, status;
  /* 標準入力から学籍番号と点数を読みこむコードをここに書く。 */
  for(i = 0; i < MAX_ST_NUM; i++)
    {
      status = scanf("%d %d",&student_id[i] ,&abs_score[i]);
      //学生番号と補正前点数を読み込んだ
      if(status != 2) break;
      num_student++;
    }

  adjust_score();  /* 点数を補正し、補正後の点数の配列に書きこむ。*/
  count_distribution();
  calc_avg();      /* 補正前・補正後の各学生の評価(A～F)を決定し、それぞれ
                     平均点と評価分布を求める*/
  print_grade();   /* 補正前と後の点数と評価を表示。実行例参照 */
  print_stat();    /* 統計と評価分布を表示。フォーマットは実行例参照 */
  return 0;
}

int calib(int score)/*点数に100/満点をかけ、四捨五入する*/
{
  double mscore;
  //scoreに100/110をかける
  mscore = score * (100.0 / (double)MAX_SCORE);
  
  //小数点以下第一位を四捨五入
  if((int)(mscore * 10)% 10 >= 5) 
    {
      score = (int)mscore + 1;
    }
  else score = (int)mscore;

  return score;
}

void adjust_score(void)
{
  int i;
  for(i = 0; i < num_student; i++)
    {
      abs_grade[i] = grade_char(abs_score[i]);//補正前の評価を決定
      rel_score[i] = calib(abs_score[i]);//補正後の点数を算出
      rel_grade[i] = grade_char(rel_score[i]);//補正後の評価を決定
    }

}

void print_grade(void)
{
  int i;

  printf("ID\t");
  printf("点数 評価 点数 評価\n");
  printf("\t(補正前)  (補正後)\n");
  printf("-------------------------\n");

  for(i = 0; i < num_student; i++)
    {
      printf(" %d %5d %c %5d %c\n",student_id[i] ,abs_score[i] ,abs_grade[i] ,rel_score[i] ,rel_grade[i]);
    }

  printf("-------------------------\n");

}

char grade_char(int score)
{
  if(score >= 0 && score <= 34) return cgrade[0];
  else if(score >= 35 && score <= 49) return cgrade[1];
  else if(score >= 50 && score <= 64) return cgrade[2];
  else if(score >= 65 && score <= 79) return cgrade[3];
  else if(score >= 80) return cgrade[4];
  else return 'Z';//Zをエラーとして扱う
}

void print_stat(void)
{
  int i;
  printf("統計\n");
  printf("学生数 %d人 ",num_student);
  printf("補正前平均点 %4.1lf点 補正後平均点 %4.1lf点\n",abs_ave ,rel_ave);
  printf("評価分布\n");

  printf("補正前");
  for(i = 4; i >= 0; i--)
    {
      printf(" %c %d",cgrade[i] ,grade_dist[0][i]);
    }
  printf("\n");

  printf("補正後");
  for(i = 4; i >= 0; i--)
    {
      printf(" %c %d",cgrade[i] ,grade_dist[1][i]);
    }
  printf("\n");
  
}

void calc_avg(void)
{
  int i;
  int abs_sum = 0, rel_sum = 0;
  for(i = 0; i < num_student; i++)
    {
      abs_sum += abs_score[i];
      rel_sum += rel_score[i];
    }
  abs_ave = (double)abs_sum / num_student;
  rel_ave = (double)rel_sum / num_student;
}

void count_distribution(void)
{
  int i, j;
  char g;
  for(i = 0; i < num_student; i++)
    {
      for(j = 0; j < 5; j++)
	{
	  if(abs_grade[i] == cgrade[j]) grade_dist[0][j]++;
	}
    }

  for(i = 0; i < num_student; i++)
    {
      for(j = 0; j < 5; j++)
	{
	  if(rel_grade[i] == cgrade[j]) grade_dist[1][j]++;
	}
    }
}
