// References
// Graph Structure : https://www.techiedelight.com/graph-implementation-using-stl/
// Articulation point and Bridge : https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/
// 
// Topological Sort : https://en.wikipedia.org/wiki/Topological_sorting
// DSS : https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
// 
// Kruskal  https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
// 
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <climits>
#include <stack>
#include <queue>
#include <algorithm>

#define NONE -1
#define INFINITY INT_MAX

using namespace std;

// data structure to store graph edges
struct Edge{
	int src, dest, weight;
};

// class to represent a graph objects
class Graph{
    public:
        vector< vector< pair<int, int> > > adjList;         // For each pair -> first element : vertex || second element : edge weight
        int total_vertices;
        int type;           // 0 undirected / 1 directed
        vector<Edge> edges;

        // initialization of the graph object
        Graph(vector<Edge> set_of_edges, int total_number_of_vertices, int type_of_graph){
            total_vertices = total_number_of_vertices;
            type = type_of_graph;
            
            adjList.resize(total_vertices);
            for (int i=0; i<set_of_edges.size(); i++){
                adjList[set_of_edges[i].src].push_back( make_pair(set_of_edges[i].dest, set_of_edges[i].weight) );
                if (type == 0){
                    adjList[set_of_edges[i].dest].push_back( make_pair(set_of_edges[i].src, set_of_edges[i].weight) );
                }
                edges.push_back(set_of_edges[i]);
            }

        }

        void printGraph(){
            for (int i = 0; i < total_vertices; i++)
            {
                cout << i << " --> ";
                for(int j = 0; j < adjList[i].size(); j++){
                    cout << adjList[i][j].first << "(" << adjList[i][j].second << ")" << " ";
                }
                cout << endl;
            }
        }
};

class Edge_Comparator_Min_heap{
    public:
        bool operator() (const Edge &e1, const Edge &e2){
            return e1.weight > e2.weight;
        }
};

class Distance_Comparator_Min_heap{
    public:
        bool operator() (const pair<int, int> &p1, const pair<int, int> &p2){
            return p1.first > p2.first;
        }
};

class Post_Visit_Max_heap{
    public:
        bool operator() (const pair<int, int> &p1,const pair<int, int> &p2){
            return p1.second < p2.second;
        }
};

// routine for depth first search of a graph
void DFS_subroutine_type2(Graph *graph, int vertex, vector<int> &visited, vector<int> &previsit, vector<int> &postvisit, vector<int> &dfs_traversal, stack<int> &stack){

    static int counter = 0;
    cout << vertex << " ";
    dfs_traversal.push_back(vertex);
    visited[vertex] = 1;
    ++counter;
    previsit[vertex] = counter;
    vector<int> childern_visied;
    cout << " [ " ;
    for(int j = 0; j < graph->adjList[vertex].size(); j++){
        if (visited[graph->adjList[vertex][j].first] == 0) {
            // only enter if the node is unvisited
            DFS_subroutine_type2(graph, graph->adjList[vertex][j].first, visited, previsit, postvisit, dfs_traversal, stack);
            cout << "  ";
        }
    }
    cout << " ] " ;
    ++counter;
    postvisit[vertex] = counter;    
}

void DFS_subroutine(Graph *graph, int vertex, vector<int> &visited, vector<int> &previsit, vector<int> &postvisit, vector<int> &dfs_traversal){
    static int counter = 0;
    dfs_traversal.push_back(vertex);
    visited[vertex] = 1;
    ++counter;
    previsit[vertex] = counter;
    for(int j = 0; j < graph->adjList[vertex].size(); j++){
        if (visited[graph->adjList[vertex][j].first] == 0) {
            // only enter if the node is unvisited
            DFS_subroutine(graph, graph->adjList[vertex][j].first, visited, previsit, postvisit, dfs_traversal);
        }
    }
    ++counter;
    postvisit[vertex] = counter;
}

void DFS(Graph *graph, int source_vertex){
    vector<int> visited(graph->total_vertices, 0);
    vector<int> dfs_traversal;
    vector<int> previsit(graph->total_vertices, 0);
    vector<int> postvisit(graph->total_vertices, 0);
    stack<int> stack;

    cout << "\t\tDFS Tree : ";
    if (visited[source_vertex] == 0) {
        DFS_subroutine_type2(graph, source_vertex, visited, previsit, postvisit, dfs_traversal, stack);
    }

    for(int i = 0; i < visited.size(); i++){
        if (visited[i] == 0) {
            DFS_subroutine_type2(graph, i, visited, previsit, postvisit, dfs_traversal, stack);
        }
    }
    
    cout << "\n\t\tThe DFS Travesal order is: " ;
    for(int i = 0; i < dfs_traversal.size(); i++){
        cout << dfs_traversal[i] << " ";
    }
    cout << endl;
    
}

