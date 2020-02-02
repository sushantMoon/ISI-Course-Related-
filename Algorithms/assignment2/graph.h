#ifndef __GRAPH_H__
#define __GRAPH_H__


struct node{
    int vertex;
    struct node* next;
}node;

struct Graph{
    int vertices;
    struct node** adjList;
}Graph;

struct Graph* create_graph(int vertices, char type);
int add_edge(struct Graph* g, int vertex_1, int vertex_2);
void print_graph(struct Graph *g);


#define UpperLimitEdges(vertices) vertices*vertices
#define LowerLimitEdges(vertices) ((vertices*(vertices-1))/2) + 1

#endif //__GRAPH_H__
