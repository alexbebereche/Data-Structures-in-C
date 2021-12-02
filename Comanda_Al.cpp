#include "stdio.h"
#include "string.h"
#include "malloc.h"

struct Produs {
	char* denumire;
	int cantitate;
	char* unitate;



};
struct Comanda {
	int id;
	char* denumireClient;
	int nrProduseComanda;
	Produs* *produse; //vezi trainee exam

	char* dataLivrare;
};

struct NodeBST {
	NodeBST* left;

	Comanda* info;

	NodeBST* right;
	/*int balanceFactor = 0;*/  //nu e avl...

};

Produs* createProdus(const char* den, int cantitate, const char* unitate){
	
	Produs* p = (Produs*)malloc(sizeof(Produs));

	p->denumire = (char*)malloc(strlen(den) + 1);
	strcpy(p->denumire, den);

	p->cantitate = cantitate;

	p->unitate = (char*)malloc(strlen(unitate) + 1);
	strcpy(p->unitate, unitate);
	

	return p;
}

Comanda* createComanda(int id, const char* den, int nr, Produs* *produse, const char* data) {
	Comanda* c = (Comanda*)malloc(sizeof(Comanda));

	c->id = id;
	c->denumireClient = (char*)malloc(strlen(den) + 1);
	strcpy(c->denumireClient, den);

	c->nrProduseComanda = nr;

	c->produse = (Produs**)malloc(sizeof(Produs*) * c->nrProduseComanda);
	/*memset(c->produse, NULL, sizeof(Produs*) * c->nrProduseComanda);*/  //eu le faceam de fapt null...
	for (int i = 0; i < nr; i++) {
		c->produse[i] = produse[i];
	}


	c->dataLivrare = (char*)malloc(strlen(data) + 1);
	strcpy(c->dataLivrare, data);


	return c;


	
}

NodeBST* createNodeBST(Comanda* val) {
	NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));

	node->left = node->right = NULL;
	node->info = val;
	/*node->balanceFactor = 0;*/

	return node;


}

//nu e avl...dumbass

//int maxim(int a, int b)
//{
//	return a > b ? a : b;
//}
//
//
//int getHeight(NodeBST* root) {
//
//	if (root != NULL) {
//		return 1 + maxim(getHeight(root->left), getHeight(root->right));
//	}
//	else
//		return 0;
//}
//
//int getBalanceFactor(NodeBST* pivot) {
//	int left, right;
//
//	right = getHeight(pivot->right);
//	left = getHeight(pivot->left);
//
//	return right - left;
//
//}
//
//NodeBST* rightRotation(NodeBST* root) {
//	if (root != NULL) {
//		NodeBST* aux = root->left;
//		root->left = aux->right;
//
//
//	}
//	
//}

void insertBST(NodeBST* &root, Comanda* value) {

	if (root == NULL) {
		root = createNodeBST(value);
	}
	else
	{
		if (value->id < root->info->id) {
			insertBST(root->left, value);
		}
		else if (value->id > root->info->id) {
			insertBST(root->right, value);
		}
		else {
			printf("Duplicate key");
		}
	}


}

//inorder: 
//2

void printComanda(Comanda* root) {
	printf("\nid: %d \ndenumire: %s \nnr produse: %d \ndata livrare: %s \nproduse: ", root->id, root->denumireClient, root->nrProduseComanda, root->dataLivrare); //error
	for (int i = 0; i < root->nrProduseComanda; i++) {
		printf("\ndenumire: %s | cantitate: %d | unitate: %s", root->produse[i]->denumire, root->produse[i]->cantitate, root->produse[i]->unitate);
	}
	printf("\n-----------------\n");

}


void printBST_Inorder(NodeBST* root) {
	if (root != NULL) {
		printBST_Inorder(root->left);
		/*printBST_Inorder(root);*/

		printComanda(root->info);


		printBST_Inorder(root->right);
	}


}


int getSize(NodeBST* root, const char* data) {
	int c = 0;
	if (root != NULL) {
		

		if (strcmp(root->info->dataLivrare, data) == 0) {
			/*vector[i++] = root->info->id;*/
			c++;
		}
		c += getSize(root->left, data);
		c += getSize(root->right, data);
	}

	return c;
}


int* vectorId(NodeBST* root, const char* data) {

	int c = getSize(root, data);
	int* vector = NULL; //...
	vector = (int*)malloc(sizeof(int) * c); //trebuie alocat...


	int i = 0;
	if (root != NULL) {


		if (strcmp(root->info->dataLivrare, data) == 0) {
			vector[i++] = root->info->id;
		}
		vectorId(root->left, data);
		vectorId(root->right, data);


		if (root->left != NULL || root->right != NULL) {

			if (strcmp(root->left->info->dataLivrare, data) == 0) {
				vector[i++] = root->left->info->id;
			}

			if (strcmp(root->right->info->dataLivrare, data) == 0) {
				vector[i++] = root->right->info->id;
			}
		}


	}
	return vector;
}

int nrFrunza(NodeBST* root, const char* client) {
	int  c = 0;
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL && strcmp(root->info->denumireClient, client) == 0) {
			c++;
		}
		else {
			c += nrFrunza(root->left, client);
			c += nrFrunza(root->right, client);
		}
	}
	
	return c;
	

	
}


void main() {
	NodeBST* root = NULL;
	Produs* p1 = createProdus("a", 1, "A");
	Produs* p2 = createProdus("b", 2, "Ab");
	Produs* p3 = createProdus("c", 3, "Ac");
	Produs* p4 = createProdus("d", 4, "Ad");
	Produs* p5 = createProdus("e", 5, "Ae");
	Produs* vector[] = { p1, p2, p3, p4, p5 };
	/*Produs* *vector2 = { p1, p2, p3, p4, p5 };*/
	Produs* vector2[] = { p1, p2 };
	/*Produs* * vector3 = NULL;
	for (int i = 0; i < 3; i++) {
		vector3[i] = p1;
		}*/


	Comanda* c1 = createComanda(2, "c1", 5, vector, "asd");
	Comanda* c2 = createComanda(1, "c1",2, vector2, "s");
	Comanda* c3 = createComanda(3, "c1", 2, vector, "asd");
	Comanda* c4 = createComanda(4, "c1", 2, vector, "asd"); //...

	insertBST(root, c1);
	insertBST(root, c2);
	insertBST(root, c3);
	//insertBST(root, c4);

	/*insertBST(root, c3);*/
	printBST_Inorder(root);


	printf("\n-------------\n");


	//3
	int* v = NULL;
	v = vectorId(root, "asd");
	printf("%d", v[0]);
	printf("\n%d", v[1]);


	//4
	int nr = nrFrunza(root, "c1");
	printf("\n\n%d", nr);

}