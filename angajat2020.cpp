#include "stdio.h"
#include "malloc.h"
#include "string.h"

struct Angajat {
	char* nume;
	int id;
	int salariu;
	char* functie;
	int vechime;

};

struct ListNode {
	ListNode* prev;
	Angajat* info;
	ListNode* next;
};

struct NodeBST {
	NodeBST* left;
	Angajat* info;
	NodeBST* right;
	int level;
};

struct Vector {
	NodeBST* *elements;
	int size;
};

Angajat* createAngajat(const char* nume, int id, int salariu, const char* functie, int vechime) {
	Angajat* a = (Angajat*)malloc(sizeof(Angajat));

	a->nume = (char*)malloc(strlen(nume) + 1);  // + 1 !!!!!!!!!!!!
	strcpy(a->nume, nume);

	a->id = id;
	a->salariu = salariu;

	a->functie = (char*)malloc(strlen(functie) + 1 );  // + 1 !!!!!!!!!!!!
	strcpy(a->functie, functie);

	a->vechime = vechime;

	return a;
}

ListNode* createListNode(Angajat* a) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	node->info = a;
	node->prev = node->next = NULL;   //aveam node.prev = node. prev = NULL........

	return node;
}

void insertListNode(ListNode* &head, Angajat* a) {
	ListNode* node = createListNode(a);

	//if (head != NULL) { //!
	//	//node->next = head; //gresit...

	//	head->prev = node;
	//}

	//head = node;

	if (head == NULL) {
		/*head->next = head->prev = NULL;*/
		head = node;
		
	}
	else {
		node->next = head;
		node->prev = NULL; //degeaba..

		head->prev = node;

		head = node;
	}
}


void printAngajat(Angajat* a) {
	printf("\nNume: %s", a->nume);
	printf("\nId: %d", a->id);
	printf("\nSalariu: %d", a->salariu);
	printf("\nFunctie: %s", a->functie);
	printf("\nVechime: %d", a->vechime);
	printf("\n");
}

void printListAmbeleSensuri(ListNode* head) {
	ListNode* crt = head;

	while (crt->next != NULL) {
		printAngajat(crt->info);

		crt = crt->next;
	}

	printAngajat(crt->info);

	printf("\n----Sens opus---");

	while (crt != NULL) {
		printAngajat(crt->info);
		crt = crt->prev;
	}

	//?
	free(crt);
}

void printList(ListNode* head) {
	ListNode* crt = head;

	while (crt != NULL) {
		printAngajat(crt->info);
		
		crt = crt->next;
	}

	//printAngajat(crt->info);


	/*while (head->next != NULL) {
		printAngajat(head->info);

		head = head->next;
	}*/
}


void stergeDinLista(ListNode* &head, int vechime) {

	ListNode* crt = head;

	while (crt != NULL) {
		if (crt->info->vechime < vechime) {
			//sterge
			if (crt == head) {
				head = head->next;
				head->prev = NULL;
			}
			else if (crt->next == NULL) {
				crt->prev->next = NULL;
				crt->prev = crt->next = NULL;
			}
			else {
				crt->prev->next = crt->next;
				crt->next->prev = crt->prev;
			}


		}

		crt = crt->next;
	}
}

NodeBST* createNodeBST(Angajat* a) {
	NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));

	node->info = createAngajat(a->nume, a->id, a->salariu, a->functie, a->vechime);
	node->left = node->right = NULL;
	node->level = 0;

	return node;
}

//void insertBST(NodeBST* &root, Angajat* an, int vechime) {
//	//sa nu partajeze mem heap
//
//	if (an->vechime >= vechime)
//	{
//		Angajat* a = createAngajat(an->nume, an->id, an->salariu, an->functie, an->vechime);
//
//		if (root == NULL) {
//			root = createNodeBST(a);
//			
//		}
//		else {
//			if (a->salariu < root->info->salariu) {
//				insertBST(root->left, a, vechime);
//				root->left->level = root->level + 1;
//			}
//			else if (a->salariu > root->info->salariu) {
//				insertBST(root->right, a, vechime);
//				root->right->level = root->level + 1;
//			}
//			else {
//				printf("\nduplicate key");
//			}
//		}
//
//	}
//}

