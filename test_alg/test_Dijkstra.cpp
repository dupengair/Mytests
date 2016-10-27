#include <stdio.h>
#include <algorithm>


const int MAXVEX = 9;
const int INF = 65535;

struct MGraph {
    int numVertexes = MAXVEX;
    int matrix[MAXVEX][MAXVEX] = {{0, 1, 5, INF, INF, INF, INF, INF, INF},
                                {1, 0, 3, 7, 5, INF, INF, INF, INF}, 
                                {5, 3, 0, INF, 1, 7, INF, INF, INF}, 
                                {INF, 7, INF, 0, 2, INF, 3, INF, INF}, 
                                {INF, 5, 1, 2, 0, 3, 6, 9, INF}, 
                                {INF, INF, 7, INF, 3, 0, INF, 5, INF}, 
                                {INF, INF, INF, 3, 6, INF, 0, 2, 7}, 
                                {INF, INF, INF, INF, 9, 5, 2, 0, 4}, 
                                {INF, INF, INF, INF, INF, INF, 7, 4, 0 }};
} ;

typedef int PathMatrix[MAXVEX];
typedef int ShortPathTable[MAXVEX];


void GetPath(PathMatrix& P, int e)
{
	printf("the shortest path v0 -> v%d: v%d", e, e);
	int m = e;
	do {
		m = P[m];
		printf(" <- v%d", m);
	} while(m != 0);
}

void ShortestPath_Dijkstra(MGraph& G, int v0) 
{
    int v, w, k, min;
    PathMatrix P;
    ShortPathTable D;
    int final[MAXVEX];

    for (v = 0; v < G.numVertexes; v++) {
        final[v] = 0;
        D[v] = G.matrix[v0][v];
        P[v] = 0;
    }


    D[v0] = 0;
    final[v0] = 1;
    
    for (v = 1; v < G.numVertexes; v++) {
        printf("round -> %d, D: ", v);
        for(auto v: D) { printf("%d ", v); };
        printf(", P: ");
        for(auto v: P) { printf("%d ", v); };
        
        min = INF;
        for(w = 0; w < G.numVertexes; w++) {
            if (!final[w] && D[w] < min) {
                k = w;
                min = D[w];
             }
        }

        printf(", k = %d, min = %d\n", k, min);
        
        final[k] = 1;
        for(w = 0; w < G.numVertexes; w++) {
            if(!final[w] && (min + G.matrix[k][w] < D[w])) {
                D[w] = min + G.matrix[k][w];
                P[w] = k;
            }
        }
    }


    
    printf("PathMatrix    : ");    
    for(auto v: P) { printf("%d ", v); }
    printf("\nShortPathTable: ");
    for(auto v: D) { printf("%d ", v); }
    printf("\nfinal: ");
    for(auto v: final) { printf("%d ", v); }
    printf("\n");
	GetPath(P, 8);
    printf("\n");
}


int main()
{
    MGraph g;

    ShortestPath_Dijkstra(g, 0);
}

