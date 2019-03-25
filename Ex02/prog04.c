#include <stdio.h>
#include <stdlib.h>

#define QLEN 5
#define QEMP -1
#define QFUL -1

int enq(int);
int deq(void);
void listq(void);

/* キューに使用する配列、その他外部変数の宣言 */
int queue[QLEN];
int quenum;//現在キューに入っているデータの数

int main(){

  int order, data;

  while(1){

  /* 処理の入力 */
    printf("1 = enQ/2 = deQ/else = end ==> ");
    scanf("%d",&order);

  /* 入力に従って関数を呼ぶ */
    if(order == 1){
      /* なお、enq()の場合は呼ぶ前に引数入力 */
      printf("Enter enQ data ==> ");
      scanf("%d",&data);

      data = enq(data);

      if(data == QFUL) printf("Q full, you should deQ first!\n");

      //返り値の確認printf("return:%d\n",data);

      listq();
    }
    else if(order == 2){
      /* deq()の場合は呼んだ後にデータ出力   */
      data = deq();
      if(data == QEMP) printf("Q empty, you should enQ first!\n");
      else printf("deQ data : %d\n",data);

      listq();
    }
    else{
      /* 終了の場合はexit()を呼ぶ */
      exit(1);
    }

  }
  return 0;
}

void listq(void){
  int i;

  /* キューが空なら"Queue empty!\n"表示 */
  if(quenum == 0) printf("Queue empty!\n");
  /* 空じゃない場合は並んでいる個数分データ表示 */
  else {
    //確認用printf("quenum:%d\n",quenum);
    printf("Queue :");
    for(i = 0; i < quenum; i++){
      printf(" %d",queue[i]);
    }
    if(quenum == QLEN)
      printf(" Queue full!\n");
    else printf("\n");
  }
}

int enq(int data){

  //値の確認printf("quenum : %d\n",quenum );

  /* キューが満杯ならQFULをreturn*/
  if(quenum == QLEN) return QFUL;
  /* そうでないならキューの最後尾にdataを追加 */
  else{
    queue[quenum] = data;
    quenum++;
    return 0;
  }
}

int deq(void){
  int i, data;

  /* キューが空ならQEMPをreturn*/
  if(quenum == 0) return QEMP;
  /* そうでないならキューの最前列のdataを変数に入れ */
  else{
    data = queue[0];
  /* 後続のデータを一つづつ前に移動させ、変数の値をリターンする */
    for(i = 0; i < quenum; i++){
      queue[i] = queue[i + 1];
    }
    quenum--;
    return data;
  }
}
