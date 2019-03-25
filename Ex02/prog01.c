#include <stdio.h>

double seqavg(double);

int main()
{
  int status;
  double data;
  double average;

  while(1)
    {
      printf("データを入力して下さい：");
      status = scanf("%lf",&data);

      if(status != 1) break;

      average = seqavg(data);
      printf(" ここまでの平均=%f\n",average);
    }

  printf("\n");
  printf("最終的な平均値は%fです。\n",average);
  
  return 0;
}

double seqavg(double data)
{
  static double average = 0, ncount = 0;

  average = (average * ncount + data) / (ncount + 1);

  ncount++;
  printf("データの個数: %d ",ncount);
  
  return average;
}
