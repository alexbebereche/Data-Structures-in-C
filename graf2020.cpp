#include "stdio.h"
#include "malloc.h"
#include "string.h"

struct Localitate {
	int id;
	char* denumire;
	char* judet;
	int numarLocuitori;
	int suprafata;
	
};

struct ListNode {
	Localitate* info;
	ListNode* next;
};

struct AdjacencyList {
	ListNode* neighbours;
};

struct Graph {
	AdjacencyList* vertices;
	int noVertices;
};

struct NodeBST {
	NodeBST* left;
	Localitate* info;
	NodeBST* right;
};

struct Vector {
	Localitate* *elements = NULL;
	int noEl = 0;
	int dim = 0;
};

void initVector(Vector &v, int dim) {
	v.dim = dim;
	v.noEl = 0;

	v.elements = (Localitate**)malloc(sizeof(Localitate*) * dim);
	memset(v.elements, 0, sizeof(Localitate*) * dim);
}

NodeBST* createNodeBST(Localitate* value)
{
	NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));
	node->info = value;
	node->left = node->right = NULL;
	return node;
}



Localitate* createElement(int id, const char* denumire, const char* judet, int numarLocuitori, int suprafata) {

	Localitate* l = (Localitate*)malloc(sizeof(Localitate));

	l->id = id;

	l->denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(l->denumire, denumire);

	l->judet = (char*)malloc(strlen(judet) + 1);
	strcpy(l->judet, judet);

	l->numarLocuitori = numarLocuitori;
	l->suprafata = suprafata;

	return l;
}

ListNode* createNode(Localitate* l)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->info = l;
	node->next = NULL;
	return node;
}

Graph* initGraph(int noNode) {

	Graph* graph = (Graph*)malloc(sizeof(Graph));

	graph->noVertices = noNode;
	graph->vertices = (AdjacencyList*)malloc(sizeof(AdjacencyList) * graph->noVertices);
	memset(graph->vertices, NULL, sizeof(AdjacencyList) * graph->noVertices);

	return graph;
}

void addEdge(Graph* graph, Localitate* start, Localitate* stop)
{
	ListNode* startN = createNode(start);
	ListNode* stopN = createNode(stop);

	//e.g edge (start:0 - stop:1)
	stopN->next = graph->vertices[start->id - 1].neighbours;
	graph->vertices[start->id - 1].neighbours = stopN;  //devine head?

	//e.g edge (start:1 - stop:0)
	startN->next = graph->vertices[stop->id - 1].neighbours;
	graph->vertices[stop->id - 1].neighbours = startN;
}

//addEdge(graph, localitati[1], localitati[2]);
//addEdge(graph, localitati[2], localitati[3]);
//addEdge(graph, localitati[3], localitati[4]);
//addEdge(graph, localitati[3], localitati[5]);
//addEdge(graph, localitati[4], localitati[5]);
//addEdge(graph, localitati[5], localitati[6]);
//addEdge(graph, localitati[6], localitati[1]);

void printLocalitate(Localitate* l) {
	if (l != NULL) {
		printf("\nId: %d", l->id);
		printf("\nDenumire: %s", l->denumire);
		printf("\nJudet: %s", l->judet);
		printf("\nNumar locuitori: %d", l->numarLocuitori);
		printf("\nSuprafata: %d", l->suprafata);
		printf("\n");
	}
}

void printNode(ListNode* l) {
	printf("\nId: %d", l->info->id);
	printf("\nDenumire: %s", l->info->denumire);
	printf("\nJudet: %s", l->info->judet);
	printf("\nNumar locuitori: %d", l->info->numarLocuitori);
	printf("\nSuprafata: %d", l->info->suprafata);
	printf("\n");
}

void printGraph(Graph* g) {
	for (int i = 0; i < g->noVertices - 1; i++) { //novertices era 7 in main...

		ListNode* crt = g->vertices[i].neighbours;

		printf("\ngraph with id: %d is connected with:", i + 1);
		while (crt != NULL) {
			printNode(crt);

			crt = crt->next;
		}
	}
}

char* *maximConexiuni(Graph* g, Localitate* *localitati, int& nrMax) {

	int c;
	int max = -1;
	int contorMaxim = 0;

	for (int i = 0; i < g->noVertices - 1; i++) { //novertices era 7 in main...


		c = 0;

		ListNode* crt = g->vertices[i].neighbours;
		while (crt != NULL) {

			c++;
			crt = crt->next;
		}

		if (c > max) {
			max = c;
			contorMaxim = 1;
		}
		else if (c == max) {
			contorMaxim++;
		}

		//free


	}

	char* *vector = (char**)malloc(sizeof(char*) * contorMaxim);
	memset(vector, NULL, sizeof(char*) * contorMaxim);
	int j = 0;

	for (int i = 0; i < g->noVertices - 1; i++) { //novertices era 7 in main...


		c = 0;

		ListNode* crt = g->vertices[i].neighbours;
		while (crt != NULL) {

			c++;
			crt = crt->next;
		}

		if (c == max) {
			/*crt = g->vertices[i].neighbours;
			while(crt)*/
			/*vector[j++] = g->vertices[i].neighbours->info->denumire;*/
				/*ListNode* crt = g->vertices[i].neighbours;*/

			//vector[j++] = crt->info->denumire;



			/*ListNode* crt = g->vertices[i].neighbours;
			while (crt->next != NULL) {
				crt = crt->next;
			}
			
			vector[j++] = crt->info->denumire;*/

			/*vector[j++] = g->vertices[i].neighbours->info->denumire;*/


			/*ListNode* crt = g->vertices[i].neighbours;
			while (crt->next != NULL) {
				crt = crt->next;
			}*/

			vector[j++] = localitati[i + 1]->denumire;

		}
		
		

	}

	nrMax = contorMaxim;
	return vector;
}


