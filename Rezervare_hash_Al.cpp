#include "stdio.h"
#include "string.h"
#include "malloc.h"
//chaining
//la chaining nu prea se preteaza resize..ma lasa sa ma duc cat vreau in heap, nu am restrictii...
//problema ar fi fost cand nu am posibilitatea asta


struct Rezervare {
	unsigned int id;
	char* denumire;
	unsigned char numarCamere;
	char* numeClient;
	char* perioada;
	float suma;
};

//ne trebuie ListNode la chaining!!! v
struct ListNode {
	ListNode* next;
	Rezervare info;
};

struct HashTable {
	ListNode* *buckets = NULL;
	int size = 0;
	int noEl = 0;
};

Rezervare createRezervare(unsigned int id, const char* den,
	unsigned char numarCamere, const char* nume, const char* perioada,
	float suma) {

	Rezervare rez; /*= (Rezervare*)malloc(sizeof(Rezervare));*/

	rez.id = id;

	rez.denumire = (char*)malloc(strlen(den) + 1);
	strcpy(rez.denumire, den);

	rez.numarCamere = numarCamere;

	rez.numeClient = (char*)malloc(strlen(nume) + 1);
	strcpy(rez.denumire, nume);

	rez.suma = suma;

	return rez;


}

ListNode* createElement(Rezervare rez) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->info = rez;
	newNode->next = NULL;

	return newNode;
}

void initHashTable(HashTable& ht, int dim) {  //& mai bine...nu *

	ht.size = dim; //size e diferit de dim
	ht.noEl = 0;

	ht.buckets = (ListNode**)malloc(sizeof(ListNode*) * dim);
	memset(ht.buckets, NULL, sizeof(ListNode*) * dim);

}


//void insertRezervare(HashTable hashtable, Rezervare rezervare)
//{
//	int index = fHash(rezervare.denumire, hashtable.noEl);
//	ListNode* list = hashtable.buckets[index];
//	insertElement(list, rezervare);
//	hashtable.keyIndex[index] = list;
//
//	//nu a crescut nr de elemente?
//}

int fHash(const char* key, int dim)
{
	int indexLoc = key[0] % dim;
	return indexLoc;
}

void insertElement(ListNode* &head, ListNode* node) {
	//inserarea normala, doar ca nu mai creez...etc


	//dc doinea a scris list
	if (head != NULL) {
		node->next = head;
	}
	head = node; //se intampla indiferent...

}


//de revazut
void insertHT(HashTable ht, Rezervare value) {
	//1. get index position for inserting
	int index = fHash(value.denumire, ht.size);
	
	//2.create new elem.
	ListNode* node = createElement(value);

	//3. insert created el into ht
	ListNode* list = ht.buckets[index];   //pb aici
	insertElement(list, node);  //inserez nodul creat la pozitia cu indexul general
	ht.buckets[index] = list;  //pun lista la indexul respectiv, dupa ce am adaugat


	ht.noEl++;		//* cu ptr
	//ca sa se faca modificarea?

}


void printHT(HashTable ht) {

	//vector de liste sp inlantuite
	for (int i = 0; i < ht.noEl; i++) {

		ListNode* current = ht.buckets[i];

		while (current != NULL) {
			printf("\nId rezervare: %d", current->info.id);
			printf("\nDenumire hotel: %s", current->info.denumire);
			/*printf("\nNr camere: %u", current->info->numarCamere);
			printf("\nNume client: %s", current->info->numeClient);
			printf("\nPerioada: %s", current->info->perioada);
			printf("\nSuma: %f", current->info->suma);*/
			printf("\n");

			current = current->next;
		}
	}
}



void main() {
	HashTable hashTable;

	initHashTable(hashTable, 101); //Dupa asta e NULL
	const char* den1 = "Mama";
	const char* nume1 = "Alexa";
	const char* per1 = "01/02-05/02";
	Rezervare r1 = createRezervare(1, den1, 10, nume1, per1, 200);
	/*ListNode* head = NULL;*/
	insertHT(hashTable, r1);
	/*Rezervare* r2 = createRezervare(2, "Piatra Craiului", 15, "Pop Ion", "05/03-10/03", 500);*/
	//insertHT(&hashTable,r2);
	//Rezervare* r3 = createRezervare(3, "Pescarusul", 20, "Popovici Ionela", "05/05-10/06", 5000);
	//insertHT(&hashTable, r3);
	//Rezervare *r4 = createRezervare(4, "Ursulica", 45, "Marin Marin", "05/03-10/03", 600);
	//insertHT(&hashTable, r4);
	//Rezervare* r5 = createRezervare(5, "Pescarusul", 25, "Traian", "05/03-10/03", 500);
	//insertHT(&hashTable, r5);

	printHT(hashTable);



}