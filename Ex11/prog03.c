#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stulist.h"

int main()
{
  int i ,status;
  FILE *fp;
  Record ndata = /*headの初期化に用いる*/
    {
      0000000,
      "NUL",
      0,0,0
    };

  fp = fopen("Student1.dat","r");
  if(fp == NULL) printf("Can not open file: Student1.dat");

  head = make_1node(ndata, NULL);

  while(1){
    status = fscanf(fp,"%d%s%d%d%d",&ndata.ID ,ndata.name,&ndata.score[0], &ndata.score[1], &ndata.score[2]);

    if(status == EOF){
      break;
    }

    insert(ndata);
  }

  fclose(fp);

  listprint();


  while (1){
    printf("Insert new data: (ID name score1 score2 score3) -> ");
    status = scanf("%d%s%d%d%d",&ndata.ID, ndata.name, &ndata.score[0], &ndata.score[1], &ndata.score[2]);
    if(status != 5){
      break;
    }

    if (insert(ndata) == NULL) printf("Data %d is already on the list\n", ndata.ID);
    listprint();
  }

  printf("\n");

  return 0;
}

NodePointer insert(Record keydata)
{/*引数でキーとなる数字を受取り、他にそのキーをもつノードがみつからなければ新しくノードを生成する。*/
  NodePointer p;
  NodePointer newnode;

  if (finditem(keydata.ID) == NULL) {
    newnode = make_1node(keydata, NULL);

    p = head;
    
    while(1){
      if(p->next == NULL) break;
      p = p->next;
    }

    p->next = newnode;

    return newnode;
  }
  else return NULL;
}

void listprint(void)
{/*ノード、headからたどり、ひとつづつキーを表示する。*/
  NodePointer n;
  int i;

  printf("Head -\n");
  for (n = head->next; n != NULL; n = n->next) {
    printf("%10d %-11s ", n->data.ID, n->data.name);
    for(i = 0; i < 3; i++)
      printf(" %d ",n->data.score[i]);
    printf("\n");
  }
  printf("\n");
}

NodePointer finditem(int keydata)
{/*搜すキーを引数で受取り、ノードのキーに一致するものがあればそれが何番目のノードかを返す。*/
  NodePointer n;

  for (n = head; n->next != NULL; n = n->next) {
    if (n->data.ID == keydata) return n;
  }

  return NULL;
}

NodePointer make_1node(Record keydata, NodePointer p)
{/*新しくメモリ領域を確保し、新しいノードを生成する。*/
  NodePointer n;
  int i;

  if ((n = (NodePointer)malloc(sizeof(struct node))) == NULL) {
    printf("Error in memory allocation\n");
    exit(8);
  }

  n->data = keydata;

  n->next = p;

  return n;
}
