#include "stdio.h"
#include "string.h"
#include "malloc.h"


struct ListNode
{
	int destination;
	ListNode* next;
};

struct AdjacencyList {
	ListNode* neightbours;
};

struct Graph {
	//list of lists or

	//array of lists
	AdjacencyList* list;
	int noVertives;
};

ListNode* createNode(int destination)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	node->destination = destination;
	node->next = NULL;

	return node;
}

void initGraph(Graph* *graph, int noVertices) {

	(*graph) = (Graph*)malloc(sizeof(Graph));

	(*graph)->noVertives = noVertices;

	(*graph)->list = (AdjacencyList*)malloc(sizeof(AdjacencyList) * noVertices);
	/*memset((*graph)->list, NULL, sizeof(AdjacencyList) * noVertices);*/

	for (int i = 0; i < noVertices; i++) {
		/*(*graph)->list->neightbours = NULL;*/
		(*graph)->list[i].neightbours = NULL;
	}

}



void addEgde(Graph* *graph, int source, int destination) {

	ListNode* start = createNode(source);
	ListNode* stop = createNode(destination);

	stop->next = (*graph)->list[source - 1].neightbours;
	(*graph)->list[source - 1].neightbours = stop;  // add and replace head

	//its basically an insertion into a list...
	start->next = (*graph)->list[destination - 1].neightbours;
	(*graph)->list[destination - 1].neightbours = start;
}

// is like level-order binary tree
void BF(int* *mat, int dim, int startVertex) {
	int last = -1, first = 0;

	int* visited = (int*)malloc(sizeof(int)*dim);
	int* queue = (int*)malloc(sizeof(int)*dim);


	memset(visited, 0, sizeof(int)*dim);
	visited[startVertex] = 1;
	queue[++last] = startVertex;

	while (last >= first)
	{
		for (int i = 0; i < dim; i++)
		{
			if (visited[i] == 0 && mat[queue[first]][i] == 1)
			{
				visited[i] = 1;
				queue[++last] = i;
			}
		}
		/*printf("%2d", queue[first++]);*/
		printf("%2d", queue[first++] + 1); //suficient asa...
	}
}


//void DF(int* *mat, int dim, int startVertex) {
//	int last = -1, first = 0;
//	int* visited = (int*)malloc(sizeof(int)*dim);
//	int* stack = (int*)malloc(sizeof(int)*dim);
//
//	memset(visited, 0, sizeof(int)*dim);
//
//
//	visited[startVertex] = 1; //i visit the start vertex
//
//
//	stack[++last] = startVertex;
//
//	while (last >= first)
//	{
//		for (int i = 0; i < dim; i++)
//		{
//
//
//			/*if (visited[i] == 0 && mat[stack[first]][i] == 1)*/
//			if (visited[i] == 0 && mat[stack[first]][i] == 1)
//			{
//				visited[i] = 1;
//				stack[++last] = i;
//			}
//		}
//		/*printf("%2d", queue[first++]);*/
//		printf("%2d", stack[first++] + 1); //suficient asa...
//	}
//
//	
//}

void DFS(int* *mat, int dim, int startVertex)
{
	int last = -1, first = 0;
	int* visited = (int*)malloc(sizeof(int)*dim);
	int* stack = (int*)malloc(sizeof(int)*dim);

	memset(visited, 0, sizeof(int)*dim);


	visited[startVertex] = 1; //i visit the start vertex
	int j;

	printf(" %d->", startVertex + 1);
	for (j = 0; j < dim; j++)
	{
		if (mat[startVertex][j] == 1 && visited[j] == 0)
			DFS(mat, dim, j);
	}
}

void dfs2(int** adj, int s, int dim) {

	int* visited = (int*)malloc(sizeof(int)*dim);
	int* stack = (int*)malloc(sizeof(int)*dim);

	memset(visited, 0, sizeof(int)*dim);

	visited[s] = true;
	for (int i = 0; i < dim; ++i) {
		if (visited[adj[s][i]] == false)
			dfs2(adj, adj[s][i], dim);
	}
}


void main() {
	

	Graph* graph = NULL;
	initGraph(&graph, 6);

	
	addEgde(&graph, 1, 3);
	addEgde(&graph, 1, 5);
	addEgde(&graph, 1, 6);
	addEgde(&graph, 2, 5);
	addEgde(&graph, 3, 6);
	addEgde(&graph, 3, 4);
	addEgde(&graph, 3, 5);
	addEgde(&graph, 4, 5);

	//create adjacency matrix
	int* *adjmat = (int**)malloc(sizeof(int*) * graph->noVertives);
	for (int i = 0; i < graph->noVertives; i++) {
		adjmat[i] = (int*)malloc(sizeof(int) * graph->noVertives);
		memset(adjmat[i], 0, sizeof(int) * graph->noVertives);
	}

	for (int i = 0; i < graph->noVertives; i++) {
		ListNode* tmp = graph->list[i].neightbours;

		while (tmp) {
			adjmat[i][tmp->destination - 1] = 1;
			tmp = tmp->next;
		}
	}

	for (int i = 0; i < graph->noVertives; i++) {
		for (int j = 0; j < graph->noVertives; j++) {
			printf("%2d ", adjmat[i][j]);
		}
		printf("\n");
	}


	printf("\n---BF----\n");
	BF(adjmat, graph->noVertives, 0); // de la primul nod, 1, dar -1

	printf("\n---DF----\n");
	//DF(adjmat, graph->noVertives, 0);
	//dfs2(adjmat, graph->noVertives, 0);


	// is connected
	bool isConnected = 1;
	for (int i = 0; i < graph->noVertives; i++) {
		bool good = 0;
		for (int j = 0; j < graph->noVertives; j++) {
			if (adjmat[i][j] == 1) {
				good = 1;
			}
		}

		if (good == 0) {
			isConnected = 0;
			break;
		}
	}

	if (isConnected) {
		printf("It is connected");
	}
	else {
		printf("Is not connected");
	}
	


}