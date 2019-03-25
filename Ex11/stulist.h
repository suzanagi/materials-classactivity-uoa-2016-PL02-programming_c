/* struct declaration */

typedef struct{
  int  ID;
  char name[11];
  int score[3];
} Record;

typedef struct node *NodePointer;

struct node {
  Record      data;
  NodePointer next;
};


/* prototype declaration */

NodePointer insert(Record);

NodePointer finditem(int);

void listprint(void);

NodePointer make_1node(Record, NodePointer);



/* Global Variable head */

NodePointer head;
