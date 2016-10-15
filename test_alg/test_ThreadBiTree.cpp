#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAXSIZE 15
#define DEPTH	4

int a[MAXSIZE] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

typedef enum{ CHILD = 0, THREAD } TTag;

typedef struct BiNode {
    int data;
    struct BiNode *lchild, *rchild;
	TTag ltag;
	TTag rtag;
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


void MidThreading(TBiNode *T)
{
    if(!T) 
		return;
	
	static TBiNode* pre = NULL;	
    MidThreading(T->lchild);
	printf("threading node: %d", T->data);
	if(pre) {
		 if(!T->lchild) {
			 T->ltag = THREAD;
			 T->lchild = pre;
			 printf(", lchild of %d point to pre: %d", T->data, pre->data); 
		 } else 
			 T->ltag = CHILD; 
		 if(!pre->rchild) {
			 pre->rtag = THREAD;
			 pre->rchild = T;
			 printf(", rchild of %d point to next: %d", pre->data, T->data); 
		 } else 
			 T->rtag = CHILD; 
	}
	printf("\n");
	pre = T;
    MidThreading(T->rchild);
}

int main()
{
	TBiNode *btree[MAXSIZE];
	InitBiTree(btree, a);
	MidThreading(btree[0]);
}
