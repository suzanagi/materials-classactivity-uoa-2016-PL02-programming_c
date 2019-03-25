#include <stdio.h>

#define N 5

int main()
{
  double arr[N];
  double tmp;//一時的に変数の中身を入れ替えるのに用いる
  double *p,*q,*minptr;


  printf("Please input %d double numbers\n", N);
  for(p = &arr[0]; p < &arr[N]; p++){
    scanf("%lf",p);
  }

  /*入力の確認用コード
  printf("入力確認\n");
  for(p = &arr[0]; p < &arr[N]; p++)
    printf("%f\n", *p);
  */

  for(p = &arr[0]; p < &arr[N]; p++){

    minptr = p;
    for(q = p; q < &arr[N]; q++){
      /*ループ内確認用
      printf("  q: %f\n",*q);
      printf("  minptr: %f\n",*minptr);
      */
      if(*q < *minptr) minptr = q;
      /*ループ内確認用
	printf("  after: %f\n",*minptr);
      */
    }//ここででてきたminptrのアドレスが一番小さいもの
    //minptrのアドレスにpの値を入れ、pのアドレスにminptrの値を入れる(入れ替え)
    tmp = *p;
    *p = *minptr;
    *minptr = tmp;

    /*ここから
    printf("\n現在の配列の状況\n");
    for(i = &arr[0]; i < &arr[N]; i++)
      printf("%f\n", *i);
    printf("\n");
    ここまで確認*/

  }

  /*変更前
    for(i = 0; i < N - 1; i++){//要素を下から順に調べる
    minidx = i;
    for(j = i + 1; j < N; j++){//一番小さい要素を求める
      if(arr[j] < arr[minidx]) minidx = j;
    }
    tmp = arr[i];//入れ替える
    arr[i] = arr[minidx];
    arr[minidx] = tmp;
    }
  */

  printf("Sorted data\n");
  for(p = &arr[0]; p < &arr[N]; p++)
    printf("%f\n", *p);
  return 0;
}
