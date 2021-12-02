#include "stdio.h"
#include "string.h"
#include "malloc.h"

struct CotaIntretinere {
	char* adresa;
	int nrApartament;
	int nrPersPerApartament;
	int an;
	int luna;
	float intretinere;

};

struct ListNode {
	ListNode* next;
	CotaIntretinere* info;
};

struct HashTable {
	ListNode*  *buckets = NULL;
	int size = 0; //dim

	int noEl = 0;
};

CotaIntretinere* createCota(const char* adresa, int nrAp, int nrPers,
	int an, int luna, float intretinere) {

	CotaIntretinere* c = (CotaIntretinere*)malloc(sizeof(CotaIntretinere));


	c->adresa = (char*)malloc((strlen(adresa) + 1));
	strcpy(c->adresa, adresa);

	c->nrApartament = nrAp;
	c->nrPersPerApartament = nrPers;
	c->an = an;
	c->luna = luna;
	c->intretinere = intretinere;

	return c;
}

ListNode* createElement(CotaIntretinere* cota) {
	ListNode* nod = (ListNode*)malloc(sizeof(ListNode));

	nod->info = cota;
	nod->next = NULL;

	return nod;
}

void initHashTable(HashTable& ht, int dim) {
	ht.size = dim;
	ht.noEl = 0;

	ht.buckets = (ListNode**)malloc(sizeof(ListNode*) * dim);
	memset(ht.buckets, NULL, sizeof(ListNode*) * dim);

}

int fHash(int nrAp, int dim) { //k mod m, m treb sa fie un nr prim, cat mai aproape de dim de chei.. k mod 2 => 0,1 | daca am 10 mil de chei, ma duc doar in 2 valori...
	int index = nrAp % dim;
	return index;
}



void insertElement(ListNode* &head, ListNode* node) {

	if (head != NULL) {
		node->next = head;
	}
	head = node;
}

//void insertHT(HashTable ht, Rezervare value) {
//	//1. get index position for inserting
//	int index = fHash(value.denumire, ht.size);
//
//	//2.create new elem.
//	ListNode* node = createElement(value);
//
//	//3. insert created el into ht
//	ListNode* list = ht.buckets[index];   //pb aici
//	insertElement(list, node);  //inserez nodul creat la pozitia cu indexul general
//	ht.buckets[index] = list;  //pun lista la indexul respectiv, dupa ce am adaugat
//
//
//	ht.noEl++;		//* cu ptr
//	//ca sa se faca modificarea?
//
//}

//doinea punea * in loc de &

void insertHT(HashTable& ht, CotaIntretinere* value){ //nu uita &
	//1
	int index = fHash(value->nrApartament, ht.size);

	//2
	ListNode* node = createElement(value);

	//3
	ListNode* list = ht.buckets[index];
	insertElement(list , node);
	ht.buckets[index] = list;

	ht.noEl++; 
	/*(*ht).noEl++;*/



}




//char* adresa;
//int nrApartament;
//int nrPersPerApartament;
//int an;
//int luna;
//float intretinere;

void printHT(HashTable ht) {
	
	for (int i = 0; i < ht.noEl; i++) {

		ListNode* crt = ht.buckets[i];


		while (crt != NULL) {
			printf("\nadresa: %s", crt->info->adresa);
			printf("\nnr ap: %d", crt->info->nrApartament);
			printf("\nNr pers: %d", crt->info->nrPersPerApartament);
			printf("\nAn: %d", crt->info->an);
			printf("\nLuna: %d", crt->info->luna);
			printf("\nIntretinere: %f", crt->info->intretinere);

			printf("\n");


			crt = crt->next;
		}
	}
}

float valIntretinere(HashTable ht ,int nrAp, int an, const char* adresa) {
	//1
	float value = 0;
	int index = fHash(nrAp, ht.size);

	//2
	ListNode* list = ht.buckets[index];
	while (list && (list->info->nrApartament != nrAp)) {
		list = list->next;
	}


	if (list) {
		value = list->info->intretinere * 12;
	}


	return value;

}


//4
int numarCoteIntretinere(HashTable ht, float prag) {
	int c = 0;

	for (int i = 0; i < ht.noEl; i++) {
		ListNode* crt = ht.buckets[i];

		while (crt != NULL) {
			if (crt->info->intretinere > prag)
				c++;
			crt = crt->next;
		}
	}

	return c;
}


void sterge(ListNode* &head) {
	if (head != NULL) {
		if (head->next == NULL) {
			head = NULL;
		}
		else {
			head = head->next;
			
		}
	}

}


void deleteHT(HashTable& ht, int nrAp, const char* adresa) {
	int index = fHash(nrAp, ht.size);
	


	if (ht.buckets[index] != NULL) 
	{

		/*ListNode* crt = ht.buckets[index];*/
		ListNode* tmp = ht.buckets[index];

		while (tmp != NULL) {
			if (strcmp(adresa, tmp->next->info->adresa) == 0) {
				tmp->next = tmp->next->next;
			}

			tmp = tmp->next;
			
		}

		/*ht.buckets[index] = NULL;*/

	}
}


void main() {
	HashTable ht;

	initHashTable(ht,6);
	CotaIntretinere* c1 = createCota("A", 1, 2, 99, 4, 1023);
	CotaIntretinere* c2 = createCota("B", 2, 2, 99, 4, 1000);
	CotaIntretinere* c3 = createCota("C", 3, 2, 99, 4, 1000);
	CotaIntretinere* c4 = createCota("D", 4, 2, 99, 4, 1000);
	CotaIntretinere* c5 = createCota("E", 5, 2, 99, 4, 1000);
	CotaIntretinere* c6 = createCota("F", 2, 2, 99, 4, 1000);


	//1
	insertHT(ht, c1);
	insertHT(ht, c2);
	insertHT(ht, c3);
	insertHT(ht, c4);
	insertHT(ht, c5);
	insertHT(ht, c6);


	//2
	printHT(ht);


	//3
	float rez = valIntretinere(ht, 1, 99, "A");
	printf("\n%5.2f", rez);

	int contor = numarCoteIntretinere(ht, 1000);
	printf("\n-----------4--------------\n");
	printf("\n%d", contor);

	printf("\n-----------5--------------\n");
	deleteHT(ht, 2, "B");



	printHT(ht);



}