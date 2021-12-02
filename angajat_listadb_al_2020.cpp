#include "stdio.h"
#include "string.h"
#include "malloc.h"
//lista db
struct Angajat {
	int id;
	char* nume;
	char* rol;
	int vechime;
	int varsta;

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
};

Angajat* createElement(int id, const char* nume, const char* rol, int vechime, int varsta) {
	Angajat* a = (Angajat*)malloc(sizeof(Angajat));

	a->id = id;
	a->vechime = vechime;
	a->varsta = varsta;

	a->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(a->nume, nume);

	a->rol = (char*)malloc(strlen(rol) + 1);
	strcpy(a->rol, rol);


	return a;
}

ListNode* createNode(Angajat* a) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	
	node->info = createElement(a->id, a->nume, a->rol, a->vechime, a->varsta);
	node->prev = node->next = NULL;

	return node;
}

void insertNode(ListNode* &head, ListNode* node) {
	//NU UITA
	if (head == NULL) {
		/*head->prev = head->next = NULL;*/
	}
	else {
		node->next = head;
		node->prev = NULL;

		head->prev = node;
	}

	head = node;
}

//
//int id;
//char* nume;
//char* rol;
//int vechime;
//int varsta;

void printList(ListNode* head) {
	ListNode* c = head;
	while (c != NULL) {
		printf("\nid: %d", c->info->id);
		printf("\nnume: %s", c->info->nume);
		printf("\nrol: %s", c->info->rol);
		printf("\nvechime: %d", c->info->vechime);
		printf("\nvarsta: %d", c->info->varsta);
		printf("\n");
		c = c->next; //nu uita
	}

	//nu am eliberat...


}

void printList2(ListNode* head) {
	ListNode* c = head;
	while (c->next != NULL) {
		printf("\nid: %d", c->info->id);
		printf("\nnume: %s", c->info->nume);
		printf("\nrol: %s", c->info->rol);
		printf("\nvechime: %d", c->info->vechime);
		printf("\nvarsta: %d", c->info->varsta);
		printf("\n");
		c = c->next; //nu uita
	}
	printf("\nid: %d", c->info->id);
	printf("\nnume: %s", c->info->nume);
	printf("\nrol: %s", c->info->rol);
	printf("\nvechime: %d", c->info->vechime);
	printf("\nvarsta: %d", c->info->varsta);
	printf("\n");

	while (c != NULL) {
		printf("\nid: %d", c->info->id);
		printf("\nnume: %s", c->info->nume);
		printf("\nrol: %s", c->info->rol);
		printf("\nvechime: %d", c->info->vechime);
		printf("\nvarsta: %d", c->info->varsta);
		printf("\n");
		c = c->prev; //nu uita
	}

	free(c);

	
}



void printNode(Angajat* c) {
	

		printf("\nid: %d", c->id);
		printf("\nnume: %s", c->nume);
		printf("\nrol: %s", c->rol);
		printf("\nvechime: %d", c->vechime);
		printf("\nvarsta: %d", c->varsta);
		printf("\n");
	
	
}


//2
void freeListNode(ListNode* node) {
	free(node->info->nume);
	free(node->info->rol);
	free(node->info);
	free(node);
}

void deleteNode(ListNode* &head, int vechime) {
	ListNode* tmp = NULL;
	ListNode* crt = head;

	while (crt != NULL) {
		if (crt->info->vechime < vechime) {
			if (crt == head) { //e head
				printf("\nhead: sterg nod cu id %d, vechime: %d", crt->info->id, crt->info->vechime);
				tmp = crt;

				tmp->next->prev = NULL;
				

				/*crt = crt->next;


				head = crt;*/
				head = crt->next;
				/*crt = head;*/
				crt = crt->next;

				freeListNode(tmp);
			}
			else if (crt->next == NULL && crt->prev == NULL) {//un singur nod
				printf("\nsingur sterg nod cu id %d, vechime: %d", crt->info->id, crt->info->vechime);
				/*tmp = crt;*/
				head = NULL;
				
				/*freeListNode(tmp);*/

			}
			else if (crt->next == NULL && crt->prev != NULL) { //ultimul nod
				printf("\nultimsterg nod cu id %d, vechime: %d", crt->info->id, crt->info->vechime);
				/*tmp = crt;*/
				crt->prev->next = NULL;
				/*crt->next = tmp->prev = NULL;*/

				/*head = */
				/*crt = NULL;*/
				/*freeListNode(tmp);
*/
			}
			else if(crt->next != NULL && crt->prev != NULL){
				printf("\nmijloc: sterg nod cu id %d, vechime: %d", crt->info->id, crt->info->vechime);

				/*tmp = crt;*/
				crt->next->prev = crt->prev;
				crt->prev->next = crt->next;

				/*freeListNode(tmp);*/
				crt = crt->next;
				
			}
			else {
				printf("\nalalala#####################################");
				
			}



		}
		else {
			crt = crt->next;
		}


		/*crt = crt->next;*/
	}

}