// routines for Articulation point
void ArticulationPoint_subroutine(  Graph *graph,
                                    int vertex,
                                    vector<bool> *visited, 
                                    vector<int> *previsit, 
                                    vector<int> *subtree_smallest_previsit, 
                                    vector<int> *parent, 
                                    vector<bool> *articulation_point){
    int dfs_tree_childern = 0;
    static int counter = 0;
    counter++;
    (*visited)[vertex] = true;
    (*previsit)[vertex] = counter;
    (*subtree_smallest_previsit)[vertex] = counter;
    
    for(int i = 0; i < graph->adjList[vertex].size(); i++){
        int adjacent_node = graph->adjList[vertex][i].first;
        if (!(*visited)[adjacent_node]) {
            dfs_tree_childern++;

            (*parent)[adjacent_node] = vertex;

            ArticulationPoint_subroutine(graph, adjacent_node, visited, previsit, subtree_smallest_previsit, parent, articulation_point);
            
            (*subtree_smallest_previsit)[vertex] = min((*subtree_smallest_previsit)[vertex], (*subtree_smallest_previsit)[adjacent_node]);

            // if vertex is the root node with more than two childern in DFS tree
            if ( ((*parent)[vertex] == NONE) && (dfs_tree_childern > 1) ) {
                (*articulation_point)[vertex] = true;
            }
            // for any non root node if any of its subtree's smallest possible previsit node conneceted to it is greater than the vertex's previsit number then vertex is a valid articulation point 
            if( ((*parent)[vertex] != NONE) && ((*subtree_smallest_previsit)[adjacent_node] >= (*previsit)[vertex]) ){
                (*articulation_point)[vertex] = true;
            }
            
        }
        else if(adjacent_node != (*parent)[vertex]){
            (*subtree_smallest_previsit)[vertex] = min(
                                        (*subtree_smallest_previsit)[vertex], 
                                        (*previsit)[adjacent_node]
                                        );
        }
    }
}
 
void ArticulationPoint(Graph *graph){
    vector<bool> visited;        // flag for visited nodes
    vector<int> previsit;       // previsitd number for nodes
    vector<int> subtree_smallest_previsit;      // in the subtree checking if
                                                // there exist any node which is connected to a lower previsit number 
    vector<int> parent;         // parent for a node
    vector<bool> articulation_point;     // if a node is an articulation point then its corresponding enter is set to 1

    visited.resize(graph->total_vertices);
    previsit.resize(graph->total_vertices);
    subtree_smallest_previsit.resize(graph->total_vertices);
    parent.resize(graph->total_vertices);
    articulation_point.resize(graph->total_vertices);

    for(int i = 0; i < visited.size(); i++){
        visited[i] = 0;
        previsit[i] = 0;
        parent[i] = NONE;
        articulation_point[i] = 0;
        subtree_smallest_previsit[i] = INFINITY;
    }

    for(int i = 0; i < graph->total_vertices; i++){
        if (!visited[i]) {
            ArticulationPoint_subroutine(graph, i, &visited, &previsit, &subtree_smallest_previsit, &parent, &articulation_point);
        }
    }
    

    // printing the articulation points
    for(int i = 0; i < articulation_point.size(); i++){
        if(articulation_point[i]){
            cout << "\tVertex - " << i << endl;
        }
    }
}

