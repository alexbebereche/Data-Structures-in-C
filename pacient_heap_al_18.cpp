#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Pacient {
	int cod;
	char* nume;
	char* problema;
	float varsta;
	int prioritate;
	int nrOre;
};

struct Heap {
	Pacient* *elements = NULL;
	int noEl;
	int size;
};

Pacient* createPacient(int cod, const char* name, const char* prob, float age, int prior, int ore)
{
	Pacient* p = (Pacient*)malloc(sizeof(Pacient));

	p->cod = cod;
	p->varsta = age;
	p->prioritate = prior;

	p->nume = (char*)malloc(strlen(name) + 1);
	strcpy(p->nume, name);

	p->problema = (char*)malloc(strlen(prob) + 1);
	strcpy(p->problema, prob);
	
	//+...
	p->nrOre = ore;

	return p;
}

void createHeap(Heap& heap, int size) //sau Heap createHeap(int size..)
{
	heap.size = size;
	heap.noEl = 0;

	heap.elements = (Pacient**)malloc(sizeof(Pacient*)*size);
	memset(heap.elements, NULL, sizeof(Pacient*)*size);

}



void printPacient(Pacient* p)
{
	printf("\n%d %s %s %f %d", p->cod, p->nume, p->problema, p->varsta, p->prioritate);
}


//pt enqueue
void ReheapUp(Heap& heap, int child) { //child <=> poz

	int parent;

	//recursive stop cond
	if (child > 0) { //child == 0, radacina...fac apelul daca e > 0
		parent = (child - 1) / 2;
		if (heap.elements[child]->prioritate > heap.elements[parent]->prioritate) {
			//interchange
			Pacient* aux = heap.elements[parent];
			heap.elements[parent] = heap.elements[child];
			heap.elements[child] = aux;

			ReheapUp(heap, parent);
		}
	}
}





//pq - priority que
void EnqueuePQ(Heap& heap, Pacient* value) {
	if (heap.noEl < heap.size) { //daca pot sa pun elemente...

		heap.elements[heap.noEl] = value;  //noEl, nu size...introduc efectiv in capat
		ReheapUp(heap, heap.noEl);
		heap.noEl++;
	}
	else {
		//as putea sa fac resize...
		heap.size *= 2;
	}



void traversare(Heap heap)
{
	for (int i = 0; i < heap.noEl; i++)
		printPacient(heap.elements[i]);
}

int getParent(int index)
{
	return (index - 1) / 2;
}

int getLeft(int index)
{
	return index * 2 + 1;
}

int getRight(int index)
{
	return (index + 1) * 2;
}

void swap(Heap& h, int i, int j)
{
	Pacient* t = h.elements[i];
	h.elements[i] = h.elements[j];
	h.elements[j] = t;
}



int nr_copii_si_gravide(Heap heap) {
	int c = 0;
	for (int i = 0; i < heap.noEl; i++)
		if (heap.elements[i]->prioritate == 5) {
			c++;
		}
		
	return c;
}

//nu am nr ore...
void crestere(Heap& heap) {
	for (int i = 0; i < heap.noEl; i++) {

		if (heap.elements[i]->nrOre >= 2 && heap.elements[i]->prioritate != 5) {
			heap.elements[i]->prioritate++;
		}
	}

	traversare(heap);

}

void ReheapDown(Heap& heap, int parent) {

	int maxChild;
	int leftChild = getLeft(parent);
	int rightChild = getRight(parent);

	//ne oprim cand 
	//daca left nu exista, nu exista nici right (pt heap)

	if (leftChild <= heap.noEl - 1) { //sa existe left..
		if (leftChild == heap.noEl - 1) { //doar el exista
			maxChild = leftChild;

		}
		else {
			if (heap.elements[leftChild]->prioritate < heap.elements[rightChild]->prioritate) {
				maxChild = rightChild;
			}
			else {
				maxChild = leftChild;
			}
		}

		if (heap.elements[parent]->prioritate < heap.elements[maxChild]->prioritate) {
			//swap
			Pacient* aux = heap.elements[parent];
			heap.elements[parent] = heap.elements[maxChild];
			heap.elements[maxChild] = aux;

			ReheapDown(heap, maxChild);
		}
	}


}

//extrag el cu prioritatea cea mai mare...primul el din vector
Pacient* DequeuePQ(Heap& heap) {

	Pacient* rez = NULL;
	if (heap.noEl > 0) //sa am ce sa extrag
	{
		rez = heap.elements[0]; //am extras...noEl--
		heap.elements[0] = heap.elements[heap.noEl - 1];
		heap.noEl--;

		ReheapDown(heap, 0);  //invers, de la parent spre child

		//din perspectiva arborelui, nu e ok, dar din vector putem sterge
		//arbore fara radacina nu exista
		//il voi inlocui cu ultimul nod, si voi "Sterge" ultimul nod din heap, primul din vector

	}


	return rez;
}

void main()
{
	//1
	Heap heap;
	createHeap(heap, 4);
	Pacient* p1 = createPacient(1, "A", "q", 20, 1,2);
	Pacient* p2 = createPacient(2, "B", "q2", 89, 5,1);
	Pacient* p3 = createPacient(3, "C", "qfasd", 30, 4, 0);
	Pacient* p4 = createPacient(4, "D", "qasda", 21, 2,12);

	EnqueuePQ(heap, p1);
	EnqueuePQ(heap, p2);
	EnqueuePQ(heap, p3);
	EnqueuePQ(heap, p4);


	//2
	traversare(heap);

	//4
	int rez = nr_copii_si_gravide(heap);
	printf("\n\nnr copii si gravide(prio 5): %d\n", rez);

	printf("\n\n@@@@@@@@@@@@\n");
	//5
	crestere(heap);
	printf("\n%d", heap.elements[1]->prioritate); //am testat

	//6


	//7
	printf("\n-----------7--------------\nAm extras");
	Pacient* extras = DequeuePQ(heap);
	printPacient(extras);
	printf("\n------------------------");
	traversare(heap);
	

}