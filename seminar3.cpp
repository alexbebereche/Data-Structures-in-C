#include "stdio.h"
#include "stdlib.h"
//#include "malloc.h"
#include "string.h"

#pragma warning(disable:4996)


// ADT - abstract data structure - ds that we define
// topic: how we can create new data types -> elements of those types, store them somewhere

enum VehicleType { CAR = 10, AIRPLANE = 20 };  // constant literals in which we declare the constant, then assign a value; 
// auto-assigned value - starting from 1; i see it actually starts from 0

union VehicleUsage {
	int noMiles;
	double flightHours;
};

// Why use union instead of a struct?
// Imagine a vehicle - have usage -- noMiles; flightHours;
// if we use noMiles, what about flightHours?
// will decide what type to use at that particular moment, at runtime
// 8B of mem, biggest data type from the declaration; they will be shared between noMiles and flightHours

struct Vehicle {
	char* name; // simple character, a ptr to a character; the most simple form a string could have; could also store an array of characters
	VehicleType type;
	VehicleUsage operation;


};

void printVehicles(Vehicle**, int );
Vehicle* buildVehicle(char*, int, double);

//void main() {
//	//VehicleUsage usage;
//
//	//usage.flightHours = 250.5;
//	////usage.noMiles = 40;
//	//usage.noMiles = 42134512;
//	////usage.flightHours = 250.5;
//
//	//printf("Integer: %i\n", usage.noMiles);
//	//printf("Integer: %Lf\n", usage.flightHours); // Lf - long float
//
//	// override the area...
//	// depends which we init first..., if init flightHours first, its good...
//
//	// first stage: overriden by the integer if init first integer and then the double, the 4B are replaced
//	// second stage: 
//
//
//	// read vehicles from a file, put them in an array, do some operations with the array
//	// how do we read this type of files?
//
//	// no of elements
//	// now, follow struct: 
//	// BOEING_747
//	// 20
//	// flight_hours: 10340.7
//
//	FILE* pFile = NULL;
//
//	pFile = fopen("Data.txt", "r"); // rb/wb
//	Vehicle* *vehicles = NULL;
//	int noEl = 0;
//
//	// we use...
//	// array of ptrs to Vehicle - one dimension
//	if (pFile) {
//		// array of ptrs to Vehicle - one dimension
//		// it can also be...:
//		
//		// --- pointer to a pointer to Vehicle type - scalar(no dimension)
//		// matrix of elements of Vehicle type - two dimensions
//
//		// Vehicle *** vehicles - cube of vehicles - 3D
//		/*Vehicle* *vehicles = NULL;*/
//
//		//const int noEl = 4; // needed to be const, can't be changed afterwards...cant change noEl at the runtime
//		//Vehicle* vehicles[noEl];
//		// how can we declare the same thing using a static allocation, lets say we know the no. of elements
//
//
//		// have the ptr, allocate the mem for it
//		// need to know how many elements, read it from the file
//		/*int noEl = 0;*/
//		fscanf(pFile, "%i", &noEl);
//
//		vehicles = (Vehicle**)malloc(sizeof(Vehicle*) * noEl);
//		int index = 0;
//
//		char buffer[50];
//		double operation = 0;
//		int type = 0;
//
//		while (!feof(pFile)) {
//			fscanf(pFile, "%s", buffer);
//			fscanf(pFile, "%i", &type);
//			fscanf(pFile, "%Lf", &operation);
//
//			Vehicle* vehicle = buildVehicle(buffer, type, operation);
//			vehicles[index++] = vehicle;
//		}
//
//		fclose(pFile);
//	}
//
//	printVehicles(vehicles, noEl);
//
//}

// Homework

void main() {

	FILE* pFile = NULL;

	pFile = fopen("Data2.txt", "r"); // rb/wb
	Vehicle* *vehicles = NULL;
	int noEl = 0;

	// we use...
	// array of ptrs to Vehicle - one dimension
	if (pFile) {
		// array of ptrs to Vehicle - one dimension
		// it can also be...:

		// --- pointer to a pointer to Vehicle type - scalar(no dimension)
		// matrix of elements of Vehicle type - two dimensions

		// Vehicle *** vehicles - cube of vehicles - 3D
		/*Vehicle* *vehicles = NULL;*/

		//const int noEl = 4; // needed to be const, can't be changed afterwards...cant change noEl at the runtime
		//Vehicle* vehicles[noEl];
		// how can we declare the same thing using a static allocation, lets say we know the no. of elements


		// have the ptr, allocate the mem for it
		// need to know how many elements, read it from the file
		/*int noEl = 0;*/

		//vehicles = (Vehicle**)malloc(sizeof(Vehicle*) * noEl);
		

		char buffer[50];
		double operation = 0;
		int type = 0;

		while (!feof(pFile)) {
			fscanf(pFile, "%s", buffer);
			fscanf(pFile, "%i", &type);
			fscanf(pFile, "%Lf", &operation);
			noEl++;

			/*Vehicle* vehicle = buildVehicle(buffer, type, operation);
			vehicles[index++] = vehicle;*/
		}

		fclose(pFile);

	}

	pFile = fopen("Data2.txt", "r");
	vehicles = (Vehicle**)malloc(sizeof(Vehicle*) * noEl); // nu trebuia un memset, dc merge?
	char buffer[50];
	double operation = 0;
	int type = 0;
	int index = 0;

	while (!feof(pFile)) {
		fscanf(pFile, "%s", buffer);
		fscanf(pFile, "%i", &type);
		fscanf(pFile, "%Lf", &operation);
		noEl++;

		Vehicle* vehicle = buildVehicle(buffer, type, operation);
		vehicles[index++] = vehicle;
	}

	printVehicles(vehicles, noEl);

}

void printVehicles(Vehicle* *_veh, int _noEl) {
	for (int i = 0; i < _noEl; i++) {
		printf("Vehicle name: %s \n", _veh[i]->name);

		switch (_veh[i]->type) {
		case VehicleType::CAR:
			printf("Vechicle usage: %i \n", _veh[i]->operation.noMiles);
			break;

		case VehicleType::AIRPLANE:
			printf("Vechicle usage: %Lf \n", _veh[i]->operation.flightHours);
			break;
		}
	
	}
}

Vehicle* buildVehicle(char* _name, int _type, double _operation) {

	// have fct that returns something, always do this
	// this way, u wont forget

	Vehicle* result = NULL;

	result = (Vehicle*)malloc(sizeof(Vehicle));

	// result-> name = _name; // nu asa...
	result->name = (char*)malloc(strlen(_name) + 1);  // se numea pc...
	strcpy(result->name, _name);

	switch (_type)
	{
	case VehicleType::CAR:
		result->type = VehicleType::CAR;
		result->operation.noMiles = _operation;

		break;
	case VehicleType::AIRPLANE:
		result->type = VehicleType::AIRPLANE;
		result->operation.flightHours = _operation;

		break;
	default:
		break;
	}

	/*result->type = _type;
	result->operation = _operation;*/
	// nu asa!!!

	return result;
}


// HW:
//Take this, based on the project, need to do the same thing, but remove the no. of elements in the Data.txt file
//adapt it s.t. it works with an undefinite number of elements