// routine for Bridge
void Bridge_subroutine( Graph *graph,
                        int vertex,
                        vector<bool> *visited, 
                        vector<int> *previsit, 
                        vector<int> *subtree_smallest_previsit, 
                        vector<int> *parent){
    int dfs_tree_childern = 0;
    static int counter = 0;
    counter++;
    (*visited)[vertex] = true;
    (*previsit)[vertex] = counter;
    (*subtree_smallest_previsit)[vertex] = counter;
    
    for(int i = 0; i < graph->adjList[vertex].size(); i++){
        int adjacent_node = graph->adjList[vertex][i].first;
        if (!(*visited)[adjacent_node]) {
            dfs_tree_childern++;

            (*parent)[adjacent_node] = vertex;

            Bridge_subroutine(graph, adjacent_node, visited, previsit, subtree_smallest_previsit, parent);
            
            (*subtree_smallest_previsit)[vertex] = min((*subtree_smallest_previsit)[vertex], (*subtree_smallest_previsit)[adjacent_node]);

            
            // for any node if any of its subtree's smallest possible previsit node conneceted to it is greater than the vertex's previsit number then that edge between them is valid for bridge 
            if((*subtree_smallest_previsit)[adjacent_node] > (*previsit)[vertex]){
                cout << "\tEdge between vertex " << vertex << " and vertex " << adjacent_node << " " << endl;
            }
            
        }
        else if(adjacent_node != (*parent)[vertex]){
            (*subtree_smallest_previsit)[vertex] = min(
                                        (*subtree_smallest_previsit)[vertex], 
                                        (*previsit)[adjacent_node]
                                        );
        }
    }
}

void Bridge(Graph *graph){
    vector<bool> visited;        // flag for visited nodes
    vector<int> previsit;       // previsitd number for nodes
    vector<int> subtree_smallest_previsit;      // in the subtree checking if
                                                // there exist any node which is connected to a lower previsit number 
    vector<int> parent;         // parent for a node

    visited.resize(graph->total_vertices);
    previsit.resize(graph->total_vertices);
    subtree_smallest_previsit.resize(graph->total_vertices);
    parent.resize(graph->total_vertices);

    for(int i = 0; i < visited.size(); i++){
        visited[i] = 0;
        previsit[i] = 0;
        parent[i] = NONE;
        subtree_smallest_previsit[i] = INFINITY;
    }

    for(int i = 0; i < graph->total_vertices; i++){
        if (!visited[i]) {
            Bridge_subroutine(graph, i, &visited, &previsit, &subtree_smallest_previsit, &parent);
        }
    }
}

// routine for Topological Sort
void TopologicalSort_subroutine_dfs( Graph *graph,
                        int vertex,
                        vector<bool> &visited,
                        vector<int> &departure,
                        int &time){
    
    visited[vertex] = true;
    
    for(int i = 0; i < graph->adjList[vertex].size(); i++){
        int adjacent_node = graph->adjList[vertex][i].first;
        if (!visited[adjacent_node]) {
            TopologicalSort_subroutine_dfs(graph, adjacent_node, visited, departure, time);
        }
    }

    departure[++time] = vertex;
}

bool TopologicalSort_subroutine_is_cyclic_util(Graph *graph, int vertex, vector<bool> &visited, vector<bool> &back_edge_stack){
    if (!visited[vertex]) {
        visited[vertex] = true;
        back_edge_stack[vertex] = true;
        
        for(int i = 0; i < graph->adjList[vertex].size(); i++){
            int adjacent_node = graph->adjList[vertex][i].first;
            if ( visited[adjacent_node]==false && TopologicalSort_subroutine_is_cyclic_util(graph, adjacent_node, visited, back_edge_stack) ) {
                return true;
            }
            else if (back_edge_stack[adjacent_node]) {
                return true;
            }
        }
    }
    // none of the vertex's child has back edge hnce setting vertex's back edge possibility to false 
    back_edge_stack[vertex] = false;
    return false;
}

bool TopologicalSort_subroutine_is_cyclic(Graph *graph){
    vector<bool> visited(graph->total_vertices, false);
    // vector for storing wheter the given vertex's childern (childern : all the nodes in its subtree) have a back edge or not. If back edge exist then cycle exist
    vector<bool> back_edge_stack(graph->total_vertices, false);

    for(int i = 0; i < graph->total_vertices; i++){
        if (TopologicalSort_subroutine_is_cyclic_util(graph, i, visited, back_edge_stack)) {
            return true;
        }
    }
    return false;
}

void TopologicalSort(Graph *graph){
    int time = -1;
    vector<bool> visited(graph->total_vertices, false);
    vector<int> departure(graph->total_vertices, -1);
    // looking for back edges

    
    if (TopologicalSort_subroutine_is_cyclic(graph)){
        cout << "\tNo Topological Sort is possible." << endl;
        return;
    }
    else{
        for(int i = 0; i < graph->total_vertices; i++){
            if (!visited[i]) {
                TopologicalSort_subroutine_dfs(graph, i, visited, departure, time);
            }
        }
        cout << "\t";
        for(int i = graph->total_vertices-1; i >= 0; i--){
            cout << departure[i] << " ";
        }
        cout << endl;
    }
}

