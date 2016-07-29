#include <stdio.h>
#include <vector>
#include <algorithm>


using std::vector;
using std::for_each;

const int MAXVEX = 10;

typedef vector<vector<vector<int> > > TGraphMap;
// In | adjvex
TGraphMap graph = {{{0, 0}, {2, 4}, {1, 3}}, {{1, 1}, {4, 6}, {3, 5}}, {{1, 2}, {5, 7}, {3, 8}}, {{2, 3}, {4, 3}}, 
                                 {{2, 4}, {7, 4}, {6, 9}}, {{1, 5}, {7, 6}}, {{1, 6}, {9, 2}}, {{2, 7}, {8, 5}}, {{1, 8}, {9, 3}}, {{2, 9}}};


struct EdgeNode {
    int adjvex;
    int weight;
    struct EdgeNode *next;

    EdgeNode(int a, int w): adjvex(a), weight(w), next(NULL) {}
};

struct VertexNode {
    int in;
    int data;
    EdgeNode *firstedge;
};

struct GraphAdjList {
    VertexNode adjList[MAXVEX];
    int numVertexes;
    int numEdges;

    GraphAdjList() {}
    GraphAdjList(int v, int e):numVertexes(v), numEdges(e) {}
};



int *etv, *ltv;
int *stack2;
int top2;

GraphAdjList* CreateALGraph(TGraphMap& g) 
{
    GraphAdjList *gl = new GraphAdjList();
    int idx = 0, edges = 0;
    
    for(const auto& i: g) {
        gl->adjList[idx].in = i[0][0];
        gl->adjList[idx].data = idx;
        if(i.size() > 1) {     
            for_each(i.begin()+1, i.end(), [&](vector<int> v){
                edges++;
                if(!gl->adjList[idx].firstedge)
                    gl->adjList[idx].firstedge = new EdgeNode(v[0], v[1]);
                else {
                    EdgeNode *e = gl->adjList[idx].firstedge;
                    EdgeNode *prev;
                    while(e) {
                        prev = e;
                        e = e->next;   
                    }
                    e = new EdgeNode(v[0], v[1]);
                    prev -> next = e;
                }
            });
        }
        idx++;
    }

    gl->numVertexes = idx;
    gl->numEdges = edges;

    printf("create Graph with %d vertexes, %d edges\n", gl->numVertexes, gl->numEdges);
    for(const auto& a: gl->adjList) {
        printf("vertex: %d, in: %d", a.data, a.in);
        EdgeNode *e = a.firstedge;
        while(e) {
            printf(" -> %d(%d)", e->adjvex, e->weight);
            e = e->next;  
        }
        printf("\n");
    }

    return gl;
}


void DestroyALGraph(GraphAdjList *GL) 
{
    for(const auto& a: GL->adjList) {
        EdgeNode *e = a.firstedge;
        printf("delete vertex: ");
        while(e) {
            printf("%d, ", e->adjvex);
            EdgeNode *n = e;
            e = e->next;  
            delete n;
        }
        printf("\n");
    }
    
}


GraphAdjList* TopologicalSort(GraphAdjList *GL)
{
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;
    int *stack = new int [GL->numVertexes];   
    etv = new int [GL->numVertexes];
    stack2 = new int [GL->numVertexes];
    top2 = 0;
    

    printf("begin Topological sort: \n");

    for (i=0; i<GL->numVertexes; i++) {
        etv[i] = 0;
        if(GL->adjList[i].in == 0) 
            stack[++top] = i;    
    }

    while(top != 0) {
        gettop = stack[top--];
        stack2[top2++] = gettop;
        for(e=GL->adjList[gettop].firstedge; e; e=e->next) {
            k = e->adjvex;
            if(!(--GL->adjList[k].in)) 
                stack[++top] = k;
            printf("etv[%d]: %d weight: %d, etv[%d]: %d, ", gettop, etv[gettop], e->weight, k, etv[k]);
            if((etv[gettop] + e->weight) > etv[k]) 
                etv[k] = etv[gettop] + e->weight;
            printf("etv[%d]=%d\n", k, etv[k]);
        }
    }

    {
        printf("the topology: \n");    
        vector<int> a(etv, etv+GL->numVertexes);
        for_each(a.begin(), a.end(), [](int e){ printf("%d ", e); }); 
        printf("\n");
        vector<int> b(stack2, stack2+GL->numVertexes);
        for_each(b.begin(), b.end(), [](int e){ printf("%d ", e); }); 
        printf("\n");
    }
    

    if(top2 < GL->numVertexes)
        printf("the graph has ring!\n");

    delete[]  stack;    
    return GL;
}

void CriticalPath(GraphAdjList *GL)
{
    EdgeNode *e;
    int i, j, k, gettop;
    int ete, lte;
    ltv = new int [GL->numVertexes];

    printf("begin CriticalPath: \n");
    
    for(i=0; i<GL->numVertexes; i++) 
        ltv[i] = etv[GL->numVertexes-1];

    printf("Step1: \n");
    while(top2 != 0) {        
        gettop = stack2[--top2];
        for(e=GL->adjList[gettop].firstedge; e; e=e->next) {
            printf("ltv[%d]: %d weight: %d, ltv[%d]: %d, ", e->adjvex, ltv[e->adjvex], e->weight, gettop, ltv[gettop]);
            k = e->adjvex;
            if((ltv[k] - e->weight) < ltv[gettop])
                ltv[gettop] = ltv[k] - e->weight;
            printf("etv[%d]=%d\n", gettop, ltv[gettop]);
        }
    }

    printf("Step2: \n");
    for(j=0; j<GL->numVertexes; j++)
        for(e=GL->adjList[j].firstedge; e; e=e->next) {
            k = e->adjvex;
            ete = etv[j];
            lte = ltv[k] - e->weight;
            printf("etv[%d]: %d, ltv[%d]: %d, weight: %d, ete: %d, lte: %d\n", j, etv[j], k, ltv[k], e->weight, ete, lte);
            if(ete == lte)
                printf("-------------------------------------------------------[v%d -> v%d]  length: %d\n", GL->adjList[j].data, GL->adjList[k].data, e->weight);
        }

    delete [] ltv;
    delete [] etv;
    delete [] stack2;
    DestroyALGraph(GL);
}

int main()
{
    CriticalPath(TopologicalSort(CreateALGraph(graph)));
}

