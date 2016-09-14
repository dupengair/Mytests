#include <stdio.h>
#include <stdlib.h>

typedef struct BiNode {
    int data;
    int bf;
    struct BiNode *lchild, *rchild;
}TBiNode;

void L_Rotate(TBiNode **P)
{
    TBiNode *L;
    L = (*P)->rchild;
    (*P)->rchild = L->lchild;
    L->lchild = (*P);
    *P = L;
}


void R_Rotate(TBiNode **P)
{
    TBiNode *L;
    L = (*P)->lchild;
    (*P)->lchild = L->rchild;
    L->rchild = (*P);
    *P = L;
}


#define LH 1
#define EH 0
#define RH -1

void LeftBalance(TBiNode **T)
{
    TBiNode *L, *Lr;
    L = (*T)->lchild;
    switch(L->bf) {
        case LH: 
	    (*T)->bf = L->bf = EH;
	    R_Rotate(T);
	    break;
	case RH:
	    Lr = L->rchild;
	    switch(Lr->bf) {
		case LH:
		    (*T)->bf = RH;
		    L->bf = EH;
		    break;
		case EH:
		    (*T)->bf = L->bf = EH;
		    break;
		case RH:
		    (*T)->bf = EH;
		    L->bf=LH;
		    break;
	    }
	    Lr->bf = EH;
	    L_Rotate(&(*T)->lchild);
	    R_Rotate(T);
	    break;
    }
}


void RightBalance(TBiNode **T)
{
    TBiNode *R, *Rl;
    R = (*T)->rchild;
    switch(R->bf) {
        case RH: 
	    (*T)->bf = R->bf = EH;
	    L_Rotate(T);
	    break;
	case LH:
	    Rl = R->lchild;
	    switch(Rl->bf) {
		case RH:
		    (*T)->bf = LH;
		    R->bf = EH;
		    break;
		case EH:
		    (*T)->bf = R->bf = EH;
		    break;
		case LH:
		    (*T)->bf = EH;
		    R->bf=RH;
		    break;
	    }
	    Rl->bf = EH;
	    R_Rotate(&(*T)->rchild);
	    L_Rotate(T);
	    break;
    }
}

bool InsertAVL(TBiNode **T, int e, bool *taller)
{
    if(!*T) {
	*T = (TBiNode *)malloc(sizeof(TBiNode));
	(*T)->data = e;
	(*T)->lchild = (*T)->rchild = NULL;
	(*T)->bf = EH;
	*taller = true;
    } else {
	if(e == (*T)->data) {
	    *taller = false;
	    return false;
	} else if (e < (*T)->data) {
	    if(!InsertAVL(&(*T)->lchild, e, taller))
		return false;
 	    if(taller) {
		switch((*T)->bf) {
		    case LH:
			LeftBalance(T);
			*taller = false;
			break;
		    case EH:
			(*T)->bf = LH;
			*taller = true;
			break;
		    case RH:
			(*T)->bf = EH;
			*taller = false;
			break;
		}
	    }
	} else {
	    if(!InsertAVL(&(*T)->rchild, e, taller))
		return false;
 	    if(taller) {
		switch((*T)->bf) {
		    case RH:
			RightBalance(T);
			*taller = false;
			break;
		    case EH:
			(*T)->bf = RH;
			*taller = true;
			break;
		    case LH:
			(*T)->bf = EH;
			*taller = false;
			break;
	        }
            }
	}
    }
    return true;	
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
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    TBiNode *T = NULL;
    bool taller;
    for(int i = 0; i < 10; i++) {
	InsertAVL(&T, a[i], &taller);
    } 
    InTraverse(T);
}
