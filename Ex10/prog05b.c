#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 20000
#define LOOP 50000

typedef struct {
  int data[N];    /* N個の要素を持つ配列 */
  int maxdata;    /* データの最大値         */
  int mindata;    /* データの最小値         */
  double avedata; /* データの平均値         */
} My_Array;

void FindMember1(My_Array *);
My_Array FindMember2(My_Array);

int main(){
  My_Array A;
  int i;
  time_t start, end;
  double passed;
  
  srand ((unsigned int)time(NULL));
  
  for(i = 0; i < N; i++)
    A.data[i] = rand()%101;
  
  start = clock();
  for(i = 0; i < LOOP; i++)
    FindMember1(&A);
  end = clock();
  passed = (end - start)/(double)CLOCKS_PER_SEC;

  printf("Call by value   : %f sec\n",passed);/*経過時間の表示*/

  start = clock();
  for(i = 0; i < LOOP; i++)
    A = FindMember2(A);
  end = clock(); 
  passed = (end - start)/(double)CLOCKS_PER_SEC;

  printf("Call by address : %f sec\n",passed);/*経過時間の表示*/

  /*bでは値の出力部を取り除く
  printf("Max: %d\n",A.maxdata);
  printf("Min: %d\n",A.mindata);
  printf("Ave: %f\n",A.avedata);
  */ 

  return 0;
}

void FindMember1(My_Array *arr){
  int i;
  arr->avedata = 0.0;
  
  for(i = 0; i < N; i++){
    
    if(arr->data[i] > arr->maxdata)
      arr->maxdata = arr->data[i];
    
    if(arr->data[i] < arr->mindata)  
      arr->mindata = arr->data[i];
    
    arr->avedata += arr->data[i];
  }

  arr->avedata /= N;  

}

My_Array FindMember2(My_Array arr){
  int i;
  arr.avedata = 0.0;
  
  for(i = 0; i < N; i++){
    
    if(arr.data[i] > arr.maxdata)
      arr.maxdata = arr.data[i];
    
    if(arr.data[i] < arr.mindata)  
      arr.mindata = arr.data[i];
    
    arr.avedata += arr.data[i];
  }

  arr.avedata /= N;  

  return arr;
}
