#include "stdio.h"
#include "string.h"
#include "malloc.h"

struct Lac {
	int cod;
	char* denumire;
	float suprafata;
	int areInsule;
};

struct ListNode {
	ListNode* prev;
	Lac* info;
	ListNode* next;
};

Lac* createElement(int cod, const char* denumire, float supratafa, int areInsule) {
	Lac* l = (Lac*)malloc(sizeof(Lac));

	l->cod = cod;
	l->denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(l->denumire, denumire);

	l->suprafata = supratafa;
	l->areInsule = areInsule;

	return l;

}
	

ListNode* createNode(Lac* l) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	node->next = node->prev = NULL;
	node->info = l;

	return node;
}

//* &
void insertNode(ListNode* &head, ListNode* node) {

	if (head == NULL) {
		head = node;
	}
	else {
		node->next = head;
		node->prev = NULL;
		
		head->prev = node;
		head = node;
	}

	
}

//int cod;
//char* denumire;
//float suprafata;
//int areInsule;

void printList(ListNode* head) {
	ListNode* tmp = head;
	while (tmp != NULL) {
		printf("\ncod: %d", tmp->info->cod);
		printf("\nden %s", tmp->info->denumire);
		printf("\nsuprafata: %5.2f", tmp->info->suprafata);
		printf("\nare insule: %d", tmp->info->areInsule);

		tmp = tmp->next;
		printf("\n");
	}
	
}


void printListInvers(ListNode* head) {
	ListNode* tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	while(tmp !=NULL){
		printf("\ncod: %d", tmp->info->cod);
		printf("\nden %s", tmp->info->denumire);
		printf("\nsuprafata: %5.2f", tmp->info->suprafata);
		printf("\nare insule: %d", tmp->info->areInsule);

		tmp = tmp->prev;
		printf("\n");
	}
}

float sumaSuprafete(ListNode* head) {
	ListNode* crt = head;
	float suma = 0;
	while (crt != NULL) {
		if (crt->info->areInsule == 0) {
			suma += crt->info->suprafata;
		}
		crt = crt->next;
	}

	return suma;
}

Lac* stergeLac(ListNode* &head, int cod) {
	Lac* lac = NULL;
	ListNode* tmp = head;

	while (tmp != NULL && tmp->info->cod != cod) {
		tmp = tmp->next;
	}

	if (tmp->info->cod == cod) {
		lac = tmp->info;
	}
	//am gasit valoarea


	//stergem
	/*if(tmp->next)*/
	if (tmp == head) { //am gasit val pe primul nod(head)
		head = head->next;
		head->prev = NULL;
	}
	else if (tmp->next == NULL) {
		tmp->prev->next = NULL;
		tmp->prev = tmp->next = NULL;
	}
	else if (tmp->next != NULL) {
		tmp->prev->next = tmp->next;
		//...crt->next->prev = crt->prev;

	}
	/*else if(tmp->next == NULL){
		
	}*/



	return lac;
}

void main() {
	Lac* l1 = createElement(1, "A", 100, 1);
	Lac* l2 = createElement(2, "B", 1001, 1);
	Lac* l3 = createElement(3, "C", 1002, 0);
	Lac* l4 = createElement(4, "D", 1003, 1);
	Lac* l5 = createElement(5, "E", 1004, 1);

	ListNode* e1 = createNode(l1);
	ListNode* e2 = createNode(l2);
	ListNode* e3 = createNode(l3);
	ListNode* e4 = createNode(l4);
	ListNode* e5 = createNode(l5);

	ListNode* head = NULL;
	insertNode(head, e1);
	insertNode(head, e2);
	insertNode(head, e3);
	insertNode(head, e4);
	insertNode(head, e5);


	printList(head);

	printf("\n -----------------INVERS-------------");
	printListInvers(head);

	printf("\n--------------4--------------");
	float s = sumaSuprafete(head);
	printf("\n%5.2f", s);  //nu mai uita sa printezi
	/*printList(head);*/

	printf("\n--------------5--------------");
	Lac* rez = stergeLac(head, 1);
	/*printf("\n\n%d", rez->cod);*/
	printList(head);

}