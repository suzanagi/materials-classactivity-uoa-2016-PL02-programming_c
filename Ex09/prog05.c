#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NMAX 20                       /* maximum number of buses */
#define NSTOP 6                       /* number of bus stops in data file */
#define UNDEF -999                    /* value for undefined data */

typedef struct{
  char colstr1[8];                    /* label of column 1 */
  char colstr2[8];                    /* label of column 2 */
  char bsname[NSTOP][12];             /* bus stop name */
} Tableinfo;

typedef struct{
  int number;                         /* Number */
  char company[8];                    /* Company */
  int hr[NSTOP];                      /* hour */
  int min[NSTOP];                     /* minute */
} Businfo;

void printInfo(Businfo, Tableinfo);   /* function for displaying results */


int main(int argc, char *argv[]){
  FILE *fp;
  Tableinfo tableinfo;
  Businfo businfo[NMAX];
  int i, j;
  char place[12];
  int from, to , time;

  fp = fopen(argv[1], "r");
  if(fp == NULL){
    printf("file open error\n");
    exit(1);
  }

  fscanf(fp,"%s%s",tableinfo.colstr1 ,tableinfo.colstr2);

  for(i = 0; i < NSTOP; i++)
    fscanf(fp,"%s",tableinfo.bsname[i]);

  /*確認用
  printf("%s\t%s",tableinfo.colstr1 ,tableinfo.colstr2);
  for(i = 0; i < NSTOP; i++)
    printf("%s\t",tableinfo.bsname[i]);
  printf("\n");
  */

  //call
  //fprintf(stderr,"confirmation completed\n");

  for(i = 0; i < NMAX; i++){
    fscanf(fp,"%d%s",&businfo[i].number ,businfo[i].company);

    //call
    //fprintf(stderr,"NSTOP:%d\n",NSTOP);

    for(j = 0; j < NSTOP; j++){
      //call
      //fprintf(stderr,"firstj:%d\n",j);

      fscanf(fp,"%d",&time);

      businfo[i].hr[j] = time / 100;
      businfo[i].min[j] = time % 100;
      //call
      //fprintf(stderr,"now j:%d\n",j);
    }
  }

  //call
  //fprintf(stderr,"time scan completed\n");

  printf("Input the name of bus stop.\n");
  scanf("%s",place);
  printf("Hours from/to?\n");
  scanf("%d%d",&from ,&to);
  printf("\n");

  for(i = 0; i < NSTOP; i++)
    if(strcmp(place, tableinfo.bsname[i]) == 0)
      break;

  for(j = 0; j < NMAX; j++)
    if(businfo[j].hr[i] <= from + 2){
      printInfo(businfo[j], tableinfo);
      printf("\n");
    }

  fclose(fp);

  return 0;
}

void printInfo(Businfo flights, Tableinfo table){
  int i;
  printf("Number: %d\tCompany: %s\n",flights.number ,flights.company);
  for(i = 0; i < NSTOP; i++){
    if(flights.hr[i] == -9) continue;
    printf("%-12s\t%2d:%-2d\n",table.bsname[i] ,flights.hr[i] ,flights.min[i]);
  }
}
