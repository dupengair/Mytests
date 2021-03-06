#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 11
int a[MAXSIZE] = {62, 38, 88, 58, 47, 35, 73, 51, 99, 37, 93};

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

bool Delete(TBiNode **p)
{
    TBiNode *q, *s;
    if((*p)->rchild == NULL) {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    } else if((*p)->lchild == NULL) {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    } else {
        q = *p;
        s = (*p)->lchild;
        while(s->rchild) {
            q = s;
            s = s->rchild;
        } 
        (*p)->data = s->data;
        if(q != *p)	
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
        free(s);
    }
}

bool DeleteBST(TBiNode **T, int key)
{
    if(!*T)
        return false;
    else {
	if(key == (*T)->data)
	    return Delete(T);
	else if(key < (*T)->data)
	    return DeleteBST(&(*T)->lchild, key);
	else
	    return DeleteBST(&(*T)->rchild, key);
    }
}

bool CreateBST(TBiNode **T, int *a)
{
    for(int i=0; i<MAXSIZE; i++)
        InsertBST(T, a[i]);
}

int main()
{
    TBiNode *T = NULL;
    CreateBST(&T, a);
    InTraverse(T);
    DeleteBST(&T, 38); 
    InTraverse(T);
}





