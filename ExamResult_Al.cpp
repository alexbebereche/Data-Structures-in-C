#include "stdio.h"
#include "string.h"
#include "malloc.h"

struct ExamResult {
	char* name;
	float points;
	int code;
	float totalPoints;
};

struct ListNode {
	ListNode* next;
	ExamResult* exam; //am ales sa folosesc ptr...

};

ExamResult* createExam(const char* name, float points, int code, float totalPoints) {
	ExamResult* ex = (ExamResult*)malloc(sizeof(ExamResult));

	//nu uita sa aloci memoria
	ex->name = (char*)malloc(sizeof(name) + 1);
	strcpy(ex->name, name);

	ex->points = points;
	ex->code = code;
	ex->totalPoints = totalPoints;

	return ex;
}

ListNode* createColet(ExamResult* exam) {
	ListNode* nou = (ListNode*)malloc(sizeof(ListNode));

	nou->exam = exam;
	nou->next = NULL;

	return nou;

}

void insertExam(ListNode* &head, ExamResult* exam) {
	ListNode* newNode = createColet(exam);

	ListNode* crt = head;
	//lista e null
	if (head == NULL) {
		newNode->next = newNode;
		head = newNode;
		//return; //?
	}
	else {
		newNode->next = head;
		//ajung pe "tail"
		while (crt->next != head) {
			crt = crt->next;
		}
		crt->next = newNode;

		head = newNode;
	}

}

//incepusem sa scriu fct asta in main..
//e scrisa gresit in celalalt cod
//4
int counterPassed(ListNode* head) {
	ListNode* crt = head;
	int c = 0;

	if (head == NULL) {
		printf("Empty");
	}
	else {
		do {
			if ((float)(crt->exam->points / crt->exam->totalPoints) >= 0.7) {
				c++;
			}
			crt = crt->next;
		} while (crt != head);
	}

	return c;
}

//3
void print(ListNode* head) {
	ListNode* crt = head;

	/*while (crt->next != head) {
		printf("\nname: %s", crt->exam->name);
		printf("\npoints: %f", crt->exam->points);
		printf("\ncode: %d", crt->exam->code);
		printf("\nTotal points: %f\n", crt->exam->totalPoints);
		
		crt = crt->next;
	}
	printf("\nname: %s", crt->exam->name);
	printf("\npoints: %f", crt->exam->points);
	printf("\ncode: %d", crt->exam->code);
	printf("\nTotal points: %f\n", crt->exam->totalPoints);*/

	//NEELEGANT

	do {
		printf("\nname: %s", crt->exam->name);
		printf("\npoints: %f", crt->exam->points);
		printf("\ncode: %d", crt->exam->code);
		printf("\nTotal points: %f\n", crt->exam->totalPoints);

		crt = crt->next;
	} while (crt != head);

}


//5
//nu intorc rezultatul, dar modific lista, nu doar il afisez
void deleteExamResult(ListNode* & head, const char* name) {
	if (head == NULL) {
		printf("\nempty list");
	}
	else {
		ListNode* crt = head;
		//un nod
		if ((head->next == head) && (strcmp(head->exam->name, name) == 0)) {
			head = NULL;
			//return; //?
		}
		//remove the head?
		else if (strcmp(crt->exam->name, name) == 0) {
			ListNode* tmp = head->next;

			while (tmp->next != head) {
				tmp = tmp->next;
			}
			head = head->next;  //ok
			tmp->next = crt->next;

		}
		else {

			//daca next trebuie extras, lui next ii dau next->next
			crt = head;

			do {
				//aici am sters
				if (strcmp(crt->next->exam->name, name) == 0) {
					crt->next = crt->next->next;
				}

				crt = crt->next;

			} while (crt->next != head);


			//de ce?
			//am verificat din nou head-ul...
			//nu cred ca era nevoie
			if (strcmp(crt->next->exam->name, name) == 0) {
				crt->next = head;
			}


		}
	}
}



void main() {
	ListNode* head = NULL;
	ExamResult* e1 = createExam("Mama", 40, 1, 100);
	ExamResult* e2 = createExam("Ma-sii", 100, 1, 100);
	ExamResult* e3 = createExam("Tata", 50,3, 100);
	ExamResult* e4 = createExam("B", 10, 1, 30);
	ExamResult* e5= createExam("C", 50, 3, 50);


	insertExam(head, e1);
	insertExam(head, e2);
	insertExam(head, e3);
	insertExam(head, e4);
	insertExam(head, e5);
	print(head);

	//4
	printf("\n%d students passed with at least 70%",counterPassed(head));

	//5
	printf("\nSterge examenul studentului: ");
	//citirea unui string de la tastatura...
	char student[100];
	scanf("%s", student);

	deleteExamResult(head, student);
	print(head);
}