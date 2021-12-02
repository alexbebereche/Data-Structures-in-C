#include "stdlib.h"
#include "stdio.h"

//struct Person {
//	int age;
//};
//
//struct Vehicle {
//	double miles;
//};


// fct that works with pointers to void
// wont know what it adds, so return type is also pointer to void
void* sumArray(void* arrayValues, int noEl, int size_t) { // size_t is type
	if (size_t == sizeof(int)) {

		int* sum = (int*)malloc(sizeof(int)/* * noEl*/);
		*sum = 0;

		for (int i = 0; i < noEl; i++) {
			*sum += ((int*)arrayValues)[i];
			//*sum += *(((int*)arrayValues) + i);
		}

		return sum;

	}
	else {
		
		double* sum = (double*)malloc(sizeof(double)/* * noEl*/);
		*sum = 0.0;

		for (int i = 0; i < noEl; i++) {
			*sum += ((double*)arrayValues)[i];
			//*sum += *(((int*)arrayValues) + i);
		}

		return sum;
		

	}
}

// generalize the no. of params, must have the no. of arguments
double sumArray(int noArgs, ...) {
	
	va_list ptrStack; // an iterator/ or a ptr to a char, in our case, its a ptr to a stack
	__crt_va_start(ptrStack, noArgs); // init the ptr to stack with the no of args

	double sum = 0.0;

	for (int i = 0; i < noArgs; i++) {
		sum += __crt_va_arg(ptrStack, double);
	}

	return sum;

}

void main() {
	
	//int noEl= 4;
	//int noBytes = noEl * sizeof(int);
	//int* px = (int*)malloc(noBytes); // malloc returns void, need to force a cast
	//px[0] = 65; //16706
	//px[1] = 66;

	//*(px + 2) = 67; // * to refer the content using pointer operations
	//*(px + 3) = 68;

	//char* pc = (char*)px;
	//printf("Value: %s", pc);

	//px[4] = 8;
	//px[10] = 9;
	//// can do it, but wont be able to read
	//printf("Val from index 13: %i", px[12]);




	// ptr to void, capable of storing other pointers to elements like vehicles and persons
	// capable of storing other pointers -> 
	//void* ptr; // matrix

	int ageArray[] = {21, 25, 23, 26};
	double milesArray[] = { 100.3, 134.7, 160.3, 390.5 };

	// how can i know how many els i have in an array?
	// the opposite of allocation
	void* resultInt = sumArray(ageArray, sizeof(ageArray) / sizeof(int), sizeof(int));
	void* resultDouble = sumArray(milesArray, sizeof(milesArray) / sizeof(double), sizeof(double));

	printf("\nSum of ints: %i", *(int*)resultInt);  // uitasem dereference...
	printf("\nSum of doubles: %f", *(double*)resultDouble);


	printf("\nSum of values: %f \n", sumArray(3, 1.1, 2.2, 3.3));
	printf("Sum of values: %f \n", sumArray(5, 1.1, 2.2, 3.3, 4.4, 5.5));

	// make something like a fct, capable of making the sum of one of the arrays



}