NodeBST* createNodeBST(Angajat* a) {
	NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));

	node->info = a;
	node->left = node->right = NULL;

	return node;
}


//
void insertBST(NodeBST* &root, Angajat* a) {
	if (root == NULL) {
		root = createNodeBST(a);
	}
	else {
		if (root->info->varsta < a->varsta) {
			insertBST(root->right,a);
		}
		else if (root->info->varsta > a->varsta) {
			insertBST(root->left, a);
		}
		else {
			printf("\nDuplicate key");
		}
	}
}

void inordine(NodeBST* root) {
	if (root != NULL) {
		inordine(root->left);
		printNode(root->info);
		inordine(root->right);
	}
}


//4
//Angajat* *salvareNoduri(NodeBST* root, int varsta) {
//	NodeBST* c = root;
//	int contor = 0;
//	while (c->info->varsta <= varsta) 
//		if (c->right->info->varsta <= varsta) {
//			c = c->right;
//			contor++;
//		}
//
//
//		Angajat* *vector = (Angajat**)malloc(sizeof(Angajat*) * contor); //* ...
//		memset(vector, NULL, sizeof(Angajat*) * contor);
//
//
//
//		int i = 0;
//
//		while (root->info->varsta <= varsta) {
//			if (root->right->info->varsta <= varsta) {
//				root = root->right;
//			}
//			else if (root->left->info->varsta > varsta) {
//				vector[i++] = root->info;
//			}
//		}
//
//
//
//	return vector;
//}


void freeBST(NodeBST* &root) {
	if (root == NULL) {
		printf("\n\n\n no tree");
	}
	else {
		freeBST(root->right);
		freeBST(root->left);
		NodeBST* tmp = root;
		
		free(tmp->info->nume);
		free(tmp->info->rol);
		free(tmp->info);
		free(tmp);

		root = NULL;
		
	}
}


void freeList(ListNode* &node) {
	ListNode* tmp = NULL;
	while (node)
	{
		tmp = node;
		node = node->next;
		freeListNode(tmp);
		
	}

}



void main() {
	FILE* pFile = fopen("Data.txt", "r");
	ListNode* head = NULL;
	ListNode* node = NULL;
	if (pFile) {
		
		while (!feof(pFile)) {
			int id = 0;
			char bufferNume[100];
			char bufferRol[100];
			int vechime = 0;
			int varsta = 0;

			fscanf(pFile, "%d %s %s %d %d", &id, bufferNume, bufferRol, &vechime, &varsta);
			Angajat* a = createElement(id, bufferNume, bufferRol, vechime, varsta);
			node = createNode(a);
			insertNode(head, node);
		}
		fclose(pFile);


		printList(head);


		printf("\n\n\n--------------------DELETE--------------");
		deleteNode(head, 10);
		if (head)
			printList2(head);
		else
			printf("\n\n----");



		printf("\n--------------3-----------------");
		//3
		NodeBST* root = NULL;
		ListNode* c = head;
		while (c != NULL) {
			if (c->info->varsta > 10) {
				insertBST(root, c->info);
				printNode(c->info);
			}
			c = c->next;
		}




		//5
		//dezalocare lista
		freeList(head);
		if (head != NULL) {
			printf("\nda");
			printList(head);
		}
		else if(head== NULL){
			printf("\neste null");
		}


		printf("\n------------BST--------------");

		/*Angajat* *elements = salvareNoduri(root, 15);*/





	printf("\n---------------");


		//inordine(root);

		//freeBST(root);

		///*inordine(root);*/
		//if (root != NULL) {
		//	printf("\nda");
		//	inordine(root);
		//}
		//else if (root == NULL) {
		//	printf("\neste null");
		//}


	}
	else {
		printf("\nNu s-a deschis");
	}

	




}