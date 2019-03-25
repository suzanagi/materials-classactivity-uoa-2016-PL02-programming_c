#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int main()
{
  char buf[MAX];
  int  i, n, c;
  FILE *fp;

  /* file open */
  if((fp = fopen("in4.data","r"))== NULL){
    printf("Cannot open file in4.data\n");
    exit(2);
  }

  /* data input */
  for(n = 0 ; n < MAX ; n++){
    if((c = fgetc(fp)) == EOF) break;
    buf[n] = (char)c;
  }
  if(n == MAX){
    printf("Buffer overflow !\n");
    exit(3);
  }

  /* data output 逆順に出力　最後の改行は出力しない */
  for(i = n - 2 ; i >= 0 ; i--){
    fputc(buf[i],stdout);
  }
  printf("\n");

  /* file close */
  fclose(fp);

  return 0;
}
