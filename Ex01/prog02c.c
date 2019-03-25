#include <stdio.h>

#define TRUE 1
#define FALSE 0

int isAlpha(char);

int main()
{

  char c;

  printf("文字を入力して下さい: ");
 
  while(1)
    {
  scanf("%c",&c);
  if(c == '\n')break;
  printf("文字 %c のアスキーコードは %d(0x%x) で、アルファベット",c,c,c);
  if(isAlpha(c) == TRUE)
    {
      printf("です\n");
    }
  else printf("ではありません\n");
    }
  return 0;
}

int isAlpha(char c)
{
  if(c >= 65 && c <= 122) return TRUE;
  else return FALSE; 
}
