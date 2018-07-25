# Strongly-Connected-Components-of-Graphs

This program Takes a file in the form


6  
1 2  
1 3  
2 4  
2 5  
2 6  
3 4  
4 5  
5 6  
0 0  

where the first integer represents the number of vertices of a graph,
and the following pairs up to the set of 0 0 represent the edge 
connections of a directed graph.

The output file will print the adjacency list representation of the
created graph as well as the strongly connected components of G
in topological sorted order.

Files Included
1) List.h               - List header file
2) List.c               - Doubly Linked List ADT
3) Graph.h              - Graph Header file
4) Graph.c              - Graph ADT
5) FindComponents.c     - Program's main. Takes file input and prints to output the
                        - adjaceny list representation and strongly connected components
			- in topological sorted order
6) Makefile             - Makefile to compile all source files
7) README               - Program desription and list of included files