void insertBST(NodeBST*& root, Localitate* l, char letter)
{
	if (l->denumire[0] == letter) {
		Localitate* value = createElement(l->id, l->denumire, l->judet, l->numarLocuitori, l->suprafata);

		if (root == NULL)
			root = createNodeBST(value);
		else
		{
			if (root->info->suprafata > value->suprafata)
				insertBST(root->left, value, letter);
			else if (root->info->suprafata < value->suprafata)
				insertBST(root->right, value, letter);
			else
				printf("Duplicate key detected, can't insert!");
		}
	}
	else {
		printf("\nlocalitatea %s nu incepe cu litera %c", l->denumire, letter);
	}
}

void inorder(NodeBST* root) {
	if (root != NULL) {

		inorder(root->left);
		printLocalitate(root->info);
		inorder(root->right);

	}
}

int getNrFrunze(NodeBST* root) {
	int nr = 0;

	if (root != NULL) {

		if (root->left == NULL && root->right == NULL) {
			nr++;
		}


		nr += getNrFrunze(root->left);
		nr += getNrFrunze(root->right);
	}

	return nr;
}



//void addVector(Vector &v,NodeBST* root,  Localitate* l) {
//	
//}

Vector extrageFrunze(NodeBST* root) {
	
	Vector v;
	//initVector(v, 0);
	if (root != NULL) {
		int nr = getNrFrunze(root);

		
		initVector(v, nr);

		

		while (v.noEl != v.dim) {
			v = extrageFrunze(root->right);

			if (root->left == NULL && root->right == NULL) {
				/*v.elements[j++] = root->info;*/

				v.elements[v.noEl++] = createElement(root->info->id, root->info->denumire,
					root->info->judet, root->info->numarLocuitori, root->info->suprafata);
				/*v[j++] = root;*/



			}

			v = extrageFrunze(root->left);
			/*v = extrageFrunze(root->right);*/
			/*v = extrageFrunze(root->left);*/
			 //schimb returnul aici...


			return v;
		}
	}
	/*else {
		return v;
	}*/
	
	
	


	
	
}

NodeBST* deleteRoot(NodeBST* &root) {
	NodeBST* node = NULL;
	node = deleteRoot(root->left);

	if (root->left == NULL && root->right == NULL) {
		return root;
	}
	node = deleteRoot(root->right);
}

//void extrage(NodeBST* root, Vector& v) {
//	int nr = getNrFrunze(root);
//	initVector(v, nr);
//	
//
//	int j = 0;
//	while (j != v.dim) {
//		if()
//	}
//}

void main() {
	FILE* pFile = fopen("Data.txt", "r");
	Localitate* *localitati = NULL;
	Graph* graph = NULL;

	if (pFile) {

		int noVertices = 0;
		fscanf(pFile, "%d", &noVertices);
		localitati = (Localitate**)malloc(sizeof(Localitate*) * noVertices);
		memset(localitati, NULL, sizeof(Localitate*) * noVertices);

		graph = initGraph(noVertices + 1);

		int index = 1;
		int id = 0;
		char denumire[100];
		char judet[100];
		int numarLocuri = 0;
		int suprafata = 0;

		while (!feof(pFile)) {
			fscanf(pFile, "%d", &id);
			fscanf(pFile, "%s", denumire);
			fscanf(pFile, "%s", judet);
			fscanf(pFile, "%d", &numarLocuri);
			fscanf(pFile, "%d", &suprafata);

			Localitate* l = createElement(id, denumire, judet, numarLocuri, suprafata);

			localitati[index++] = l;
			//printLocalitate(l);
		}
		//nu uita
		fclose(pFile);

		//nr maxim: 3, 5: cate 3 conexiuni
		addEdge(graph, localitati[1], localitati[2]);
		addEdge(graph, localitati[2], localitati[3]);
		addEdge(graph, localitati[3], localitati[4]);
		addEdge(graph, localitati[3], localitati[5]);
		addEdge(graph, localitati[4], localitati[5]);
		addEdge(graph, localitati[5], localitati[6]);
		addEdge(graph, localitati[6], localitati[1]);

		printGraph(graph);



		//2
		int nrMax = 0;
		char* *vector = maximConexiuni(graph, localitati, nrMax);
		printf("\nOrase cu nr maxim de conexiuni: ");

		for (int i = 0; i < nrMax; i++) {
			printf("\n%s", vector[i]);
		}

		printf("\n-----------------BST----------");

		Localitate* lo = createElement(1, "Buc", "asd", 12, 3);
		NodeBST* root = NULL;
		for (int i = 1; i < noVertices + 1; i++) {  //(1, n + 1) ...asa am scris eu, de-aia imi dadea NULL
			insertBST(root, localitati[i], 'B');
		}

		/*insertbst(root, lo, 'b');*/

		printf("\n---------------Inorder---------");
		inorder(root);

		//for (int i = 0; i < noVertices + 1; i++) {  //+ 1, iau de la 1 la novertices
		//	printLocalitate(localitati[i]);
		//}

		printf("\n---------------Vector---------");

		int nr = getNrFrunze(root);
		printf("\n%d frunze", nr);
		Vector v = extrageFrunze(root);

		for (int i = 0; i < v.dim; i++) {
			printLocalitate(v.elements[i]);
		}


		//printLocalitate(v.elements[0]);
	
	}
}

