#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 9

typedef struct 
{
	int r[MAXSIZE + 1];
	int length;
}TList;

inline void swap(TList *l, int i, int j)
{
	int temp = l->r[i];
	l->r[i] = l->r[j];
	l->r[j] = temp;
}

void InitList(TList *l, int a[])
{
	l->r[0] = 0;
	l->length = MAXSIZE;
	for(int i=1; i<MAXSIZE+1; i++)
		l->r[i] = a[i-1];
}

void PrintList(TList *l, const char *s)
{
	if(s)
		printf("%s", s);
	for(int i=1; i<MAXSIZE+1; i++)
		printf("%d ", l->r[i]);
	printf("\n");
}













