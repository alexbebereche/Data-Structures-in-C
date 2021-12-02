#include <stdio.h>
#include<malloc.h>
#include<string.h>

struct Colet {
	int id;
	char* expeditor;
	char* destinatar;
	float greutate;

};

//lista simpla circulara
struct ListNode {
	//nu asa
	/*ListNode* prev;*/



	/*Colet* colet;*/

	Colet colet; //mai bine
	ListNode* next;

};

Colet createColet(int id, const char* exp, const char* des,
	float g) {
	Colet colet;

	colet.id = id;

	colet.expeditor = (char*)malloc(sizeof(exp) + 1);
	strcpy(colet.expeditor, exp);

	colet.destinatar = (char*)malloc(sizeof(des) + 1);
	strcpy(colet.destinatar, des);

	colet.greutate = g;

	return colet;
}

ListNode* createNode(Colet colet) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->colet = colet;
	newNode->next = NULL;

	return newNode;

}

void insertColet(ListNode* &head, Colet colet) {
	ListNode* newNode = createNode(colet); //l-am facut nod...

	if (head == NULL) {
		head = newNode;
		head->next = head;  //circular, nu uita
		//head->next NU POATE fi null intr-o lista de genul
	}
	else {
		newNode->next = head;
		ListNode* crt = head;
		while (crt->next != head) {  // != head aici!!!!e lista circulara
			crt = crt->next;
		}
		crt->next = newNode;

		//nu uita, schimba head-ul
		head = newNode;
	}
	//nice


}


//3
void printColet(Colet colet)
{
	printf("\n");
	printf("\nId colet: %d", colet.id);
	printf("\nExpeditor: %s", colet.expeditor);
	printf("\nDestinatar: %s", colet.destinatar);
	printf("\nGreutate: %f", colet.greutate);
}

//3
void printList(ListNode* head) {
	ListNode* crt = head; //crt cam mereu = head...

	if (head == NULL) {
		printf("gol\n");
	}
	else {
		/*while (crt->next != head) {
			printColet(crt->colet);
			crt = crt->next;
		}
		printColet(crt->colet);*/

		//NEELEGANT mai sus

		do {
			printColet(crt->colet);
			crt = crt->next;
		} while (crt != head);
	}

	//free(crt); // dont free in circular linked list

}


//4 - de revazut
Colet deleteNode(ListNode* &head, int id){
	//Colet colet = NULL; // nu merge pt ca nu e pointer!
	
	Colet colet = createColet(0, "nimeni", "alt nimeni", 0);

	ListNode* crt = head;
	if (head == NULL) {
		return colet; // return;
	}
	
	//un singur nod - mai mult
	if ((head->colet.id == id) && (head->next == head)) {
		colet = head->colet;  //cam confuz, cu numele lol //extrag
		//head = NULL; // nu asa...dar ma rog free(head)
		free(head);
		return colet;
	}

	//daca e head-ul...si sunt mai multe noduri
	if (head->colet.id == id) {
		colet = head->colet;
		//acum, ce fac cu head-ul?

		while (crt->next != head) {
			crt = crt->next;
		}
		crt->next = head->next;
		head = head->next;

		return colet;
	}

	//crt = head; //de ce?
	//else..
	while (crt->next->next != head) {
		if (crt->next->colet.id == id) {
			colet = crt->next->colet;
			crt->next = crt->next->next;
		}
		crt = crt->next;
	}
	//free nu trebuie facut?...

	if (crt->next->colet.id == id) {
		colet = crt->next->colet;
		crt->next = head;
	}

	return colet;





}

void vector(ListNode* head, const char* dest)
{
	int nr = 0;
	ListNode* current = head; //ok

	//ok
	do
	{
		if (strcmp(current->colet.destinatar, dest) == 0)
			nr++;

		current = current->next;
	} while (current != head);

	//vector alocat dinamic
	//am parcurs o data ca sa pot aloca
	Colet* colete = (Colet*)malloc(sizeof(Colet)*nr);
	int poz = 0;

	current = head;

	//ii adaug in vector..
	do
	{
		if (strcmp(current->colet.destinatar, dest) == 0)
		{
			colete[poz] = current->colet;
			poz++;
		}
		current = current->next;

	} while (current != head);


	//sortare prin interschimbare
	for (int i = 0; i < nr - 1; i++)
		for (int j = i + 1; i < nr; j++)
		{
			if (colete[i].greutate < colete[j].greutate)
			{
				Colet aux = colete[i];
				colete[i] = colete[j];
				colete[j] = aux;
			}
		}

	for (int i = 0; i < nr; i++)
		printColet(colete[i]);
}

void v(ListNode* head, const char* destinatar) {
	int nr = 0;
	ListNode* crt = head;

	do {
		if (strcmp(crt->colet.destinatar, destinatar) == 0) {
			nr++;
		}

		crt = crt->next;
	} while (crt != head);

	Colet* vector = (Colet*)malloc(sizeof(Colet) * nr);


	//reset
	crt = head;
	int i = 0;
	do {
		if (strcmp(crt->colet.destinatar, destinatar) == 0) {
			vector[i++] = crt->colet;
		}

		crt = crt->next;
	} while (crt != head);

	for (int i = 0; i < nr - 1; i++) {
		for (int j = 1; j < nr; j++) {
			
			if (vector[i].greutate < vector[j].greutate) {
				Colet aux = vector[i];
				vector[i] = vector[j];
				vector[j] = aux;
			}
		}
	}

	for (int i = 0; i < nr; i++)
		printColet(vector[i]);
}


void main() {

	Colet c1 = createColet(1, "Pop Popa", "Ion ion", 24);
	Colet c2 = createColet(2, "Tom Tom", "Iom iom", 4);
	Colet c3 = createColet(3, "Pop Popa", "Ana nama", 7);
	Colet c4 = createColet(4, "Tip top", "Ion ion", 2.4);
	Colet c5 = createColet(5, "Pop Popica", "Ion mona", 5);


	/*printf("%s", c4.destinatar);*/

	ListNode* head = NULL;
	insertColet(head, c1);
	insertColet(head, c2);
	insertColet(head, c3);
	insertColet(head, c4);
	insertColet(head, c5);

	printList(head);

	printf("\n\n------COlet sters:-\n\n");
	Colet sters = deleteNode(head, 4);
	printColet(sters);
	printf("\n\nlista dups stergere:");
	printList(head);


	printf("\n\nvector:");
	v(head, "Ion ion");
}

