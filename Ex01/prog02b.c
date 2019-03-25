#include <stdio.h>

int main()
{

  char c;

  printf("文字を入力して下さい: ");
 
  while(1)
{
  scanf("%c",&c);
  if(c == '\n')break;
  printf("文字 %c のアスキーコードは %d(0x%x) です\n",c,c,c);
 }
  return 0;
}
