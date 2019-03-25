#include <stdio.h>
#include <stdlib.h>
#include "prog03.h"


#ifdef DEBUG /* 単体試験用 */
int main(){
Planet planets[8];
if(input_planet(&planets[0]) == -1) printf("Error has occured\n");
 else printf("return is ok\n");

return 0;
}
#endif


int input_planet (Planet *planets) {
    int i;
    FILE *fp;

    /*ファイルオープン*/
    fp = fopen("planet.txt","r");
    if(fp == NULL){
      printf("cannot open fileplanet.txt\n");
      exit(8);
    }

    for (i = 0; i < NPLANETS; i++) {
      /*ファイルから各データをスキャンし、すべてが正常に格納できなければ
       *(データが異常であれば)-1を返す。 
       */
      if(fscanf(fp,"%s %lf %lf %lf",planets[i].name, &planets[i].radius, &planets[i].density, &planets[i].orbital_radius) != 4) return -1;      
    }

    /*ファイルクローズ*/
    fclose(fp);

    /*正常にデータを格納できたので0を返す*/
    return 0;
}
