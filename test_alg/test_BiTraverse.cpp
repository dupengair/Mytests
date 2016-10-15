#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAXSIZE 15
#define DEPTH	4

int a[MAXSIZE] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

typedef struct BiNode {
    int data;
    struct BiNode *lchild, *rchild;
}TBiNode;


bool InitBiTree(TBiNode** T, int *a)
{
	for(int i=0; i<MAXSIZE; i++) {
		T[i] = (TBiNode*)malloc(sizeof(TBiNode));
		T[i]->data = a[i];
		T[i]->lchild = NULL;
		T[i]->rchild = NULL;		
	}

	int cnt = 0;
	for(int i=0; i<DEPTH-1; i++)
		for(int j=0; j<pow(2, i); j++) {
			T[cnt]->lchild = T[2*cnt+1];
			T[cnt]->rchild = T[2*cnt+2];
			++cnt;
		}
}

void PreTraverse(TBiNode *T)
{
    if(!T) 
		return;
		
    printf("%d ", T->data);
    PreTraverse(T->lchild);
    PreTraverse(T->rchild);
}


void MidTraverse(TBiNode *T)
{
    if(!T) 
		return;
		
    MidTraverse(T->lchild);
    printf("%d ", T->data);
    MidTraverse(T->rchild);
}

void PostTraverse(TBiNode *T)
{
    if(!T) 
		return;
		
    PostTraverse(T->lchild);
    PostTraverse(T->rchild);
    printf("%d ", T->data);
}
int main()
{
	TBiNode *btree[MAXSIZE];
	InitBiTree(btree, a);
	printf("Pretraverse: ");
	PreTraverse(btree[0]);
	printf("\n");
	printf("Midtraverse: ");
	MidTraverse(btree[0]);
	printf("\n");
	printf("Posttraverse: ");
	PostTraverse(btree[0]);
	printf("\n");
}
