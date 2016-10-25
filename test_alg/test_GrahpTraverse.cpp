#include "test_SortComm.h"


typedef struct
{
	int numVexs = MAXSIZE;
	int vexs[MAXSIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arcs[MAXSIZE][MAXSIZE] = {
					{ 0, 1, 0, 1, 0, 0, 0, 0, 0 },
					{ 1, 0, 1, 0, 1, 0, 0, 0, 1 },
					{ 0, 1, 0, 1, 0, 1, 0, 1, 0 },
				    { 1, 0, 1, 0, 0, 0, 1, 0, 0 },
					{ 0, 1, 0, 0, 0, 1, 0, 0, 1 },
					{ 0, 0, 1, 0, 1, 0, 1, 1, 1 },
					{ 0, 0, 0, 1, 0, 1, 0, 1, 0 },
					{ 0, 0, 1, 1, 0, 1, 1, 0, 0 },
					{ 0, 1, 0, 0, 1, 1, 0, 0, 0 }	
				 };
} TGraph;


bool visited[MAXSIZE];

void InitVisited()
{
	for(int i=0; i<MAXSIZE; i++)
		visited[i]=0;
}

void DFS(TGraph& G, int i)
{
	visited[i] = true;
	printf("visit: %d\n", G.vexs[i]);
	for(int j=0; j<G.numVexs; j++)
		if(G.arcs[i][j] == 1 && !visited[j])
			DFS(G, j);
}

void DFSTraverse(TGraph& G)
{
	for(int i=0; i<G.numVexs; i++)
		if(!visited[i])
			DFS(G, i);
}


int queue[MAXSIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int q_head = 0;
int q_end = 0;
bool empty_flag = true;
bool full_flag = false;
int Deque()
{
	if(empty_flag == false) {
		int elem = queue[q_head];
		queue[q_head] = 0;
		++q_head;
		q_head%=MAXSIZE;
		if(q_head == q_end)
			empty_flag = true;
		if(full_flag = true)
			full_flag = false;
		//printf("deque: %d\n", elem);	
			
		return elem;
	} else
		return -1;
}

int Enque(int i)
{
	if(full_flag == false) {
		queue[q_end] = i;
		++q_end;
		q_end%=MAXSIZE;
		if(q_end == q_head)
			full_flag = true;
		if(empty_flag == true)
			empty_flag = false;
		//printf("enque: %d\n", i);	
		return q_end;
	} else
		return -1;
}

bool Emptyque()
{
	return empty_flag;
}

void BFSTraverse(TGraph& G)
{
	for(int i=0; i<G.numVexs; i++) {
		if(!visited[i]) {
			Enque(i);
			visited[i] = true;
			while(!Emptyque()) {
				i = Deque();
				printf("visit %d\n", G.vexs[i]);
				for(int j=0; j<G.numVexs; j++) 
					if(G.arcs[i][j] == 1 && !visited[j]) {
						Enque(j);
						visited[j] = true;
					}
			}
		} 
	}
}



int main()
{
	TGraph G;
	InitVisited();
	DFSTraverse(G);
	InitVisited();
	BFSTraverse(G);
}



	
