#include "test_SortComm.h"

int a[MAXSIZE] = { 50, 10, 90, 30, 70, 40, 80, 60, 20 };

void HeapAdjust(TList *l, int s, int m)
{
	int temp, j;
	temp = l->r[s];
	for(j=2*s; j<=m; j*=2)
	{
		if(j<m && (l->r[j] < l->r[j+1]))
			++j;
		if(temp >= l->r[j])
			break;
		l->r[s] = l->r[j];
		s = j;
	}
	l->r[s] = temp;
}


void HeapSort(TList *l)
{
	int i;
	for(i=l->length/2; i>0; i--)
		HeapAdjust(l, i, l->length);
	
	for(i=l->length; i>1; i--)
	{
		swap(l, 1, i);
		HeapAdjust(l, 1, i-1);
	}	
}



int main()
{
	TList l;
	InitList(&l, a);
	PrintList(&l, "original list: ");
	HeapSort(&l);
	PrintList(&l, "heap sorted list: ");
}



