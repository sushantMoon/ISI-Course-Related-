#include "common.h"
#include "graph.h"

struct Graph* create_graph(int vertices, char type){
    // vertices = toal number of vertices required
    // type : U for undirected graph and D for directed graph 
    // creates a random graph, with total vertices = vertices, 
    // minimum number of edges can be nC2 and maximum number of edges can be n*n
    struct Graph *g = MALLOC(struct Graph, 1);
    g->vertices = vertices;
    g->adjList = MALLOC(struct node*, vertices);
    
    srand(time(0));
    
    int i, j, k, l, edge_present = 0;

    if (type == 'U'){
        // conecting a given vertex to atleast one other vertex which it is nto connected to
        for(i = 0; i < vertices; i++){
            while(edge_present == 0){
                j = i;
                while(j == i){
                    j = rand()%vertices;
                }
                edge_present = add_edge(g, i, j);
                edge_present = add_edge(g, j, i);
            }
            edge_present = 0;
        }
        j = rand()%(UpperLimitEdges(vertices)-LowerLimitEdges(vertices)+1);
        for(i=0; i<j; i++){
            while(edge_present == 0){
                k = 0;
                l = 0;
                while(k == l){
                    k = rand()%vertices;
                    l = rand()%vertices;
                }
                edge_present = add_edge(g, k, l);
                edge_present = add_edge(g, l, k);
            }            
            edge_present = 0;
        }
    }
    else if(type == 'D'){
        // conecting a given vertex to atleast one other vertex which it is nto connected to
        for(i = 0; i < vertices; i++){
            while(edge_present == 0){
                j = i;
                while(j == i){
                    j = rand()%vertices;
                }
                edge_present = add_edge(g, i, j);
            }
            edge_present = 0;
        }
        j = rand()%(UpperLimitEdges(vertices)-LowerLimitEdges(vertices)+1);
        for(i=0; i<j; i++){
            while(edge_present == 0){
                k = 0;
                l = 0;
                while(k == l){
                    k = rand()%vertices;
                    l = rand()%vertices;
                }
                edge_present = add_edge(g, k, l);
            }            
            edge_present = 0;
        }
    }
    return g;
}

int add_edge(struct Graph* g, int vertex_1, int vertex_2){
    int flag = 0;
    struct node **list = g->adjList;
    if (list[vertex_1] == NULL){
        struct node *n = MALLOC(struct node, 1);
        n->vertex = vertex_2;
        n->next = NULL;
        list[vertex_1] = n;
        return 1;
    }
    else{
        struct node *temp = list[vertex_1];
        while(temp != NULL){
            if(temp->vertex == vertex_2){
                flag = 1;
            }
			temp = temp->next;
        }
        if (flag == 0){
            struct node *n = MALLOC(struct node, 1);
            n->vertex = vertex_2;
            n->next = list[vertex_1];
            list[vertex_1] = n;
            return 1;
        }
        else if (flag == 1){
            return 0;
        }
    }
    return 0;
}


void print_graph(struct Graph *g){
    int i = 0;

    for(i=0; i < g->vertices; i++){
        printf("Node %d : ", i);
        struct node* t = g->adjList[i];
        while(t != NULL){
            printf(" %d ", t->vertex);
            t = t->next;
        }
        printf("\n");
    }
}