// routine for Dijkstra's Shortest path
void print_paths_in_dijktra(vector<int> &parent, int vertex) 
{ 
    if (parent[vertex] != - 1){
        print_paths_in_dijktra(parent, parent[vertex]); 
    }
    printf("%d ", vertex); 
} 

void Dijkstra_shortest_path(Graph *graph, int vertex){
    // pair<distance, vertex>
    // priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > distance_min_heap;
    priority_queue< pair<int, int>, vector< pair<int, int> >, Distance_Comparator_Min_heap > distance_min_heap;
    
    vector<int> distance(graph->total_vertices, INFINITY);
    vector<int> parent(graph->total_vertices, -1);
    distance_min_heap.push(make_pair(0, vertex));

    distance[vertex] = 0;
    // parent[vertex] = -1;

    while(!distance_min_heap.empty()){
        int node = distance_min_heap.top().second;
        distance_min_heap.pop();
        vector< pair<int, int> > set_of_edges = graph->adjList[node];

        for(int i = 0; i < set_of_edges.size(); i++){
            if (distance[set_of_edges[i].first] > distance[node] + set_of_edges[i].second) {
                distance[set_of_edges[i].first] = distance[node] + set_of_edges[i].second;
                distance_min_heap.push(make_pair(distance[set_of_edges[i].first], set_of_edges[i].first));
                parent[set_of_edges[i].first] = node;
            }
        }
    }
    
    for(int i = 0; i < graph->total_vertices; i++){
        if (distance[i] == INFINITY) {
            cout << "\t" << "Vertex:" << i << " Distane:" << "Infinity" << "\tPath :"; 
        }
        else{
            cout << "\t" << "Vertex:" << i << " Distane:" << distance[i]<< "\tPath :"; 
        }
        print_paths_in_dijktra(parent, i);
        cout << endl;
    }
}

// routine for Krushkal's MST
int find_root_of_set_having_vertex(vector<int> &list_of_roots, int vertex){
    // path compression
    while(list_of_roots[vertex] != vertex){
        list_of_roots[vertex] = list_of_roots[list_of_roots[vertex]];
        vertex = list_of_roots[vertex];
    }
    return vertex;
}

void union_of_set(vector<int> &list_of_roots, vector<int> &list_of_ranks_of_roots, int vertex1, int vertex2){
    int vertex1_root = find_root_of_set_having_vertex(list_of_roots, vertex1);
    int vertex2_root = find_root_of_set_having_vertex(list_of_roots, vertex2);

    if (list_of_ranks_of_roots[vertex1_root] > list_of_ranks_of_roots[vertex2_root]) {
        list_of_roots[vertex2_root] = vertex1_root;
    }
    else if(list_of_ranks_of_roots[vertex1_root] < list_of_ranks_of_roots[vertex2_root]) {
        list_of_roots[vertex1_root] = vertex2_root;
    }
    else {
        list_of_roots[vertex2_root] = vertex1_root;
        list_of_ranks_of_roots[vertex1_root]++;
    }
}

void Kruskal_MST(Graph *graph){
        
    priority_queue< Edge, vector<Edge>, Edge_Comparator_Min_heap > edge_min_heap;
    vector<int> list_of_roots(graph->total_vertices, -1);
    vector<int> list_of_ranks_of_roots(graph->total_vertices, 0);
    vector<Edge> edges_in_mst;

    // initially each node is root for the set they belong
    for(int i = 0; i < list_of_roots.size(); i++){
        list_of_roots[i] = i;
    }
    
    // populating the edge min heap
    for(int i = 0; i < graph->edges.size(); i++){
        edge_min_heap.push(graph->edges[i]);
    }
    
    int possibility_of_mst = 1;
    while(edges_in_mst.size() < graph->total_vertices-1){
        if (edge_min_heap.empty()){
            possibility_of_mst = 0;
            break;
        }

        Edge e = edge_min_heap.top();
        edge_min_heap.pop();
        if(find_root_of_set_having_vertex(list_of_roots, e.src) != find_root_of_set_having_vertex(list_of_roots, e.dest)){
            edges_in_mst.push_back(e);
            union_of_set(list_of_roots, list_of_ranks_of_roots, e.src, e.dest);
        }
    }

    if (possibility_of_mst == 0) {
        cout << "MST is not possible" << endl;
        return;
    }
    
    for(int i = 0; i < edges_in_mst.size(); i++){
        cout << "Edge : (" << edges_in_mst[i].src << "," << edges_in_mst[i].dest << ") Weight : " << edges_in_mst[i].weight << endl;
    }
}

