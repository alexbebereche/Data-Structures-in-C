#include "stdio.h"
#include "malloc.h"
#include "string.h"

//LIFO - stiva
struct Team {
	int code;
	char* captain;
	int topic;
	int noStudents;
	float points;

};

struct ListNode {
	Team* team;
	ListNode* next;
};

struct Array {
	Team* *teams = NULL;
};

Team* createTeam(int code, const char* captain, int topic,
	int noStudents, float points) {
	Team* team = (Team*)malloc(sizeof(Team));

	team->code = code;

	team->captain = (char*)malloc(strlen(captain) + 1);
	strcpy(team->captain, captain);

	team->topic = topic;
	team->noStudents = noStudents;
	team->points = points;

	return team;


}

ListNode* createNode(Team* team) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->team = team;
	newNode->next = NULL;

	return newNode;
}


void printTeam(Team* team) {
	printf("\nCode: %d", team->code);
	printf("\nCaptain: %s", team->captain);
	printf("\nTopic: %d", team->topic);
	printf("\nNo. Students: %d", team->noStudents);
	printf("\nPoints: %f\n", team->points);

}
//1
void insertTeam(ListNode* &head, Team* team) {
	ListNode* newNode = createNode(team);

	if (head == NULL) {
		head = newNode;
		newNode->next = NULL;
	}
	else {
		ListNode* crt = head;
		while (crt->next != NULL) {
			crt = crt->next;
		}
		crt->next = newNode;
		newNode->next = NULL;
	}

}

//void insertTeam(ListNode* &head, Team* team) {
//	ListNode* newNode = createNode(team);
//
//	if (head == NULL) {
//		head = newNode;
//		newNode->next = NULL;
//	}
//	else {
//		newNode->next = head;
//		head = newNode->next;
//	}
//
//}



//2
//Team* pop(ListNode* &stack) {
//	Team* rez = stack->team;
//
//	ListNode* aux = stack;
//	stack = stack->next;
//	free(aux);   //nu uita de free!
//
//	return rez;
//}

Team* pop(ListNode* &head) {
	ListNode* crt = head;

	Team* t = NULL;
	if (head->next != NULL) {
		while (crt->next->next != NULL) {
			crt = crt->next;
		}


		t = crt->next->team;
		free(crt->next);
		crt->next = NULL;

		
	}
	else {
		if (head != NULL) {
			t = head->team;
			head = NULL;
		}
	}

	return t;
}

//Team* pop(ListNode* &head) {
//	ListNode* crt = head;
//
//	Team* t = NULL;
//	if (head != NULL) {
//
//
//		while (crt->next->next != NULL) { //nu poti sa ai NULL->next...
//			crt = crt->next;
//		}
//
//
//		t = crt->next->team;
//		free(crt->next);
//		crt->next = NULL;
//
//
//
//
//	}
//	else {
//		t = crt->team;
//
//	}
//
//
//	return t;
//}


//Team* pop(ListNode* &head) {
//	ListNode* crt = head;
//
//	Team* t = NULL;
//	if (head->next->next != NULL) {
//
//
//		while (crt->next->next != NULL) { //nu poti sa ai NULL->next...
//			crt = crt->next;
//		}
//
//
//		t = crt->next->team;
//		free(crt->next);
//		crt->next = NULL;
//
//
//
//
//	}
//	else {
//		if (crt->next != NULL) {
//			t = crt->next->team;
//			free(crt->next);
//			crt->next = NULL;
//		}
//		else {
//			t = crt->team;
//			
//
//		}
//
//		
//
//	}
//
//
//	return t;
//}



//2
//void displayTeams(ListNode* head){
//	ListNode* crt = head;
//
//	if (head == NULL) {
//		printf("\nEmpty stack");
//	}
//	else {
//
//		ListNode* crt = head;
//		while (crt->next != NULL) {
//
//			printf("\n%d", crt->team->code);
//			crt = crt->next;
//	
//
//		}
//		printf("\n%d", crt->team->code);
//	}
//}


void printStack(ListNode* &stack) {
	while (stack) {
		Team* team = pop(stack);
		printTeam(team);
		/*free(team->captain);*/
		
	}

	/*Team* t = pop(stack);
	printTeam(t);*/
}

//3
Array totalPoints(ListNode* head, float points) {
	Array vector;

	

	ListNode* crt = head;
	int c = 0, k = 0;
	while (crt != NULL) {
		c++;

		if (crt->team->points > points) {
			k++;
		}
		crt = crt->next;
	}

	vector.teams = (Team**)malloc(sizeof(Team*) * k);
	memset(vector.teams, NULL, sizeof(Team*) * k);

	crt = head;
	for (int i = 0; i < c; i++) {
		vector.teams[i] = crt->team;
		if (vector.teams[i]->points > crt->team->points) {
			vector.teams[k++] = vector.teams[i];
		}
		crt = crt->next;
	}


	return vector;
}



Array creareVector(ListNode* head, int& c) {
	Array vector;



	ListNode* crt = head;
	c = 0;
	while (crt != NULL) {
		c++;
		crt = crt->next;
	}

	vector.teams = (Team**)malloc(sizeof(Team*) * c);
	memset(vector.teams, NULL, sizeof(Team*) * c);

	crt = head;
	for (int i = 0; i < c; i++) {
		vector.teams[i] = crt->team;
		crt = crt->next;
	}


	return vector;
}

//4
int greaterThanAverage(ListNode* head) {
	ListNode* crt = head;

	int greater = 0;
	int c = 0;
	float avg = 0, max = -1, sum = 0;


	if (head == NULL) {
		return 0;
	}
	else {
		while (crt != NULL) {
			if (crt->team->points > max) {
				max = crt->team->points;
			}
			c++;
			sum = sum + crt->team->points;
			crt = crt->next;
		}

		avg = sum / c;
		crt = head;

		while (crt != NULL) {
			if (crt->team->points > avg) {
				greater++;
				/*crt = crt->next;*/
			}

			crt = crt->next;

		}



	}
	return greater;
}

//5



void main() {
	ListNode* head = NULL;
	Team* t1 = createTeam(1, "A", 10, 30, 100);
	Team* t2 = createTeam(2, "B", 11, 40, 200);
	Team* t3 = createTeam(3, "C", 12, 50, 300);
	Team* t4 = createTeam(4, "D", 13, 60, 400);
	Team* t5 = createTeam(5, "E", 14, 70, 500);

	//printf("%d", t1->code);


	//push...
	insertTeam(head, t1);
	insertTeam(head, t2);
	insertTeam(head, t3);
	insertTeam(head, t4);
	insertTeam(head, t5);

	/*int i = greaterThanAverage(head);*/

	//trebuie 5,4,3,2,1 ...
	ListNode* copie = head;

	//2
	printStack(copie);

	if (head == NULL) {
		printf("\nasdasd");
	}
	else {
		printf("\nnuu");
	}


	//3 - imi "stricasem" head-ul...
	copie = NULL;
	insertTeam(copie, t1);
	insertTeam(copie, t2);
	insertTeam(copie, t3);
	insertTeam(copie, t4);
	insertTeam(copie, t5);
	int c = 0;
	Array array = creareVector(copie, c);
	printf("\n\n\n%f", array.teams[0]->points);
	/*printf("\n\n\n%f", array.teams[1]->points);*/
	
	printf("\n\n-----");

	for (int i = 0; i < c; i++) {
		printTeam(array.teams[i]);
	}

	//4
	int i = greaterThanAverage(copie);
	printf("\ngreater than avg: %d\n", i);


	
}