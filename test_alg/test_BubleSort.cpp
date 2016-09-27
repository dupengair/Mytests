#include "test_SortComm.h"

int a[MAXSIZE] = { 9, 1, 5, 8, 3, 7, 4, 6, 2 };

void ImprovedBuble(TList *l)
{
	int i, j;
	bool flag = true;
	for(i=1; i<l->length && flag; i++)
	{
		flag = false;
		for(j=l->length-1; j>=i; j--)
		{
			if(l->r[j] > l->r[j+1])
			{	
				swap(l, j, j+1);
				flag = true;
			}
		}
	}
}

void SimpleBuble(TList *l)
{
	int i, j;
	for(i=1; i<l->length+1; i++)
		for(j=i+1; j<=l->length; j++)
			if(l->r[i] > l->r[j])
				swap(l, i, j);
}

void NormalBuble(TList *l)
{
	int i, j;
	for(i=1; i<l->length; i++)
		for(j=l->length-1; j>=i; j--)
			if(l->r[j] > l->r[j+1])
				swap(l, j, j+1);
}

void NormalBuble2(TList *l)
{
	int i, j;
	for(i=1; i<l->length; i++)
		for(j=1; j<l->length+2-i; j++)
			if(l->r[j] < l->r[j-1])
				swap(l, j, j-1);
}
int main()
{
	TList l;
	InitList(&l, a);
	PrintList(&l, "original list: ");
	ImprovedBuble(&l);
	PrintList(&l, "improved bubble: ");	

	InitList(&l, a);
	PrintList(&l, "original list: ");
	SimpleBuble(&l);
	PrintList(&l, "simple bubble: ");	


	InitList(&l, a);
	PrintList(&l, "original list: ");
	NormalBuble(&l);
	PrintList(&l, "normal bubble: ");	

	InitList(&l, a);
	PrintList(&l, "original list: ");
	NormalBuble2(&l);
	PrintList(&l, "normal bubble2: ");	
}








