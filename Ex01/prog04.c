#include <stdio.h>

char vowelxchg(char);

int main()
{
  int status;
  char c;

  while(1)
    {
      status = scanf("%c",&c);
      if(status == EOF) break;
      c = vowelxchg(c);
      printf("%c",c);
    }

  return 0;
}

char vowelxchg(char c)
{
  char r;
  if(c == 'a') r = 'A';
  else if(c == 'i')r = 'I';
  else if(c == 'u')r = 'U';
  else if(c == 'e')r = 'E';
  else if(c == 'o')r = 'O';
  else if(c == 'A')r = 'a';
  else if(c == 'I')r = 'i';
  else if(c == 'U')r = 'u';
  else if(c == 'E')r = 'e';
  else if(c == 'O')r = 'o';
  else r = c;

  return r;
}