void insertBST(NodeBST* &root, Angajat* an, int vechime) {
	//sa nu partajeze mem heap
	Angajat* a = createAngajat(an->nume, an->id, an->salariu, an->functie, an->vechime);

	if (an->vechime >= vechime)
	{
		

		if (root == NULL) {
			root = createNodeBST(a);

		}
		else {
			if (a->salariu < root->info->salariu) {
				insertBST(root->left, a, vechime);
				root->left->level = root->level + 1;
			}
			else if (a->salariu > root->info->salariu) {
				insertBST(root->right, a, vechime);
				root->right->level = root->level + 1;
			}
			else {
				printf("\nduplicate key");
			}
		}

	}
}



void inordine(NodeBST* root) {
	if (root != NULL) {
		inordine(root->left);

		printf("\nlevel: %d", root->level);
		printAngajat(root->info);
		
		inordine(root->right);

	}
}


//am apelat inordine in loc de inordinelevel...
void inordineLevel(NodeBST* root, int level) {
	if (root != NULL) {
		inordineLevel(root->left, level);

		if (root->level == level) {

			printf("\nlevel: %d", root->level);
			printAngajat(root->info);
		}

		inordineLevel(root->right, level);

	}
}

void initVector(Vector& v, int size) {

	v.size = size;
	v.elements = (NodeBST**)malloc(sizeof(NodeBST*) * size);
	memset(v.elements, NULL, sizeof(NodeBST*) * size);
}


int maxim(int a, int b)
{
	return a > b ? a : b;
}

int getHeight(NodeBST* root) {
	if (root == NULL) {
		return 0;
	}
	else {
		return 1 + maxim(getHeight(root->left), getHeight(root->right));
	}
}


//
//void getHeightWithKey(NodeBST* root, int key, int& height) {
//	if (root != NULL) {
//		getHeightWithKey(root->left, key, height);
//		if (root->info->salariu == key) {
//			height = getHeight(root);
//		}
//		getHeightWithKey(root->right, key, height);
//	}
//}

void getLevel(NodeBST* root, int key, int& level) {
	NodeBST* copy = root;

	level = 0;
	while (copy != NULL && copy->info->salariu != key) {
		if (key < copy->info->salariu)
		{
			level++;
			copy = copy->left;
			
		}
		else if (key > copy->info->salariu)
		{
			level++;
			copy = copy->right;

		}
	}
}

int searchLevelAfterKey(NodeBST* root, int key) {
	/*int level = 0;

	if (root != NULL) {
		searchLevelAfterKey(root->left, key);

		if(root->info->salariu == key){
			level = root->level;
		}

		searchLevelAfterKey(root->right, key);

	}

	return level;*/


	/*
	if (root != NULL) {
		if (key < root->info->salariu) {
			return searchLevelAfterKey(root->left, key);
		}
		else if (key > root->info->salariu) {
			return searchLevelAfterKey(root->right, key);
		}
		else {
			return root->level;
			
		}
	}

	return -1;*/


	if (root == NULL || root->info->salariu == key) {
		return root->level;
	}

	if (key < root->info->salariu) {
		return searchLevelAfterKey(root->left, key);
	}

	if (key > root->info->salariu) {
		return searchLevelAfterKey(root->right, key);
	}
}

