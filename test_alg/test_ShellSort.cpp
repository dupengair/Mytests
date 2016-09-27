#include "test_SortComm.h"

int a[MAXSIZE] = { 9, 1, 5, 8, 3, 7, 4, 6, 2 };

void ShellSort(TList *l)
{
	int i, j;
	int inc = l->length;
	do 
	{
		inc = inc/3 + 1;
		for(i=inc+1; i<=l->length; i++)
		{
			if(l->r[i] < l->r[i-inc])
			{
				l->r[0] = l->r[i];
				for(j=i-inc; j>0&&(l->r[0]<l->r[j]); j-=inc)
					l->r[j+inc] = l->r[j];
				l->r[j+inc] = l->r[0];
			}
		}
	} while(inc > 1);
}

int main()
{
	TList l;
	InitList(&l, a);
	PrintList(&l, "original list: ");
	ShellSort(&l);
	PrintList(&l, "Shell sorted list: ");
}





