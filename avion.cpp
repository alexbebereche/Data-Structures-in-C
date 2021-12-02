#include "stdio.h"
#include "malloc.h"
#include "string.h"

struct Avion {
	char* model;
	int nrLocuri;
	int nrLocuriOcupate;
	float* preturiBilete;
};

struct NodeBST { //mai usor de vizualizat scris asa zic eu
	NodeBST* left;
	Avion info;
	NodeBST* right;
};

Avion initAvion(const char* model, int nrLocuri, int nrLocuriOcupate, float* preturi) {
	Avion avion;

	avion.model = (char*)malloc(strlen(model) + 1);
	strcpy(avion.model, model);

	avion.nrLocuri = nrLocuri;
	avion.nrLocuriOcupate = nrLocuriOcupate;

	avion.preturiBilete = (float*)malloc(sizeof(float) * avion.nrLocuriOcupate);
	for (int i = 0; i < nrLocuriOcupate; i++) {
		avion.preturiBilete[i] = preturi[i];
	}


	return avion;
}

void afisareAvion(Avion avion) {
	printf("\nAvionul %s are %d locuri din care %d sunt ocupate: ",
		avion.model, avion.nrLocuri, avion.nrLocuriOcupate);
	printf("\nPreturi:");
	for (int i = 0; i < avion.nrLocuriOcupate; i++) {
		printf("%5.2f, ", avion.preturiBilete[i]);
	}
}

Avion citesteAvionDinFisier(FILE* f) {
	Avion avion;

	char buffer[100];
	fscanf(f, "%s", buffer);
	avion.model = (char*)malloc(strlen(buffer) + 1);
	strcpy(avion.model, buffer);

	fscanf(f, "%d", &avion.nrLocuri);
	fscanf(f, "%d", &avion.nrLocuriOcupate);

	avion.preturiBilete = (float*)malloc(sizeof(float) * avion.nrLocuriOcupate);
	for (int i = 0; i < avion.nrLocuriOcupate; i++)
		fscanf(f, "%f", &avion.preturiBilete[i]);  //la citire las doar %f, nu %5.2f

	return avion;

}

NodeBST* inserareAvionInArbore(NodeBST* root, Avion avion) {

	if (root != NULL) {
		//asta de mai jos inseamna ca ce introducem e mai mic...
		if (root->info.nrLocuri > avion.nrLocuri) {  //inseram in st, folosim recursivitate
			root->left = inserareAvionInArbore(root->left, avion);
		}
		else {
			root->right = inserareAvionInArbore(root->right, avion);  //mai mic, inserez in dreapta, tot cu recursivitate
		}
		return root;
	}
	else {
		//nu avem nod..
		NodeBST* nou = (NodeBST*)malloc(sizeof(NodeBST));  //aloc inainte!, NU UITA SA CREEZI

		nou->info = avion;
		nou->left = nou->right = NULL;

		return nou;
	}

}

//aplicam Divide et Impera
//Inordine(SRD) - imi sorteaza crescator
void afisareArbore(NodeBST* root) { //adresa primului nod
	printf("\n------------------------\n");
	if (root) {
		afisareArbore(root->left);
		afisareAvion(root->info);
		afisareArbore(root->right);
	}
	else {

	}

}

void afisareArborePreordine(NodeBST* root) { //adresa primului nod
	printf("\n------------------------\n");
	if (root) {
		afisareAvion(root->info);
		afisareArbore(root->left);
		afisareArbore(root->right);
	}
	else {

	}

}

Avion cautareAvionInArboreDupaNrLocuri(NodeBST* root, int nr) {
	if (root) {
		if (root->info.nrLocuri == nr) {		//cand scriu . intelisense ma ajuta oricum, cand scriu ->, nu
			//shallow sau deep copy?
			//aleg sa fac deep aici
			Avion avion = initAvion(root->info.model, root->info.nrLocuri, root->info.nrLocuriOcupate, root->info.preturiBilete);

			return avion;
		}
		else {
			if (root->info.nrLocuri > nr)

				return cautareAvionInArboreDupaNrLocuri(root->left, nr);

			else {

				return cautareAvionInArboreDupaNrLocuri(root->right, nr);

			}


		}
	}
	else {
		return initAvion("", -1, -1, NULL);		//avion NULL
	}
}


//stergem intregul arbore
//post-ordine
//void deleteBST(NodeBST* & root) {
//	if (root == NULL) {
//		printf("\nempty");
//	}
//	else {
//		free(root);
//		deleteBST(root->left);
//		deleteBST(root->right);
//		deleteBST(root->info);
//	}
//}

void main() {

	//Avion avion = initAvion("A1", 400, 2, new float[2]{ 5, 10 });  //new float[2] { 5, 10} //trebuie mentionata dimensiunea

	//afisareAvion(avion);

	/*FILE* pFile = fopen("Data.txt", "r");

	int nrAvioane = 0;

	if (pFile) {

		fscanf(pFile, "%d", &nrAvioane);
		for (int i = 0; i < nrAvioane; i++) {
			Avion a = citesteAvionDinFisier(pFile);
			afisareAvion(a);
		}
	}
	fclose(pFile);*/

	NodeBST* root = NULL;

	FILE* pFile = fopen("Data.txt", "r");

	

	if (pFile) {

		int nrAvioane = 0;

		fscanf(pFile, "%d", &nrAvioane);
		for (int i = 0; i < nrAvioane; i++) {
			/*Avion a = citesteAvionDinFisier(pFile);
			afisareAvion(a);*/

			root = inserareAvionInArbore(root, citesteAvionDinFisier(pFile)); //citesteavion a facut shallow copy
		}
	}
	fclose(pFile);
	

	afisareArbore(root);
	//afisareArborePreordine(root);

	printf("\n\n\n");
	Avion avionCautat = cautareAvionInArboreDupaNrLocuri(root, 1400);
	afisareAvion(avionCautat);

	//daca nu faceam asta, aveam memory leak
	free(avionCautat.model);
	free(avionCautat.preturiBilete);
}