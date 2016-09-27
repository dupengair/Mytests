#include "test_SortComm.h"

int a[MAXSIZE] = { 9, 1, 5, 8, 3, 7, 4, 6, 2 };


void InsertSort(TList *l)
{
	int i, j;
	for(i=2; i<=l->length; i++)
		if(l->r[i] < l->r[i-1])
		{
			l->r[0] = l->r[i];
			for(j=i-1; l->r[j]>l->r[0]; j--)
				l->r[j+1] = l->r[j];
			l->r[j+1] = l->r[0];
		}
}


int main()
{
	TList l;
	InitList(&l, a);
	PrintList(&l, "original list: ");
	InsertSort(&l);
	PrintList(&l, "insert sorted list: ");
}







