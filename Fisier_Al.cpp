#include "stdio.h"
#include "malloc.h"
#include "string.h"

//wtf
struct Fisier {
	char* denumire;
	char* path;
	char* extensie;
	unsigned int dimensiune;
};

struct ListNode{
	ListNode* prev;
	Fisier fisier;		//fara ptr de data asta...
	ListNode* next;
};

Fisier createFisier(const char* den, const char* path,
	const char* extensie, unsigned int dim) {
	Fisier fisier;

	fisier.denumire = (char*)malloc(strlen(den) + 1);
	strcpy(fisier.denumire, den);

	fisier.path = (char*)malloc(strlen(path) + 1);
	strcpy(fisier.path, path);

	fisier.extensie = (char*)malloc(strlen(extensie) + 1);
	strcpy(fisier.extensie, extensie);

	fisier.dimensiune = dim;

	return fisier;
}


ListNode* createNode(Fisier fisier) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->fisier = fisier;
	newNode->next = newNode->prev = NULL;

	return newNode;

}

void insertNode(ListNode* &head, Fisier fisier) {
	ListNode* newNode = createNode(fisier);

	if (head == NULL) {
		head = newNode; //atat, nu mai e nevoie de prev, next = NULL, am facut asta in fct create
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void printFile(Fisier fisier)
{
	printf("\n");
	printf("\nNume fisier: %s", fisier.denumire);
	printf("\nCale fisier: %s", fisier.path);
	printf("\nExtensie fisier: %s", fisier.extensie);
	printf("\nDimensiune fisier: %d", fisier.dimensiune);
}

//atentie, citeste cerinta, trebuie traversare in ambele sensuri
void printList(ListNode* head) {
	
	if (head == NULL) {
		printf("\nNup");
	}
	else {

		ListNode* crt = head;
		while (crt->next != NULL) { //nu e null aici, nu e lista circulara...
			printFile(crt->fisier);
			crt = crt->next;
		}
		printFile(crt->fisier);  //pt a printa ultimul el...

		/*do {
			printFile(crt->fisier);
			crt = crt->next;
		} while (crt != NULL);*/

		printf("\n-----------Invers----------------\n");

		while (crt->prev != NULL) {
			printFile(crt->fisier);
			crt = crt->prev;
		}
		printFile(crt->fisier);

		/*crt = crt->prev;
		do {
			printFile(crt->fisier);
			crt = crt->prev;
		} while (crt != NULL);*/

	}
}

void searchFisier(ListNode* head, ListNode* &newHead, const char* extensie) {

	ListNode* crt = head;
	if (head == NULL) {
		printf("\nempty list");
	}
	else {
		while (crt != NULL) {
			if (strcmp(crt->fisier.extensie, extensie) == 0) {
				insertNode(newHead, crt->fisier);
			}
			crt = crt->next;
		}
	}
}

void modifica(ListNode* &head, const char* initialPath, const char* newPath) {
	ListNode* crt = head;

	if (head == NULL) {

		printf("\nlista goala");
	}
	else {
		while (crt != NULL) {
			if (strcmp(crt->fisier.path, initialPath) == 0) {
				//aloc...ok
				crt->fisier.path = (char*)malloc(strlen(newPath) + 1);
				strcpy(crt->fisier.path, newPath);
			}
			crt = crt->next;
		}
	}

}

void main() {
	//2
	Fisier f1 = createFisier("Fisier_1", "C:\\SDD", "txt", 3892);
	Fisier f2 = createFisier("Fisier_2", "C:\\SDD\\Fisiere", "bin", 5000);
	Fisier f3 = createFisier("FIsier_3", "C:\\SDD\\F3", "txt", 2587);
	Fisier f4 = createFisier("FIsier_4", "C:\\SDD", "txt", 1578);
	Fisier f5 = createFisier("FIsier_5", "C:\\SDD", "bin", 3892);

	ListNode* head = NULL;
	insertNode(head, f1);
	insertNode(head, f2);
	insertNode(head, f3);
	insertNode(head, f4);
	insertNode(head, f5);
	
	//3
	printList(head);

	//4
	ListNode* newHead = NULL;

	searchFisier(head, newHead, "txt");
	printList(newHead);

	printf("\n------------------   5   ------------------\n");
	modifica(head, "C:\\SDD", "OOOOFFFFFFF");
	printList(head);
}