void salvareVector(Vector& v, NodeBST* root, int cheie) {
	//NodeBST* *vector = NULL;
	
	
	
	/*int i = 0;

	NodeBST* root = root2;

	while (root->info->salariu != cheie) {
		if (cheie < root->info->salariu) {
			i++;
			root = root->left;
		}
		else if (cheie > root->info->salariu) {
			i++;
			root = root->right;
		}
		else {
			i++;
			break;
		}
	}*/
	/*vector = (NodeBST**)malloc(sizeof(NodeBST) * i);
	memset(vector, NULL, sizeof(NodeBST) * i);*/

	//int height = 0;

	//getHeightWithKey(root2, cheie, height);


	int level = searchLevelAfterKey(root, cheie);
	
	initVector(v, level + 1);

	int i = 0;

	while (root->info->salariu != cheie && root != NULL) {
		if (cheie < root->info->salariu) {
			v.elements[i++] = root;
			root= root->left;
		}
		else if (cheie > root->info->salariu) {
			v.elements[i++] = root;
			root = root->right;
		}
		else {
			v.elements[i++] = root;
			break;
		}


 	}

	v.elements[i++] = root;


	//return v;
}

void freeVector(Vector& v) {

	for(int i = 0; i < v.size; i++)
		free(v.elements[i]);

	free(v.elements);

	
}

void freeNode(ListNode* node) {

	free(node->info->nume);
	free(node->info->functie);
	free(node->info);


	free(node->next);
	free(node->prev);
	free(node);
}

void freeList(ListNode* &head) {
	while (head != NULL) {
		ListNode* crt = head;

		head = head->next;


		freeNode(crt);
	// free(crt);
	}
}

void main() {
	FILE* pFile = fopen("Data.txt", "r");
	ListNode* head = NULL;
	if (pFile) {
		int nrValori;
		fscanf(pFile, "%d", &nrValori);
		
		for (int i = 0; i < nrValori; i++) {

			char nume[1000];
			int id = 0;
			int salariu = 0;
			char functie[1000];
			int vechime = 0;

			fscanf(pFile, "%s", nume);
			fscanf(pFile, "%d", &id);
			fscanf(pFile, "%d", &salariu);
			fscanf(pFile, "%s", functie);
			fscanf(pFile, "%d", &vechime);


			Angajat* a = createAngajat(nume, id, salariu, functie, vechime);
			insertListNode(head, a);

			//printAngajat(a);


		}
		fclose(pFile);
		
		//ListNode* head2 = head;

		printf("\n----------print list--------\n");
		//printList(head);


		printf("\n----------END print list--------\n");
		/*printf("\n----------print list2--------\n");
		if (head == NULL)
			printf("\nhead is null");*/
		//printList(head);
		
		printf("\n----------print list 2 sensuri--------\n");
		//printListAmbeleSensuri(head);



		printf("\n---------- 2 - sterge lista-------------");
		//stergeDinLista(head, 2);

		//printListAmbeleSensuri(head);

		printf("\n---------- 3 - insert bst-------------");
		NodeBST* root = NULL;

		//filtru: vechime < 2
		int vechime = 2;
		while (head != NULL) {
			ListNode* crt = head;

			//Angajat* a = createAngajat(head->info->nume, head->info->id, head->info->salariu, head->info->functie, head->info->vechime);
			//insertBST(root, a, vechime);


			insertBST(root, head->info, vechime);
			printAngajat(head->info);

			head = head->next;

			//free area
			//freeNode(crt);
		}


		printf("\n---------- inordine-------------");
		/*NodeBST* root2 = root;*/
		inordine(root);

		printf("\n--------level order(bonus)------------");
		/*printf("height: %d", getHeight(root2));
		for (int k = 0; k < getHeight(root2); k++) {
			inordineLevel(root, k);
		}*/


		printf("\n----------4  vector-------------");



		Vector v;
		salvareVector(v, root, 2100);
		for (int j = 0; j < v.size; j++) {
			printAngajat(v.elements[j]->info);
		}

		freeVector(v);
		if (v.elements == NULL) {
			printf("\nVector is null");
		}
		else {
			printf("\nVector is NOT null");
		}

		/*for (int j = 0; j < v.size; j++) {
			printAngajat(v.elements[j]->info);
		}*/

		
		freeList(head);
		
		if (head == NULL) {
			printf("\nhead is null");
		}
		else
			while (head != NULL) {
			
				printAngajat(head->info);
				head = head->next;
			}
	}

}