// routine for Strongly Connected Components
void Strongly_Connected_Components(Graph *graph, Graph *reverse_graph){
    // to store list of conncted components
    vector< vector<int> > scc;
    // priority queue to get vertices in non increasing order of their post visit in reverse graph
    // in pair<int, int> pair.first = vertex and pair.second = postvisit number
    priority_queue< pair< int, int >, vector< pair< int, int > >, Post_Visit_Max_heap > postvisit_max_heap;

    // DFS routines on reverse of the graph
    // gets us the sink
    vector<int> visited(reverse_graph->total_vertices, 0);
    vector<int> previsit(reverse_graph->total_vertices, 0);
    vector<int> postvisit(reverse_graph->total_vertices, 0);
    vector<int> dfs_traversal;

    for(int i = 0; i < visited.size(); i++){
        if (visited[i] == 0) {
            DFS_subroutine(reverse_graph, i, visited, previsit, postvisit, dfs_traversal);
        }
    }

    // cout << "Reverse Graph :" << endl;
    // reverse_graph->printGraph();

    for(int i = 0; i < postvisit.size(); i++){
        postvisit_max_heap.push( make_pair(i, postvisit[i]) );
    }
    
    // while(!postvisit_max_heap.empty()){
    //     cout << postvisit_max_heap.top().first << " " << postvisit_max_heap.top().second << endl;
    //     postvisit_max_heap.pop();
    // }

    // clearing out variables
    fill(visited.begin(), visited.end(), 0);
    fill(previsit.begin(), previsit.end(), 0);
    fill(postvisit.begin(), postvisit.end(), 0);
    dfs_traversal.clear();

    while(!postvisit_max_heap.empty()){
        int vertex = postvisit_max_heap.top().first;
        postvisit_max_heap.pop();
        if (visited[vertex] == 0){
            DFS_subroutine(graph, vertex, visited, previsit, postvisit, dfs_traversal);
            scc.push_back(dfs_traversal);
            dfs_traversal.clear();
            fill(previsit.begin(), previsit.end(), 0);
            fill(postvisit.begin(), postvisit.end(), 0);
        }
    }
    
    for(int i = 0; i < scc.size(); i++){
        cout << "\t" << i+1 << " Connected Component has the following vertices:" << endl;
        cout << "\t\t";
        for(int j = 0; j < scc[i].size(); j++){
            cout << scc[i][j] << " ";
        }
        cout << "\n";
    }   
}

