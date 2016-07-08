#include <stdio.h>


const int MAXVEX = 9;
const int INF = 65535;

struct MGraph {
    int numVertexes = MAXVEX;
    int arc[MAXVEX][MAXVEX] = {{0, 10, INF, INF, INF, 11, INF, INF, INF},
                                {10, 0, 18, INF, INF, INF, 16, INF, 12}, 
                                {INF, INF, 0, 22, INF, INF, INF, INF, 8}, 
                                {INF, INF, 22, 0, 20, INF, INF, 16, 21}, 
                                {INF, INF, INF, 20, 0, 26, INF, 7, INF}, 
                                {11, INF, INF, INF, 26, 0, 17, INF, INF}, 
                                {INF, 16, INF, INF, INF, 17, 0, 19, INF}, 
                                {INF, INF, INF, 16, 7, INF, 19, 0, INF}, 
                                {INF, 12, 8, 21, INF, INF, INF, INF, 0 }};
} ;


void MiniSpanTree_Prim(MGraph G) {
    int min, i, j, k;
    int adjvex[MAXVEX];
    int lowcost[MAXVEX];

    lowcost[0] = 0;
    adjvex[0] = 0;

    for (i = 1; i < G.numVertexes; i++) {
           lowcost[i] = G.arc[0][i];
           adjvex[i] = 0;
    }

    for (i = 1; i < G.numVertexes; i++) {
        min = INF;

        j = 1; k = 0;
        while(j < G.numVertexes) {
            if(lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                k = j;
                printf("min = %d, k = %d\n", min, k);
            }
            j++;
        }

        printf("(%d, %d)\n", adjvex[k], k);
        lowcost[k] = 0;
        for(j = 1; j < G.numVertexes; j++) 
                printf("before: lowcost[%d] = %d\n", j, lowcost[j]);
        
        for(j = 1; j < G.numVertexes; j++) {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k;
                printf("find: lowcost[%d] = %d, adjvex[%d] = %d\n", j, lowcost[j], j, adjvex[j]);
            }
        }

        for(j = 1; j < G.numVertexes; j++) 
                printf("after: lowcost[%d] = %d\n", j, lowcost[j]);
    }
}

int main() {
    MGraph g;

    MiniSpanTree_Prim(g);
}
