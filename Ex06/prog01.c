#include <stdio.h>
void swap(int *, int *);

int main()
{
  int x = 777, y = 121;
  printf("start: x=%d\ty=%d\n", x, y);

  /*main側、swap側でそれぞれアドレスを表示し、正しくアドレスが渡されたか確認する*/

  /*main側での変数のアドレスを確認*/
  printf("&x:%p\t&y:%p\n",&x,&y);

  swap(&x, &y);
  printf("end: x=%d\ty=%d\n", x, y);
  
  return 0;
}

void swap(int *p, int *q)
{
  int temp;

  /*swap側で受け取った変数の確認*/
  printf("p(&x):%p\tq(&y):%p\n",p,q);

  printf("p=%d\t q=%d\n",*p,*q);
  temp = *p;
  *p = *q;  
  *q = temp; 
  printf("p=%d\t q=%d\n",*p,*q);
}