int main(int argc, char const *argv[]){


    int problem_number;
    int source_vertex;
    FILE *fp;
    int total_vertices, total_edges, type_of_graph;
    int vertex1, vertex2, edge_weight;

    cout << "# Type of problem being solved :\n\
                \tEnter 1 for DFS \n\
                \tEnter 2 for Strongly Connected Components \n\
                \tEnter 3 for Articulation Point \n\
                \tEnter 4 for Bridge \n\
                \tEnter 5 for Topological Sort \n\
                \tEnter 6 for Dijkstra's Shortest Path \n\
                \tEnter 7 for Kruskal's Spanning Tree \n\
\n\
                \t## Enter you choice of problem : ";
    
    cin >> problem_number;
    
    cout << "Enter total number of vertices : ";
    cin >> total_vertices;
    cout << "Enter total number of edges : ";
    cin >> total_edges;
    cout << "Enter 0 for undirected graph OR 1 for directed graph : ";
    cin >> type_of_graph;

    // clearing out the input file or ceating a new one
    fp = fopen("input_assign2.txt", "w");
    fclose(fp);

    fp = fopen("input_assign2.txt", "a");

    fprintf(fp, "%d %d %d\n", total_vertices, total_edges, type_of_graph);

    cout << "\nNow Edges would be taken, please note the following :\n\
        1. For undirected edge, only one way edge is required. Eg. if there exist an undirected edge between vertex 6 and vertex 7 then only give First-Vertex=6 Second-Vertex=7 as input, (no need of seperately inputting edge 7 to 6 seperately) rest is handled internally.\n\
        2. For Directed graph, enter source vertex and destination vertex as required.\n\
        3. Edge weight has to be provided always, if there is no edge weight needed just give 0 as edge weight.\n\
        4. All the vertex are given with 0-based index ( i.e first vertex is 0 and last vertex is" << total_vertices-1 <<" ).Always bear that in mind when inputting the following edge connecctions\n" << endl;
    for (int i = 0; i < total_edges; i++){
        cout << "\nEnter the details for " << i+1 << "th edge" << endl;
        if (type_of_graph == 1){
            cout << "\tEnter Source-Vertex : ";
            cin >> vertex1;
            cout << "\tEnter Destination-Vertex : ";
            cin >> vertex2;
            cout << "\tEnter Edge Weight (give 0 if not needed for the problem statement) : ";
            cin >> edge_weight;
        }
        else{
            cout << "\tEnter First-Vertex : ";
            cin >> vertex1;
            cout << "\tEnter Second-Vertex : ";
            cin >> vertex2;
            cout << "\tEnter Edge Weight (give 0 if not needed for the problem statement) : ";
            cin >> edge_weight;
        }
        if (vertex1 >= total_vertices || vertex2 >= total_vertices){
            cout << "Invalid entry, terminating the program."<< endl;
            return 0;
        }
        fprintf(fp, "%d %d %d\n", vertex1, vertex2, edge_weight);
    }
    fclose(fp);

    fp = fopen("input_assign2.txt", "r");
    vector<Edge> edges;
    vector<Edge> reverse_edges;

    fscanf(fp, "%d %d %d", &total_vertices, &total_edges, &type_of_graph);

    for(int i=0; i<total_edges; i++){
        Edge *e;
        Edge *r_e;
        e = new Edge[1];
        r_e = new Edge[1];
        fscanf(fp, "%d %d %d", &(e->src), &(e->dest), &(e->weight));
        r_e->src = e->dest;
        r_e->dest = e->src;
        r_e->weight = e->weight;
        edges.push_back(*e);
        reverse_edges.push_back(*r_e);
    }
    
    Graph graph(edges, total_vertices, type_of_graph);
    Graph reverse_graph(reverse_edges, total_vertices, type_of_graph);
    cout << "# The graph provided is : (Displayed in Adjacency List format, and the values in the brackets represent the edge weights)" << endl;
    graph.printGraph();
    
    if (problem_number == 1){
        // DFS Traversal 
        cout << "\tEnter the source vertex (" << " it can be anything from 0 to "<< total_vertices-1 << " ) :";
        cin >> source_vertex;
        cout << "# DFS : \nThe Nodes traveled in order by DFS from Vertex-"<< source_vertex << endl;
        cout << "Note : To read the output, \n\
        1. The opening bracket [ denotes going down the child.\n\
        2. The closing bracket ] denotes going up to the parent.\n\
        3. The nodes printed adjacent to each other without any opened/incomplete bracket between them are siblings.\n\
        4. The order from left to right denote the order in which the nodes are traversed." << endl;
        DFS(&graph, source_vertex);
    }
    else if (problem_number == 2){
        // Strongly Connected Components
        cout << "# Strongly Connected Components : \nThe components are," << endl;
        Strongly_Connected_Components(&graph, &reverse_graph);
    }
    else if (problem_number == 3){
        // Articulation Point
        cout << "# Articulation Points : \nFollowing are the articulation points," << endl;
        ArticulationPoint(&graph);
    }
    else if (problem_number == 4){
        // Bridge
        cout << "# Bridge : \nFollowing are the bridges," << endl;
        Bridge(&graph);
    }
    else if (problem_number == 5){
        // Topological Sort
        cout << "# Topological Sort : \nThe vertices in sorted order are, " << endl;
        TopologicalSort(&graph);
    }
    else if (problem_number == 6){
        // Dijkstras Shortest Path
        cout << "\tEnter the source vertex (" << " it can be anything from 0 to "<< total_vertices-1 << " ) :";
        cin >> source_vertex;
        cout<< "# Dijkstra's Shortest Path for each of the vertex from Source Vertex-" << source_vertex << " are," << endl;
        Dijkstra_shortest_path(&graph, source_vertex);
    }
    else if (problem_number == 7){    
        // Krushkal's MST
        cout << "# Krushkal's MST : \nThe Edges in order are, " << endl;
        Kruskal_MST(&graph);
    }
    else{
        cout << "Entered the wrong input. Terminating the code." << endl;
    }
    
    return 0;
}