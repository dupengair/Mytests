#include <stdio.h>
#include <stdlib.h>

int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};

typedef struct BiNode {
    int data;
    struct BiNode *lchild, *rchild;
}TBiNode;




bool SearchBST(TBiNode *T, int key, TBiNode *f, TBiNode **p)
{
    if(!T) {
	*p = f;
	return false;
    } else if(key == T->data ) {
	*p = T;
        return true;
    } else if(key < T->data) 
	return SearchBST(T->lchild, key, T, p);
   else 
       return SearchBST(T->rchild, key, T, p);
}


bool InsertBST(TBiNode **T, int key)
{
    printf("insert: %d\n", key);

    TBiNode *p, *s;
    if (!SearchBST(*T, key, NULL, &p)) {
	s = (TBiNode*)malloc(sizeof(TBiNode));
	s->data = key;
	s->lchild = s->lchild = NULL;
	if(!p) 
	    *T = s;
	else if(key < p->data)
	    p->lchild = s;
	else
	    p->rchild = s;
	return true;
    } else
	return false;
}

void InTraverse(TBiNode *T)
{
    if(!T) {
       printf("\n");
	return;
    }
    InTraverse(T->lchild);
    printf("%d ", T->data);
    InTraverse(T->rchild);
}

int main()
{
    TBiNode *T = NULL;
    for (int i=0; i<10; i++)
	InsertBST(&T, a[i]);
    InTraverse(T);
}



