#include <stdio.h>

int main(void)
{
  int i;
  int *p;
  i = 777;

  p = &i;
  printf("The value of i : %d\n", i); //iに代入されているint型の値
  printf("The address of i : %p\n", &i); //iのアドレス
  printf("The value of pointed by p : %d\n", *p); //ポインタpに示されたiのint型の値
  printf("The value of p : %p\n", p); //pに代入された変数iのアドレス
  printf("The address of p : %p\n", &p); //pのアドレス

  return 0;
}
