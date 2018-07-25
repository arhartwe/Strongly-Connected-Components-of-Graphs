/*
 *  * Name         : Andrew Hartwell
 *  * CruzID       : arhartwe
 *  * Assignment   : pa4
*/


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

typedef struct GraphObj
{
	List *neighbors;
	char *color;
	int *parent;
	int *distance;	
	int order;
	int size;
	int source;

}GraphObj;

Graph newGraph(int n) //Creates a new Graph object
{
	Graph g = malloc(sizeof(GraphObj));
	g->source = NIL;
	g->neighbors = calloc(n+1,sizeof(List));
	for(int i = 1; i <= n; i++)
	{
		g->neighbors[i] = newList();
	}
	g->color = (char *)malloc(sizeof(char)*(n+1));
	g->parent = (int *)calloc(n+1, sizeof(int));
	g->distance = (int *)calloc(n+1, sizeof(int));	
	g->order = n;
	g->size = 0;	
	return (g);
}

void freeGraph(Graph* pG) //Frees all dynamic memory associated with the Graph *pG the sets the handle
	//*pG to NULL
{
	if(pG != NULL && *pG != NULL)
	{
		free((*pG)->distance);
		free((*pG)->parent);
		free((*pG)->color);
		for(int i = 1; i <= ((*pG)->order); i++)
		{
			freeList(&(*pG)->neighbors[i]);
		}
		free((*pG)->neighbors);
		free(*pG);
		*pG = NULL;
	}	
}

int getOrder(Graph G) //Return Graphs order
{
	return G->order;
}

int getSize(Graph G) //Return Graphs size
{
	return G->size;
}

int getSource(Graph G) //Returns source vertex most recently used in function BFS(), or NIL if 
	//BFS has not yet been called
{
	return G->source;
}

int getParent(Graph G, int u) //Returns the parent of vertex u in the Breadth-First tree created by
	//BFS(), or NIL if BFS() has not yet been called
{
	if(1<=u && u<=getOrder(G) && getSource(G) != NIL)
	{
		return G->parent[u];
	}
	else
	{
		return NIL;
	}
}

int getDist(Graph G, int u) //Returns the distance from the most recent BFS source to vertex u, or INF
	//if BFS() has not yet been called
{
	if(u >= 1 && u<=getOrder(G) && getSource(G) != NIL)
	{
		return G->distance[u];
	}
	else
	{
		return INF;
	}
}

void getPath(List L, Graph G, int u) //Appends to the List L the vertices of a shortest path G from 
	//from source to u, or appends to L the value NIL if no such path
	//exists
{
	if(u >= 1 && u <= getOrder(G) && getSource(G) != NIL)
	{
		if(G->source == u)
		{
			append(L, G->source);	
		}
		else if(G->parent[u] == NIL)
		{
			append(L, NIL);
		}
		else
		{
			getPath(L, G, G->parent[u]);
			append(L, u);
		}
	}

}

void makeNull(Graph G) //Deletes all edges of G, restoring it to its original (no edge) state
{
	for(int i = 1; i <= G->order; i++)
	{ 
		clear(G->neighbors[i]);
	}
	G->size = 0;

}

void addEdge(Graph G, int u, int v) //Inserts a new edge joining u to v, i.e. u is added to the 
	//adjacency List of v, and v to the adjacency List of u. 
{
	if(length(G->neighbors[u]) == 0)
	{
		append(G->neighbors[u], v);
		G->size++; 
	}
	if(length(G->neighbors[v]) == 0)
	{
		append(G->neighbors[v], u);
	}

	moveFront(G->neighbors[u]);

	while(v > get(G->neighbors[u]))
	{
		if(length(G->neighbors[u]) == 1)
		{
			append(G->neighbors[u], v);	
			G->size++;
		}
		if(length(G->neighbors[u]) == (index(G->neighbors[u]) + 1))
		{
			append(G->neighbors[u], v);
			G->size++;
		}
		moveNext(G->neighbors[u]);
	}
	if(v < get(G->neighbors[u]))
	{
		insertBefore(G->neighbors[u], v);
		G->size++;
	}

	moveFront(G->neighbors[v]);

	while(u > get(G->neighbors[v]))
	{
		if(length(G->neighbors[v]) == 1)
		{
			append(G->neighbors[v], u);
		}
		if(length(G->neighbors[v]) == (index(G->neighbors[v]) + 1))
		{
			append(G->neighbors[v], u);
		}
		moveNext(G->neighbors[v]);
	}
	if(u < get(G->neighbors[v]))
	{
		insertBefore(G->neighbors[v], u);
	}

}

void addArc(Graph G, int u, int v) //Inserts a new directed edge from u to v, i.e. v is added to the
	//adjacency List of u (but not u to the adjacency List of v)
{                
	if(length(G->neighbors[u]) == 0)
	{
		append(G->neighbors[u], v);
		G->size++;
	}
	moveFront(G->neighbors[u]);

	while(v > get(G->neighbors[u]))
	{
		if(length(G->neighbors[u]) == 1)
		{
			append(G->neighbors[u], v);
			G->size++;
		}
		if(length(G->neighbors[u]) == (index(G->neighbors[u]) + 1))
		{
			append(G->neighbors[u], v);
			G->size++;
		}
		moveNext(G->neighbors[u]);
	}
	if(v < get(G->neighbors[u]))
	{
		insertBefore(G->neighbors[u], v);
		G->size++;
	}

}

void BFS(Graph G, int s) //Runs BFS algorithm on Graph G with source s, setting the color, distance,
	//parent, and source fields of G accordingly.
{

	int x;
	G->source = s;

	for(x = 1; x <= G->order; x++)
	{
		G->color[x] = 'w';
		G->distance[x] = INF;
		G->parent[x] = NIL;
	} 
	G->color[s] = 'g';
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List FIFO = newList();
	append(FIFO, s);

	while(!(isEmpty(FIFO)))
	{
		x = front(FIFO);
		deleteFront(FIFO);	

		for(int t = 1; t <= length(G->neighbors[x]); t++)
		{
			if(t == 1)
			{
				moveFront(G->neighbors[x]);
			}

			int y = get(G->neighbors[x]);
			if(G->color[y] == 'w')
			{
				G->color[y] = 'g';
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(FIFO, y);
			}
			moveNext(G->neighbors[x]);
		}
		G->color[x] = 'b';
	}
	freeList(&FIFO);	
}


void printGraph(FILE* out, Graph G) //Prints the adjacency list representation of G to the file pointed
	//by out.
{	

	for(int i = 1; i <= getOrder(G); i++)
	{
		fprintf(out,"%d: ",i);
		printList(out, G->neighbors[i]);
	}
}
