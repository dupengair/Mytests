
#include "test_SortComm.h"

int a[MAXSIZE] = { 50, 10, 90, 30, 70, 40, 80, 60, 20 };

typedef int (*TPartFunc)(TList *l, int low, int high);

int Partition(TList *l, int low, int high)
{
	int pivot;
	pivot = l->r[low];

	while(low < high) {
		while(low<high && l->r[high]>=pivot) 
			high--;
		swap(l, low, high);
		while(low<high && l->r[low]<=pivot) 
			low++;
		swap(l, low, high);
	}

	return low;
}

int Partition2(TList *l, int low, int high)
{
	int m = low + (high - low)/2;
	if(l->r[low] > l->r[high])
		swap(l, low, high);
	if(l->r[m] > l->r[high])
		swap(l, high, m);
	if(l->r[low] > l->r[m])
		swap(l, m, low);

	int pivot = l->r[low];

	while(low < high) {
		while(low<high && l->r[high]>=pivot) 
			high--;
		swap(l, low, high);
		while(low<high && l->r[low]<=pivot) 
			low++;
		swap(l, low, high);
	}

	return low;
}

int Partition3(TList *l, int low, int high)
{
	int m = low + (high - low)/2;
	if(l->r[low] > l->r[high])
		swap(l, low, high);
	if(l->r[m] > l->r[high])
		swap(l, high, m);
	if(l->r[low] > l->r[m])
		swap(l, m, low);

	int pivot = l->r[low];
	l->r[0] = pivot;

	while(low < high) {
		while(low<high && l->r[high]>=pivot) 
			high--;
		//swap(l, low, high);
		l->r[low] = l->r[high];
		while(low<high && l->r[low]<=pivot) 
			low++;
		//swap(l, low, high);
		l->r[high] = l->r[low];
	}

	l->r[low] = l->r[0];
	return low;
}

void QSort(TList *l, int low, int high, TPartFunc Partition)
{
	int pivot;
	if(low < high) {
		pivot = Partition(l, low, high);
		
		QSort(l, low, pivot-1, Partition);
		QSort(l, pivot+1, high, Partition);
	}
}
		
void QSort2(TList *l, int low, int high, TPartFunc Partition)
{
	int pivot;
	while(low < high) {
		pivot = Partition(l, low, high);
		
		QSort(l, low, pivot-1, Partition);
		low = pivot + 1;
	}
}

void QuickSort(TList *l)
{
	QSort(l, 1, l->length, Partition);
}



void QuickSort2(TList *l)
{
	QSort(l, 1, l->length, Partition2);
}



void QuickSort3(TList *l)
{
	QSort(l, 1, l->length, Partition3);
}



void QuickSort4(TList *l)
{
	QSort2(l, 1, l->length, Partition3);
}


int main()
{
	TList l;

	InitList(&l, a);
	PrintList(&l, "original list: ");
	QuickSort(&l);
	PrintList(&l, "quick sorted list: ");
	
	InitList(&l, a);
	PrintList(&l, "original list: ");
	QuickSort2(&l);
	PrintList(&l, "quick2 sorted list: ");

	InitList(&l, a);
	PrintList(&l, "original list: ");
	QuickSort3(&l);
	PrintList(&l, "quick3 sorted list: ");
	
	InitList(&l, a);
	PrintList(&l, "original list: ");
	QuickSort4(&l);
	PrintList(&l, "quick4 sorted list: ");
} 
