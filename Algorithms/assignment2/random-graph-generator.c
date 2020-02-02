#include "common.h"
#include "graph.h"

int main(int argc, char const *argv[])
{
    // First Argument expected is number of vertices 
    // Second aorgument D - Directed Graph OR U - Undirected Graph
    if (argc < 3){
        printf("Use command like :\n\
                ./random-graph-generator 5 U\n\
                This means a Undirected Graph of vertices 5\n");
        return 0;
    }
    int vertices = atoi(argv[1]);
    struct Graph *g = create_graph(vertices, *argv[2]);

    //int i = 0;
    //for(i=0; i<vertices; i++){
    //    printf("Node %d : ", i);
    //    struct node* t = g->adjList[i];
    //    while(t != NULL){
    //        printf(" %d ", t->vertex);
    //        t = t->next;
    //    }
    //    printf("\n");
    //}
	//
	print_graph(g);

    return 0;
}
