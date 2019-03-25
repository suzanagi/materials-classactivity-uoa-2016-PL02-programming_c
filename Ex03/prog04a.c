#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int main()
{
  char buf[MAX];
  int  i, n, c;
  FILE *fpin, *fpout;

  /* file open */
  fpin = fopen("data.in","r");
  if(fpin == NULL){
    printf("Cannot open file in4.data\n");
    exit(2);
  }

  /* data input */
  for(n = 0 ; n < MAX ; n++){
    c = fgetc(fpin);
    if(c == EOF) break;
    buf[n] = (char)c;
  }
  if(n == MAX){
    printf("Buffer overflow !\n");
    exit(3);
  }

  /*file open */
  fpout = fopen("mydata.out", "w");

  /* data output 逆順に出力　最後の改行は出力しない */
  for(i = n - 2 ; i >= 0 ; i--){
    fputc(buf[i],fpout);
  }
  fprintf(fpout, "\n");

  /* file close */
  fclose(fpin);
  fclose(fpout);



  return 0;

}
