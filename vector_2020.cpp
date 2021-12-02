#include "stdio.h"
#include "malloc.h"
#include "string.h"

struct Avion {
	int id;
	char* nume;
	char* proprietar;
	int capacitate;

};

struct Vector {
	Avion* *elements;
	int dim;
};

struct ListNode {
	ListNode* prev;
	Avion* info;
	ListNode* next;

};

struct Queue {
	//am facut init aici!
	ListNode* head = NULL;
	ListNode* tail = NULL;
};

ListNode* createNode(Avion* a) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	node->info = a;
	node->prev = node->next = NULL;
	
	return node;
}

void insertNode(ListNode* &head, Avion* a) {

	ListNode* node = createNode(a);

	node->next = head;
	node->prev = NULL;

	head->prev = node;
	head = node;

}

void putNode(Queue& queue, ListNode* node) {

	//lista e goala
	if (queue.head == NULL && queue.tail == NULL) { 
		queue.head = queue.tail = node;
	}
	else {
		//inserez la sf in coada  //extragerea e la inceput (FIFO)
		node->prev = queue.tail;
		queue.tail->next = node;

		queue.tail = node;
	}

}

Avion* getNode(Queue& queue) {
	Avion* info = NULL;

	if (queue.head != NULL && queue.tail != NULL) { //macar un element
		//extrag de la inceput (FIFO)
		info = queue.head->info;

		ListNode* tmp = queue.head;  //il sterg, si trebuie sa il dezaloc

		if (queue.head->next == NULL) { //doar un element
			queue.head = queue.tail = NULL;
		}
		else {
			queue.head = queue.head->next;
			queue.head->prev = NULL;
		}

		free(tmp);
	}

	return info;
}

Avion* createAvion(int id, const char* nume, const char* proprietar, int capacitate) {

	Avion* a = (Avion*)malloc(sizeof(Avion));

	a->id = id;

	a->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(a->nume, nume);

	a->proprietar = (char*)malloc(strlen(proprietar) + 1);
	strcpy(a->proprietar, proprietar);

	a->capacitate = capacitate;

	return a;
}

void initVector(Vector& v, int dim) {

	v.dim = dim;
	v.elements = (Avion**)malloc(sizeof(Avion*) * dim);
	memset(v.elements, NULL, sizeof(Avion*) * dim);
}

void printAvion(Avion* a) {
	printf("\nId: %d", a->id);
	printf("\nNume: %s", a->nume);	
	printf("\nProprietar: %s", a->proprietar);
	printf("\nCapacitate: %d", a->capacitate);
	printf("\n");

}


void printVector(Vector v) {
	
	for (int i = 0; i < v.dim; i++) {
		printAvion(v.elements[i]);
	}
}

void printQueue(Queue q) {
	ListNode* crt = q.head;

	while (crt != NULL) {
		printAvion(crt->info);

		crt = crt->next;
	}

	free(crt);
}

void mutaDinVector(Vector& v, Queue& queue) {

	for (int i = 0; i < v.dim; i++) {
		ListNode* node = createNode(v.elements[i]);
		putNode(queue, node);

	}

	free(v.elements);

}

void decolare(Queue& queue, int nr) {

	Avion* a = NULL;
	for (int i = 0; i < nr; i++) {
		a = getNode(queue);
		printAvion(a);
	}
}


//5
void ex5(Queue& queue, Queue& queue2, int id) {
	
	ListNode* crt = NULL;



}

void main() {
	FILE* pFile = fopen("Data.txt", "r");
	Avion* a = NULL;
	

	if (pFile) {
		int numar = 0;
		fscanf(pFile, "%d", &numar);
		Vector v;
		Queue queue;
		initVector(v, numar);

		int id = 0;
		char nume[100];
		char proprietar[100];
		int capacitate = 0;


		for (int i = 0; i < numar; i++) {
			fscanf(pFile, "%d", &id);
			fscanf(pFile, "%s", &nume);
			fscanf(pFile, "%s", &proprietar);
			fscanf(pFile, "%d", &capacitate);

			a = createAvion(id, nume, proprietar, capacitate);
			v.elements[i] = a;
		}
		fclose(pFile);



		printVector(v);

		printf("\n----------queue---------");
		/*for (int i = 0; i < v.dim; i++) {
			ListNode* node = createNode(v.elements[i]);
			putNode(queue, node);
		}*/

		mutaDinVector(v, queue);
		printQueue(queue);


		/*if (v.elements == NULL) {
			printf("\nelements are null");
		}
		for (int i = 0; i < v.dim; i++) {
			printAvion(v.elements[i]);
		}*/


		printf("\n-------4  Decolare--------");
		decolare(queue, 4);


		printf("\n-------5 --------");


	}

}