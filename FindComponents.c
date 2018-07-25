/*
 *  * Name         : Andrew Hartwell
 *  * CruzID       : arhartwe
 *  * Assignment   : pa5
*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char * argv[])
{
	FILE *in, *out;
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	char line[256];
	int nmbrSCC = 0;
	int count = 0;
	int i;
	int first;
	int second;
	List order = newList();
	List SCC = newList();
	Graph T = NULL;

	if(argc != 3)
	{
		printf("Usage %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	fscanf(in, "%d ", &i);
	Graph G = newGraph(i);
	for(int j = 1; j <= i; j++)
	{
		append(order,j);
	}
	while(fgets(line,sizeof(line),in))
	{
		sscanf(line, "%d %d", &first, &second);
		if(first != 0 && second != 0)
		{
			addArc(G, first, second);
		}
	}

	DFS(G, order);
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out,"\n");
	T = transpose(G);
	DFS(T, order);
	moveBack(order);

	while(index(order) != -1)
	{
		if(getParent(T, get(order)) == NIL)
		{
			nmbrSCC++;
		}
		movePrev(order);
	}
	fprintf(out, "G contains %d strongly connected components:\n", nmbrSCC);

	moveBack(order);	
	while(index(order) != -1)
	{


		if(getParent(T, get(order)) != NIL)
		{
			prepend(SCC, get(order));
		}
		else
		{
			prepend(SCC, get(order));
			count++;
			fprintf(out, "Component %d: ", count);
			printList(out,SCC);
			clear(SCC);
		}
		movePrev(order);
	}

	freeGraph(&G);
	freeGraph(&T);
	freeList(&order);
	fclose(in);
	fclose(out);
	return 1;
}	
