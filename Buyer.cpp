#include "stdio.h"
#include "malloc.h"
#include "string.h"

//Simple chained list
struct Buyer {
	char* buyerName;
	float budget;

};



//simple chained list
struct ListNode {
	Buyer info;
	ListNode* next;

};

//2
struct Apartment {
	int code;
	int noRooms;
	float surfaceSize;
	float pricePerSquareMeter;
	ListNode* headBuyers;   //simple chained list
};

//one-dimensional array structure
struct Array {
	Apartment* aparments;  
	int noValues;		//need this
};


//create and init

ListNode* createNode(Buyer buyer) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->info = buyer;
	newNode->next = NULL;
	
	return newNode;
}

Buyer initBuyer(const char* name, float budget) {
	Buyer buyer;

	buyer.buyerName = (char*)malloc(strlen(name) + 1);
	strcpy(buyer.buyerName, name);
	buyer.budget = budget;

	return buyer;

}


//print

void printBuyer(Buyer buyer) {

	printf("\nbuyer's name: %s", buyer.buyerName);
	printf("\nbuyer's budget: %f", buyer.budget);

}


//4
void insertBuyer(ListNode*& head, Buyer buyer){          //grija mare aici: *&
	ListNode* newNode = createNode(buyer);

	if (head == NULL) {
		head = newNode;
		//return;			//rev

		
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}

Apartment initApartment(int code, int noRooms, float surface, float price, ListNode* head)
{
	Apartment ap;

	ap.code = code;
	ap.noRooms = noRooms;
	ap.surfaceSize = surface;
	ap.pricePerSquareMeter = price;
	ap.headBuyers = head;

	return ap;

}

void printArray(Array array) {

	for (int i = 0; i < array.noValues; i++) {
		printf("cod %d", array.aparments[i].code);
		printf("rooms %d", array.aparments[i].noRooms);
		printf("size %f", array.aparments[i].surfaceSize);
		printf("cod %f", array.aparments[i].pricePerSquareMeter);

		if (array.aparments[i].headBuyers != NULL) {

			ListNode* crt = array.aparments[i].headBuyers;


			while (crt) {
				printBuyer(crt->info);
				crt = crt->next;
			}
		}
	}
}


//3
Array insertArray(Array array, Apartment apartment) {

	Array copy;

	if (array.noValues > 0) {
		copy.noValues = array.noValues + 1;  //inserez,  + 1
		copy.aparments = (Apartment*)malloc((array.noValues + 1) * sizeof(Apartment));
		for (int i = 0; i < array.noValues + 1; i++) {
			copy.aparments[i] = array.aparments[i];
		}

		copy.aparments[array.noValues] = apartment;
	}
	else {
		copy.noValues = 1;
		copy.aparments = (Apartment*)malloc(sizeof(Apartment));
		copy.aparments[0] = apartment;
	}

	return copy;
}


//5
void display(Array array, float area) {
	for (int i = 0; i < array.noValues; i++) {
		if (array.aparments[i].headBuyers != NULL) {
			if (array.aparments[i].surfaceSize > 0) {
				printf("\napp code: %d", array.aparments[i].code);   //display anyway

				ListNode* crt = array.aparments[i].headBuyers;
				while (crt != NULL) {
					if (crt->info.budget >= (array.aparments[i].surfaceSize*array.aparments[i].pricePerSquareMeter))  //formula, usor de dedus...
					{
						printf("\nclient name: %s", crt->info.buyerName);
					}
					crt = crt->next;
				}

			}
		}
		else {
			printf("\napp with code %d has no potential customers", array.aparments[i].code);
		}
	}
}

void main() {
	//Buyer* ex = initBuyer();
	//if (ex->buyerName)
	//	printf("sadad");
	//else
	//	printf("ASdasasssss");


	Buyer b1 = initBuyer("Tom", 200000);
	Buyer b2 = initBuyer("Tim", 270000);
	Buyer b3 = initBuyer("Pom", 200800);
	Buyer b4 = initBuyer("Lom", 200500);
	Buyer b5 = initBuyer("Mom", 201200);

	ListNode* head = NULL;

	insertBuyer(head, b1);
	insertBuyer(head, b2);
	insertBuyer(head, b3);
	insertBuyer(head, b4);
	insertBuyer(head, b5);

	printf("%f", head->info.budget);



	Apartment a1 = initApartment(1, 3, 200, 90, NULL);
	Apartment a2 = initApartment(2, 2, 100, 10, NULL);
	Apartment a3 = initApartment(3, 1, 250, 70, NULL);
	Apartment a4 = initApartment(4, 4, 290, 50, NULL);
	Apartment a5 = initApartment(5, 3, 230, 50, head);

	printf("\n%d", a1.code);

	Array array;
	array.noValues = 0;
	array.aparments = NULL;

	array = insertArray(array, a1);
	array = insertArray(array, a2);
	array = insertArray(array, a3);
	array = insertArray(array, a4);
	array = insertArray(array, a5);

	printArray(array);

	printf("----------------\n");

	display(array,100);
}