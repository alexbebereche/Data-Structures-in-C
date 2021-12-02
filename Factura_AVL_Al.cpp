#include "stdio.h"
#include "malloc.h"
#include "string.h"

struct Factura {
	int numar;
	char* data;
	char* denumire;
	float valoare;
	int nrProduse;
};

struct AVLNode {
	Factura factura;
	AVLNode* left;
	AVLNode* right;

};

struct Queue {
	Queue* next;
	AVLNode* info;
};

Factura initFactura(int nr, const char *data, const char* nume, float val, int nrProd)
{
	Factura factura;

	factura.numar = nr;
	factura.valoare = val;
	factura.nrProduse = nrProd;

	factura.data = (char*)malloc(strlen(data) + 1);
	strcpy(factura.data, data);

	factura.denumire = (char*)malloc(strlen(nume) + 1);
	strcpy(factura.denumire, nume);

	return factura;
}

//1
AVLNode* createNode(Factura f)
{
	AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));

	newNode->factura = f;
	newNode->left = newNode->right = NULL;

	return newNode;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int getHeight(AVLNode* head)
{
	if (head == NULL)
		return 0;
	else
		return 1 + max(getHeight(head->left), getHeight(head->right));
}

int getBalanceDegree(AVLNode* root) { //dc head?
	if (root == NULL) {
		return 0;
	}
	else {
		return getHeight(root->right) - getHeight(root->left);
	}
}

AVLNode* rotateLeft(AVLNode* root) {
	if (root != NULL) {
		AVLNode* aux = root->right;
		root->right = aux->left;
		aux->left = root;

		return aux;

	}

	return root;
	
}


AVLNode* rotateRight(AVLNode* root) {
	if (root != NULL) {
		AVLNode* aux = root->left;
		root->left = aux->right;
		aux->right = root;

		return aux;

	}

	return root;

}


//de continuat
void rebalance(AVLNode* &root) {
	if (root != NULL) {
		if (getBalanceDegree(root) == 2) {
			if (getBalanceDegree(root->right) != 1) {
				root->right = rotateLeft(root->right);
			}
			root = rotateLeft(root);
		}


		if (getBalanceDegree(root) == -2) { 
			if (getBalanceDegree(root->left) != -1) {
				root->left = rotateRight(root->right);
			}
			root = rotateRight(root);
		}

	}
	
}


void insert(AVLNode* &root, Factura f) {

	AVLNode* newNode = createNode(f); //creez nodul
	
	//nu uita sa verifici daca e NULL
	if (root == NULL) {
		root = newNode;
	}
	else {
		if (f.numar < root->factura.numar) {
			insert(root->left, f); //mai mic, inserez in dreapta
		}
		else { //daca sunt egale?
			insert(root->right, f);
			/*rebalance(root);*/  //nu aici...
		}
		rebalance(root);
	}
}

void printFactura(Factura f)
{
	printf("\n %d %s %s %f %d", f.numar, f.data, f.denumire, f.valoare, f.nrProduse);
}

void inorder(AVLNode* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printFactura(root->factura);
		inorder(root->right);
	}
}

//void DSR(AVLNode* root)
//{
//	if (root != NULL)
//	{
//		
//		DSR(root->right);
//		DSR(root->left);
//		printFactura(root->factura);
//	}
//}


//void DSR(AVLNode* root)
//{
//	if (root != NULL)
//	{
//
//		DSR(root->right);
//		DSR(root->left);
//		printFactura(root->factura);
//	}
//}

void DRS(AVLNode* root)  //descrescator
{
	if (root != NULL)
	{

		DRS(root->right);
		printFactura(root->factura);
		DRS(root->left);
	}
}

void RSD(AVLNode* root)  //descrescator
{
	if (root != NULL)
	{
		printFactura(root->factura);
		RSD(root->left);
		RSD(root->right);
	}
}

//Level-order, imi trebuie o coada
int getMaxHeight(AVLNode* root)  //descrescator
{
	if (root != NULL) {
		int maxHeight = 0;

		AVLNode* tmp = root;
		while (tmp->right != NULL && tmp->left != NULL) {
			if (tmp->right != NULL)
				tmp = tmp->right;
			else {
				if (tmp->left != NULL)
					tmp = tmp->left;
			}

			maxHeight++;
		}

		return maxHeight;
	}

	return 0;

}

void printLevel(AVLNode* root, int level)
{
	if (root != NULL)
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printFactura(root->factura);
		printLevel(root->left, level + 1);
		printLevel(root->right, level + 1);
	}
	else
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printf("NULL\n");
	}
}


void main() {
	Factura f1 = initFactura(23, "2019.01.20", "Alex", 222, 9);
	Factura f2 = initFactura(20, "2019.04.22", "Bob", 45, 3);
	Factura f3 = initFactura(30, "2019.03.05", "Alice", 23., 1);
	Factura f4 = initFactura(17, "2019.03.13", "Adi", 40, 2);
	Factura f5 = initFactura(21, "2019.02.24", "Ana", 55, 4);
	Factura f6 = initFactura(28, "2019.05.17", "Vader", 1, 40);
	Factura f7 = initFactura(35, "2019.06.02", "Alex", 22, 5);
	/*Factura f8 = initFactura(30, "2019.04.19", "Ion", 33.44, 6);*/
	//Factura f9 = initFactura(41, "2019.02.02", "Andrei", 5, 2);

	AVLNode* root = NULL;

	insert(root, f1);
	insert(root, f2);
	insert(root, f3);
	insert(root, f4);
	insert(root, f5);
	insert(root, f6);
	insert(root, f7);
	/*insert(root, f8);*/

	inorder(root);

	printf("\n----------------------\n");
	RSD(root);

	printf("\n----------------------\n");
	//traversarePeNivele(root);

	/*int m = getMaxHeight(root);
	printf("\n\n\n\n%d", m);*/
}