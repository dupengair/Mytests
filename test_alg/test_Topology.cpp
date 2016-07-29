#include <stdio.h>
#include <vector>
#include <algorithm>


using std::vector;
using std::for_each;

const int MAXVEX = 14;

typedef vector<vector<int> > TGraphMap;
// In | adjvex
TGraphMap graph = {{0, 11, 5, 4}, {0, 8, 4, 2}, {2, 9, 6, 5}, {0, 13, 2}, {2, 7}, 
                                               {3, 12, 8}, {1, 5}, {2}, {2, 7}, {2, 11, 10}, {1, 13}, {2}, {1, 9}, {2}};


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


GraphAdjList* CreateALGraph(TGraphMap& g) 
{
    GraphAdjList *gl = new GraphAdjList();
    int idx = 0, edges = 0;
    
    for(const auto& i: g) {
        gl->adjList[idx].in = i[0];
        gl->adjList[idx].data = idx;
        if(i.size() > 1) {     
            for_each(i.begin()+1, i.end(), [&](int v){
                edges++;
                if(!gl->adjList[idx].firstedge)
                    gl->adjList[idx].firstedge = new EdgeNode(v, 0);
                else {
                    EdgeNode *e = gl->adjList[idx].firstedge;
                    EdgeNode *prev;
                    while(e) {
                        prev = e;
                        e = e->next;   
                    }
                    e = new EdgeNode(v, 0);
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
            printf(" -> %d", e->adjvex);
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


int TopologicalSort(GraphAdjList *GL)
{
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack = new int [GL->numVertexes];   
    int *result = new int [GL->numVertexes]; 

    printf("begin Topological sort: \n");

    for (i=0; i<GL->numVertexes; i++) 
        if(GL->adjList[i].in == 0) 
            stack[++top] = i;

    {
        printf("\nin stack: ");    
        vector<int> a(stack, stack+GL->numVertexes);
        for_each(a.begin(), a.end(), [](int e){ printf("%d ", e); }); 
        printf("\n");
    }

    while(top != 0) {
        gettop = stack[top--];
        printf("[-%d] %d",gettop, GL->adjList[gettop].data);
        result[count] = gettop;
        count++;
        for(e=GL->adjList[gettop].firstedge; e; e=e->next) {
            printf(" -> %d", e->adjvex);
            k = e->adjvex;
            if(!(--GL->adjList[k].in)) {
                printf(" [+%d] ", k);
                stack[++top] = k;
            }
        }
        
        {
            printf("\nin stack: ");    
            vector<int> a(stack, stack+GL->numVertexes);
            for_each(a.begin(), a.end(), [](int e){ printf("%d ", e); }); 
            printf("\n");
        }
    }

    {
        printf("\nthe topology: ");    
        vector<int> b(result, result+GL->numVertexes);
        for_each(b.begin(), b.end(), [](int e){ printf("%d ", e); }); 
        printf("\n");
    }
            

    if(count < GL->numVertexes)
        printf("the graph has ring!\n");

    delete[] stack;
    delete[] result;
    DestroyALGraph(GL);
    
    return 0;
}

// test no stack function, learned from the kernel kfifo
int ta, tb;
#define t_init(a, b) \
({ \
    int t1 = a; \
    int t2 = b; \
    vector<int> c = { t1, t2, t1, t2, t1, t2 }; \
    for(auto i: c) { \
        printf("a = %d, b = %d\n", t1, t2); \
    } \
    a == 0 ? ta = 1 : ta = t1; \
    b == 0 ? tb = 2 : tb = t2; \
})

int main()
{
    TopologicalSort(CreateALGraph(graph));

    t_init(12, 13);
    printf("ta = %d, tb = %d\n", ta, tb);
}
