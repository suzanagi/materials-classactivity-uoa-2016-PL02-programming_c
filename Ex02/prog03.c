#include <stdio.h>
#define N 10

int func(int);

int main()
{
  int n,r;

  while(1) {
    printf("数値を入力して下さい（正：格納、負：取出）-> ");
    scanf("%d",&n);
    if (n==0) break;
    r=func(n);/* スタックに格納または取出*/
    func(0); /* スタックを表示 */
    if (r>0) printf("取り出したデータ: %d\n",r); /* 取得データの表示 */
    else if (r==-1) printf("エラー（データがありません）\n"); 
    else if (r==-2) printf("エラー（オーバーフロー）\n"); 
  }
  return 0;
}

/* 引数：：正の整数：スタックに格納、負の整数：スタックから取出
　　０：スタックの中身を表示　
戻り値：スタックから取り出した値。取出時スタックが空なら-1,
        格納時スタックがいっぱいのとき-2、表示の際はいつも0 を返す*/
int func(int x)
{
  int i;
  int ojt;/*取り出した値を格納する変数*/
  static int stack[N]; /* スタック本体 */
  static int num=0;  /* データ数 */
  /* 
     numはデータ数であると同時に、スタックの、次にデータを
  　 入れる場所を指している（最初はデータがまだ格納されて
     いないので、初期値は０になる）。
  */

  if(x == 0)//スタックの中身を表示する
    {
      printf("num=%d [",num);
      for(i = 0; i < num; i++)
	{
	  printf("%d ",stack[i]);
	}
      printf("]\n");

      return 0;
    }
  else if(x > 0)//スタックに格納する
    {
      if(num == N)//スタックがいっぱいのとき 
	{
	  return -2;
	}
      else//スタックに正常に格納できるとき
	{
	  stack[num] = x;//スタックに格納
	  num++;

	  return 0;
	}
    }
  else //スタックから取り出す(xの値がマイナス)
    {
      if(num == 0)//スタックが空のとき
	{
	  return -1;
	}
      else//スタックから取出し可能なとき
	{
	  ojt = stack[num - 1];
	  num--;
	  return ojt;
	}
    }

}
