#include "stdio.h"
#include "malloc.h"
#include "string.h"


struct Rezervare {
	unsigned int idRezervare;
	char* denumireHotel;
	unsigned char nrCamere;
	char* numeClient;
	char* perioada;
	float suma;

};

struct ListNode{
	Rezervare rezervare;
	ListNode* next;
};

struct HashTable {
	ListNode* *buckets = NULL;
	int noEl = 0;
};


Rezervare createRezervare(unsigned int id, const char* den, unsigned char nr, const char* nume, const char* per, float suma) {

	Rezervare r;

	r.idRezervare = id;
	r.suma = suma;
	r.denumireHotel = (char*)malloc(sizeof(den) + 1);
	r.numeClient = (char*)malloc(sizeof(nume) + 1);
	r.perioada = (char*)malloc(sizeof(per) + 1);

	strcpy(r.denumireHotel, den);
	strcpy(r.numeClient, nume);
	strcpy(r.perioada, per);

	return r;

}

ListNode* createElement(Rezervare r) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->rezervare = r;
	newNode->next = NULL;

	return newNode;

}

int getHash(const char* nume, int dim) {
	
	int asciiSUM = 0;
	for (int i = 0; i < strlen(nume); i++)
		asciiSUM += nume[i];
	return asciiSUM % dim;
}


void insertNode(ListNode* &head, Rezervare r) {//* &, ListNode*, &-> modific...
	
	ListNode* newNode = createElement(r);

	newNode->next = head;
	head = newNode;


}

HashTable createHashTable(int n) {

	HashTable ht;

	ht.noEl = n;
	ht.buckets = (ListNode**)malloc(sizeof(ListNode*) * n);  //NU uita n
	/*for (int i = 0; i < n; i++) {
		ht.buckets[i] = NULL;
	}*/

	memset(ht.buckets, NULL, sizeof(ListNode*) * n);   //asa?

	return ht;
}

void insertRezervare(HashTable ht, Rezervare r) {

	int index = getHash(r.denumireHotel, ht.noEl);

	ListNode* list = ht.buckets[index];
	insertNode(list, r);

	ht.buckets[index] = list;

	//noel ++?

}


//3 - traversare
void print(HashTable hashTable)
{

	for (int i = 0; i < hashTable.noEl; i++)
	{
		ListNode* current = hashTable.buckets[i];

		while (current != NULL)
		{
			printf("\nId rezervare: %d", current->rezervare.idRezervare);
			printf("\nDenumire hotel: %s", current->rezervare.denumireHotel);
			printf("\nNr camere: %u", current->rezervare.nrCamere);
			printf("\nNume client: %s", current->rezervare.numeClient);
			printf("\nPerioada: %s", current->rezervare.perioada);
			printf("\nSuma: %f", current->rezervare.suma);
			printf("\n");

			current = current->next;
		}
	}
}

void deleteHT(HashTable ht, const char* nume) {

	int index = getHash(nume, ht.noEl); //iau indexul de la poz det de fct hash pt numele primit ca parametru

	if (ht.buckets[index]) { //daca avem valori cu hash ul acela...in poz aia

		ListNode* crt = ht.buckets[index];
		ListNode* tmp = crt;  //dc = crt? ma rog

		while (tmp != NULL){

			//e bine, tmp devine urmatorul, sterg actual, crt devine urmatorul
			tmp = crt->next;
			free(crt);
			crt = tmp;

		}

		ht.buckets[index] = NULL;  //!
	}



}

//4
int camereDisponibile(HashTable ht, const char* hotel,  const char* perioada) {

	int index = getHash(hotel, ht.noEl);
	int nrCamere = 0;
	if (ht.buckets[index]) {

		ListNode* crt = ht.buckets[index];
		  

		while (crt != NULL) {
			if (strcmp(perioada, crt->rezervare.perioada)) {
				nrCamere += ht.buckets[index]->rezervare.nrCamere;
				return nrCamere;
			}
			crt = crt->next;
			
		}



	}

	return nrCamere;
}

void main() {

	HashTable hashTable = createHashTable(101);
	const char* den1 = "Mama";
	const char* nume1 = "Alexa";
	const char* per1 = "01/02-05/02";

	Rezervare r1 = createRezervare(1, den1, 10, nume1, per1, 200);
	ListNode* head = NULL;
	insertRezervare(hashTable, r1);
	Rezervare r2 = createRezervare(2, "Piatra Craiului", 97, "Pop Ion", "05/03-10/03", 500);
	insertRezervare(hashTable, r2);
	Rezervare r3 = createRezervare(3, "Pescarusul", 2, "Popovici Ionela", "05/05-10/06", 5000);
	insertRezervare(hashTable, r3);
	Rezervare r4 = createRezervare(4, "Ursulica", 4, "Marin Marin", "05/03-10/03", 600);
	insertRezervare(hashTable, r4);
	Rezervare r5 = createRezervare(5, "Pescarusul", 2, "Traian", "05/03-10/03", 500);
	insertRezervare(hashTable, r5);

	print(hashTable);

	printf("\nStergere!");
	
	
	//5
	deleteHT(hashTable, "Pescarusul");
	print(hashTable);

	//rev
	int nr = camereDisponibile(hashTable, "Ursulica", "05/03-10/03");
	printf("\n\n\n%d", nr);


}

