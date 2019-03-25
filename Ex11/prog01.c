#include <stdio.h>
#include <stdlib.h>
#include "prog01.h"

int main()
{
  int i,num;

  printf("[Initial]\n");
  head = make_1node(0, NULL);
  for (i = 1; i <= 9; i++) insert(i);
  listprint();

  printf("[Insert](enter number)\n");
  while (scanf("%d", &num) == 1) {
    if (insert(num) == NULL) printf("Data %d is already on the list\n", num);
    listprint();
  }
  return 0;
}

NodePointer insert(int keydata)
{/*引数でキーとなる数字を受取り、他にそのキーをもつノードがみつからなければ新しくノードを生成する。*/
  NodePointer newnode;

  if (finditem(keydata) == NULL) {
    newnode = make_1node(keydata, head->next);
    head->next = newnode;

    return newnode;
  }
  else return NULL;
}

void listprint(void)
{/*ノード、headからだどり、ひとつづつキーを表示する。*/
  NodePointer n;

  printf("Head");
  for (n = head->next; n != NULL; n = n->next) {
    printf(" - %d", n->key);
  }
  printf("\n");
}

NodePointer finditem(int keydata)
{/*搜すキーを引数で受取り、ノードのキーに一致するものがあればそれが何番目のノードかを返す。*/
  NodePointer n;

  for (n = head; n->next != NULL; n = n->next) {
    if (n->next->key == keydata) return n;
  }

  return NULL;
}

NodePointer make_1node(int keydata, NodePointer p)
{/*新しくメモリ領域を確保し、新しいノードを生成する。*/
  NodePointer n;

  if ((n = (NodePointer)malloc(sizeof(struct node))) == NULL) {
    printf("Error in memory allocation\n");
    exit(8);
  }

  n->key = keydata;
  n->next = p;

  return n;
}
