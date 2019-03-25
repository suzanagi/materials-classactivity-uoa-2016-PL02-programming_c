#include <stdio.h>

int main()
{

  char c;

  printf("文字を入力して下さい: ");
  scanf("%c",&c);

  printf("文字 %c のアスキーコードは %d(0x%x) です\n",c,c,c);

  return 0;
}
