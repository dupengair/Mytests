#include "test_SortComm.h"

int a[MAXSIZE] = { 50, 10, 90, 30, 70, 40, 80, 60, 20 };

void Merge(int SR[], int TR[], int i, int m, int n)
{
	int j, k, l;
	for(j=m+1, k=i; i<=m&&j<=n; k++)
	{
		if(SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}

	if(i <= m)
		for(l=0; l<=m-i; l++)
			TR[k+l] = SR[i+l];

	
	if(j <= n)
		for(l=0; l<=n-j; l++)
			TR[k+l] = SR[j+l];
}

void MSort(int SR[], int TR1[], int s, int t)
{
	int m;
	int TR2[MAXSIZE+1];

	if(s == t)
		TR1[s] = SR[s];
	else
	{
		m = (s+t)/2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m+1, t);
		Merge(TR2, TR1, s, m, t);
	}
}


void MergeSort(TList *l)
{
	MSort(l->r, l->r, 1, l->length);
}


void MergePass(int SR[], int TR[], int s, int n)
{
	int i=1;
	int j;

	while(i <= n-2*s+1)
	{
		Merge(SR, TR, i, i+s-1, i+2*s-1);
		i = i+2*s;
	}
	
	if(i < n-s+1)
		Merge(SR, TR, i, i+s-1, n);
	else
		for(j=i; j<=n; j++)
			TR[j] = SR[j];
}


void MergeSort2(TList *l)
{	
	int *TR = (int *)malloc(l->length*sizeof(int));
	int k = 1;
	
	while(k < l->length)
	{
		MergePass(l->r, TR, k, l->length);
		k = 2*k;
		MergePass(TR, l->r, k, l->length);
		k = 2*k;
	}

	free(TR);
}

int main()
{
	TList l;

	InitList(&l, a);
	PrintList(&l, "original list: ");
	MergeSort(&l);
	PrintList(&l, "merge sorted list: ");

	InitList(&l, a);
	PrintList(&l, "original list: ");
	MergeSort2(&l);
	PrintList(&l, "merge sorted list2: ");
	
}









