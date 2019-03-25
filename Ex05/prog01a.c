#include <stdio.h>
int main()
{
   int i;
   int array[] = {11,22,33,44};
   //int型のためアドレスの間隔は4バイト
   long l_array[] = {111,222,333,444};
   //long型のアドレスの間隔も4バイト
   char c_array[] = {'A','B','C','D'};
   //char型のアドレスの間隔は1バイト
   char *str_array[] = {"a","bc","def","ghijklmn"};
   //Solarisでポインタを用いたアドレスの間隔は4バイト
   double d_array[] = {3e-3, 4e-4, 5e-5, 6e-6};
   //double型のアドレスの間隔は8バイト
   char array_2dc[][10] = {"A","BCDEF","GHI","JK"};
   //1行につきchar型の大きさ1バイトで要素10個分の領域を確保しているので間隔は10バイト 

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %d\n",i,&array[i],array[i]);
   printf("\n%p\n",array);

   printf("\n");

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %d\n",i,&l_array[i],l_array[i]);
   printf("\n%p\n",l_array);

   printf("\n");

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %d\n",i,&c_array[i],c_array[i]);
   printf("\n%p\n",c_array);

   printf("\n");

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %s\n",i,str_array+i,*(str_array+i));
   printf("\n%p\n",str_array);

   printf("\n");

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %f\n",i,&d_array[i],d_array[i]);
   printf("\n%p\n",d_array);

   printf("\n");

   for(i = 0 ; i < 4 ; i++)
     printf( "%d %p %s\n",i,&array_2dc[i],array_2dc[i]);
   printf("\n%p\n",array_2dc);

   return 0;
}
