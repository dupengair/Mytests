#include <stdio.h>


const int MAXEDGE = 15;
const int MAXVEX = 9;


struct Edge {
    int begin;
    int end;
    int weight;
};

struct MGraph {
    int numVertexes = MAXVEX;
    int numEdges = MAXEDGE;
    struct Edge edges[MAXEDGE] = { {4, 7, 7}, {2, 8, 8}, {0, 1, 10}, {0, 5, 11}, {1, 8, 12}, {3, 7, 16}, {1, 6, 16}, {5, 6, 17}, 
                                                        {1, 2, 18}, {6, 7, 19}, {3, 4, 20}, {3, 8, 21}, {2, 3, 22}, {3, 6, 24}, {4, 5, 26}};
} ;


int Find(int *parent, int f)
{
    bool more = false;
    if(parent[f] > 0) {
        printf("%d", f);
        more = true;
    }

    
    while(parent[f] > 0) {        
        f = parent[f];
        printf("->%d", f);
    }

    if(more)
        printf("\n");
    
    return f;
}

void printall(MGraph& G)
{
    for (int i = 0; i < G.numEdges; i++)
            printf("edge: (%d, %d, %d)\n", G.edges[i].begin, G.edges[i].end, G.edges[i].weight);
}


void MiniSpanTree_Kruskal(MGraph& G)
{
    int i, n, m;
    int parent[MAXVEX];

    for (i = 0; i < G.numVertexes; i++) 
        parent[i] = 0;
    
    for (i = 0; i < G.numEdges; i++) {
        n = Find(parent, G.edges[i].begin);
        m = Find(parent, G.edges[i].end);

        if (n != m) {
            parent[n] = m;
            printf("[%d] = %d, get edge: (%d, %d, %d)\n", n, m, G.edges[i].begin, G.edges[i].end, G.edges[i].weight);
        } else {
            printf("circulated, drop the edge: (%d, %d, %d)\n", G.edges[i].begin, G.edges[i].end, G.edges[i].weight);
        }
    }
}



int main()
{
    MGraph g;
    
    printall(g);
    MiniSpanTree_Kruskal(g);
}

    

