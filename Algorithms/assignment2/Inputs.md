# Format
```
total_vertices total_edges Directed/Undirected
vertex1 vertex2 edge_weight
```

# Graph 0 Undirected Dummy
6 5 0
0 1 0
1 2 0
2 0 0
3 2 0
4 5 0

# DFS/Articulation Point/Bridge

## Graph 1 Undrirected (DFS)
8 11 0
0 1 0
0 2 0
0 4 0
1 2 0
1 5 0
2 3 0
3 5 0
3 4 0
3 6 0
5 7 0
6 7 0

## Graph 2 Directed (DFS)
6 9 1
0 1 0
0 5 0
1 4 0
1 5 0
2 1 0
2 3 0
3 4 0
4 0 0
5 4 0

## Graph 3 Undirected (Articulation Point/Bridge)
10 12 0
0 1 0
0 6 0
5 1 0
5 6 0
2 1 0
2 3 0
2 4 0
3 4 0
6 7 0
7 8 0
8 9 0
7 9 0

## Graph 4 Directed (DFS)
8 13 1
0 1 0
0 2 0
0 5 0
1 4 0
2 3 0
3 0 0
3 7 0
4 5 0
4 6 0
4 7 0
5 1 0
5 6 0
7 6 0

## Graph 5 Undirected (Articulation Point/Bridge)
14 16 0
0 1 0
0 2 0
2 3 0
1 3 0
3 4 0
4 5 0
5 6 0
6 7 0
6 8 0
6 11 0
8 9 0
8 10 0
9 10 0
10 12 0
11 12 0
11 13 0

# SCC

## Graph 6 Directed
12 17 1
0 1 0
3 1 0
1 2 0
1 4 0
2 5 0
4 1 0
4 5 0
4 6 0
5 2 0
5 7 0
6 7 0
6 9 0
7 10 0
8 6 0
9 8 0
10 11 0
11 9 0

## Graph 7 Directed
16 27 1
0 2 0
1 0 0
1 5 0
2 1 0
2 4 0
3 2 0
3 10 0
4 3 0
4 5 0
4 11 0
5 6 0
5 8 0
5 15 0
6 7 0
7 8 0
7 9 0
8 6 0
8 9 0
10 11 0
11 12 0
11 13 0
12 10 0
13 12 0
13 15 0
14 15 0
15 9 0
15 14 0

# Topological

## Graph 8 Directed 
6 6 1
0 2 0
1 0 0
1 3 0
2 4 0
2 5 0
3 2 0

## Graph 9 Directed
8 9 1
0 3 0
1 3 0
1 4 0
2 4 0
2 7 0
3 5 0
3 6 0
3 7 0
4 6 0

# Dijkstras

## Graph 10 Undirected
6 9 0
0 1 14
0 2 9
0 3 7
1 2 2
1 5 9
2 3 10
2 4 11
3 4 15
4 5 6

## Graph 11 Directed
6 9 1
0 1 1
0 3 4
0 2 2
1 3 1
1 4 3
2 3 2
2 5 3
3 4 1
3 5 2

# Kruskal's

## Graph 12 Undirected
10 21 0
0 1 6
0 2 3
0 3 9
1 2 4
1 4 2
1 5 9
2 3 9
2 4 2
2 6 9
3 6 8
3 9 18
4 5 9
4 6 8
5 6 7
5 8 5
5 7 4
6 8 9
6 9 10
7 8 1
7 9 4
8 9 3

##Graph 13 Undirected
6 10 0
0 1 5
0 2 6
0 3 4
1 2 1
1 3 2
2 3 2
2 4 5
2 5 3
3 5 4
4 5 4

## Graph 14 Undirected (Articulation Point)
13 12 0
0 1 0
0 2 0
1 3 0
1 4 0
2 5 0
2 6 0
6 7 0
6 8 0
7 9 0
7 10 0
8 11 0
11 12 0
