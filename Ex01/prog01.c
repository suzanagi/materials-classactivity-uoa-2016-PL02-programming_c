#include <stdio.h>

int main()
{
  char c;
  short s;
  int i;
  long l;
  double d;
  int array[10];

  printf("sizeof(char   ) : %d\n",sizeof(c));
  printf("sizeof(short  ) : %d\n",sizeof(s));
  printf("sizeof(int    ) : %d\n",sizeof(i));
  printf("sizeof(long   ) : %d\n",sizeof(l));
  printf("sizeof(double ) : %d\n",sizeof(d));
  printf("sizeof(array[]) : %d\n",sizeof(array));

  return 0;
}
