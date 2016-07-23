#include <stdio.h>
#include<string>

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

typedef int PathMatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
typedef int Table[MAXVEX][MAXVEX];

void print_table(const char* s, const int (&t)[MAXVEX][MAXVEX]);
void print_AllShortestPath(const int (&d)[MAXVEX][MAXVEX], const int (&p)[MAXVEX][MAXVEX]);
void print_ShortestPath(const int v, const int w, const int (&d)[MAXVEX][MAXVEX], const int (&p)[MAXVEX][MAXVEX]);

void ShortestPath_Floyd(MGraph& G, int v0) 
{
    int v, w, k;
    PathMatrix P;
    ShortPathTable D;

    for (v = 0; v < G.numVertexes; v++) {
        for(w = 0; w < G.numVertexes; w++) {
            D[v][w] = G.matrix[v][w];
            P[v][w] = w;
        }
    }

    printf("before Floyd:\n");
    print_table("D", D);
    print_table("P", P);

    for (k = 0; k < G.numVertexes; k++) {
        for (v = 0; v < G.numVertexes; v++) {
            for(w = 0; w < G.numVertexes; w++) {
                printf("if(D[%d][%d] > D[%d][%d] + D[%d][%d])\n", v, w, v, k, k, w);
                if(D[v][w] > D[v][k] + D[k][w]) {
                    D[v][w] = D[v][k] + D[k][w];
                    P[v][w] = P[v][k];
                }
            }
            printf("\n");
        }
    }     

    printf("after Floyd:\n");
    print_table("D", D);
    print_table("P", P);

    print_AllShortestPath(D, P);
    print_ShortestPath(1, 8, D, P);
    
}

void print_table(const char* s, const int (&t)[MAXVEX][MAXVEX])
{
    int k, v;

    printf("table %s = {\n", s);
    for (k = 0; k < MAXVEX; k++) {
        for (v = 0; v < MAXVEX; v++) {
            printf("%d, ", t[k][v]);
        }
        printf("\n");
     }
    printf("}\n");
}

void print_AllShortestPath(const int (&d)[MAXVEX][MAXVEX], const int (&p)[MAXVEX][MAXVEX])
{
    int k, v, w;

    for (v = 0; v < MAXVEX; v++) {
        for (w = v+1; w < MAXVEX; w++) {
            printf("v%d - v%d weight: %d,  the shortest path: %d", v, w, d[v][w], v);    
            k = p[v][w];
            while(k!=w) {
                printf(" -> %d", k);
                k = p[k][w];
            }
            printf(" -> %d\n", w);
        }
        printf("\n");
     }
}

void print_ShortestPath(const int v, const int w, const int (&d)[MAXVEX][MAXVEX], const int (&p)[MAXVEX][MAXVEX])
{
    if(v > w)
        return;

    printf("v%d - v%d weight: %d,  the shortest path: %d", v, w, d[v][w], v);    
    int k = p[v][w];
    while(k != w) {
        printf(" -> %d", k);
        k = p[k][w];
    }
    printf(" -> %d\n", w);    
}

int main()
{
    MGraph g;

    ShortestPath_Floyd(g, 0);
}

