#include "stdio.h"
#include "malloc.h"
#include "string.h"



struct Trainee {
	char* student_name;
	float points;
	int test_code;
};

struct Exam {
	int test_code;
	float min_no_of_points;

	int no_0f_total_trainees;
	Trainee* *trainees;
};

struct ListNode {
	Exam info;
	ListNode* next;
};

Trainee createTrainee(const char* name, float points, int code) {
	Trainee t;
	t.student_name = (char*)malloc(strlen(name) + 1);
	strcpy(t.student_name, name);

	t.points = points;
	t.test_code = code;

	return t;
}


Exam createExam(int code, float min, int number, Trainee** trainees)
{
	Exam exam;
	exam.test_code = code;
	exam.no_0f_total_trainees = number;
	exam.min_no_of_points = min;
	exam.trainees = (Trainee**)malloc(number * sizeof(Trainee*));
	for (int i = 0; i < number; i++)
	{
		exam.trainees[i] = NULL;
	}
	return exam;
}


ListNode* createNode(Exam exam) {

	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->next = NULL;
	newNode->info = exam;

	return newNode;
}


void insertNode(ListNode*& head, Exam  exam) {

	ListNode* newNode = createNode(exam);
	
	if (head == NULL) {
		head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode; //ok
	}

}


void print(ListNode* head) {
	if (head == NULL) {
		printf("\nNu sunt examene");
	}
	else
	{
		ListNode* crt = head;
		while (crt != NULL) {
			printf("\nTest code: %d", crt->info.test_code);
			printf("\nMin nr of points: %f", crt->info.min_no_of_points);
			printf("\nNumber of trainees: %d", crt->info.no_0f_total_trainees);
			if (crt->info.no_0f_total_trainees > 0)
			{
				for (int i = 0; i < crt->info.no_0f_total_trainees; i++) {

					printf("\nTest code: %d", crt->info.trainees[i]->test_code);
					printf("\nStudent name: %s", crt->info.trainees[i]->student_name);
					printf("\nNo of points: %d", crt->info.trainees[i]->points);
				}
			}
			crt = crt->next;
		}
	}
}




void main() {

	ListNode* head = NULL;

	Exam e1 = createExam(1, 2, 3, NULL);
	Exam e2 = createExam(2, 3, 5, NULL);

	insertNode(head, e1);
	insertNode(head, e2);

	print(head);


	Trainee t1 = createTrainee("Pop Ioana", 7, 1);
	Trainee t2 = createTrainee("Ion Ion", 3, 1);


	
}