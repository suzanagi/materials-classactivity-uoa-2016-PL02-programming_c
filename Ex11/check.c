#include <stdio.h>
#include <stdlib.h>
#include "stulist.h"

int main(){
  FILE *fp;
  fp=fopen("Student1.dat","r");
  
  Record ndata;
  Record *n = &ndata;

  fscanf(fp,"%d%s%dA%d%d",&ndata.ID ,&ndata.name ,&ndata.score[0] ,&ndata.score[1] ,&ndata.score[2]);
  printf("ID:%d\n",ndata.ID);

  return 0;
}
