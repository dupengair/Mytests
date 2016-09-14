#include <stdio.h>
#include <stdlib.h>

#define SUCCESS	  1
#define UNSUCCESS 0
#define HASHSIZE 12
#define NULLKEY -32768

typedef struct
{
	int *elem;
	int count;
}THashTbl;

int m = 0;

bool InitHashTable(THashTbl *H)
{
	int i;
	m = HASHSIZE;
	H->count = m;
	H->elem=(int *)malloc(m*sizeof(int));
	if(!H->elem)
		return false;

	for(i=0; i<m; i++)
		H->elem[i] = NULLKEY;
	return true;
}

int Hash(int key)
{
	return key % m;
}

void InsertHash(THashTbl *H, int key)
{
	int addr = Hash(key);
	//printf("original insert %d at: %d\n", key, addr);

	while (H->elem[addr] != NULLKEY) {
		addr = (addr + 1) % m;
		//printf("conflict insert %d at: %d\n", key, addr);
	}
	H->elem[addr] = key;
	
}

bool SearchHash(THashTbl *H, int key, int *addr)
{
	*addr = Hash(key);

	//printf("original search %d at: %d\n", key, *addr);

	while( H->elem[*addr] != key) 
	{
		*addr = (*addr + 1) % m;
		//printf("conflict search %d at: %d\n", key, *addr);
		if( H->elem[*addr] == NULLKEY || *addr == Hash(key))
			return UNSUCCESS;
	}

	//printf("final search %d at: %d\n", key, *addr);

	return SUCCESS;
}


int main()
{
	int a[HASHSIZE] = { 12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34 };
	
	THashTbl h;
	if(InitHashTable(&h) == false)
		printf("init hashtable failed. \n");

	for(int i=0; i<HASHSIZE; i++)
		InsertHash(&h, a[i]);

	int addr = NULLKEY;
	int ret = -1;

	ret = SearchHash(&h, 37, &addr);
	printf("search 37: %s, at: %d\n", ret?"SUCCESS":"FAILED", addr);
	ret = SearchHash(&h, 27, &addr);
	printf("search 27: %s, at: %d\n", ret?"SUCCESS":"FAILED", addr);
}


