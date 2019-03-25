#include <stdio.h>
#include <stdlib.h>
#include "prog04_1.h" /* (1) */
 /* 必要に応じてプログラムを追加、修正 */
 
 int main () { /* (2) */
   /* 必要に応じてプログラムを追加 */
   int status;
   Triangle tri1,tri2;
   Point Centroid1, Centroid2;
   int i;

   /* IsTriangleの結果を元に先へ進むか，InputTriangleで再入力へ */
   while(1){

     /* １番目の三角形の３点を入力する */
     status = InputTriangle(&tri1,1);
     if(status == -1){//入力が異常であれば終了
       printf("\n");
       exit(1);
     }
     
     status = IsTriangle(&tri1);
     if(status == 1) break;
     else printf("These points can not form a triangle!\n");
   }
   
   

   IsTriangle(&tri2);
   /* IsTriangleの結果を元に先へ進むか，InputTriangleで再入力へ */
   while(1){
   /* ２番目の三角形の３点を入力する */
   status = InputTriangle(&tri2,2);
   if(status == -1){//入力が異常であれば終了
     printf("\n");
     exit(1);
   }
     status = IsTriangle(&tri2);
     if(status == 1) break;
   }

   GetTriangleArea(&tri1);
   GetTriangleArea(&tri2);
   
   printf("Area 1: %f\tArea 2: %f\n",tri1.surface ,tri2.surface);
   
   /* 面積の大きい方を表示 */
   if(tri1.surface > tri2.surface){
     printf("Triangle 1 is larger than triangle 2!\n");
   }
   else if(tri2.surface > tri1.surface){
     printf("Triangle 2 is larger than triangle 1!\n");
   }
   else printf("Both triangle have a same surface.");

   Centroid1 = CalcTriangleCentroid(&tri1);
   Centroid2 = CalcTriangleCentroid(&tri2);
   printf("Centroid 1: (%f, %f)\tCentroid 2: (%f, %f)\n",Centroid1.x ,Centroid1.y ,Centroid2.x ,Centroid2.y);

   return 0;
 }
