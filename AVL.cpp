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


NodeBST* rotireLaDreapta(NodeBST* root) {
	if (root != NULL) {
		//apelam la dreapta, stim sigur ca avem ceva in stanga pt ca nu e NULL
		NodeBST* aux = root->left;
		root->left = aux->right;
		aux->right = root;

		return aux;
	}

	return root; //NULL, daca ajunge aici
}

//verific ca nu e NULL si la apel, deci nu mai trebuie inca un return
//gresit, trebuie sa returnezi NULL, nu e bine sa lasi "exceptiile" pe seama apelului
NodeBST* rotireLaStanga(NodeBST* root) {
	if (root != NULL) {
		//apelam la dreapta, stim sigur ca avem ceva in stanga pt ca nu e NULL
		NodeBST* aux = root->right;
		root->right = aux->left;
		aux->left = root;

		return aux;
	}

	return root; //NULL, daca ajunge aici

}

int getInaltimeArbore(NodeBST* root) {
	if (root) {
		int inaltimeST = getInaltimeArbore(root->left);
		int inaltimeDR = getInaltimeArbore(root->right);


		return 1 + (inaltimeST > inaltimeDR ? inaltimeST : inaltimeDR);
		//wow, scrisesem:
		//return 1 + (inaltimeST > inaltimeDR? inaltimeST : inaltimeDR);
	}
	else {
		return 0;
	}
}

int calculareGradEchilibru(NodeBST* root) {
	if (root != NULL) {
		int inaltimeST = getInaltimeArbore(root->left);
		int inaltimeDR = getInaltimeArbore(root->right);

		//grad echilibru
		return inaltimeDR - inaltimeST;
	}
}

//pt arbore echilibrat, pas in plus
NodeBST* inserareAvionInArboreAVLLung(NodeBST* root, Avion avion) {

	if (root != NULL) {
		//asta de mai jos inseamna ca ce introducem e mai mic...
		if (root->info.nrLocuri > avion.nrLocuri) {  //inseram in st, folosim recursivitate
			root->left = inserareAvionInArbore(root->left, avion);
		}
		else {
			root->right = inserareAvionInArbore(root->right, avion);  //mai mic, inserez in dreapta, tot cu recursivitate
		}

		//determinam inaltimile
		//int inaltimeST = getInaltimeArbore(root->left);
		//int inaltimeDR = getInaltimeArbore(root->right);

		////grad echilibru
		//int gradEchilibru = inaltimeDR - inaltimeST;

		//sa nu fie 0, -1, 1, si e MAX = 2 sau -2
		int gradEchilibru = calculareGradEchilibru(root);

		if (gradEchilibru == 2) { //pe exemplul meu: dezechilibrat la dreapta...
			if (calculareGradEchilibru(root->right) == 1) { //sigur am ceva in dreapta, de-asta aleg root->right
				root = rotireLaStanga(root);
			}
			else {
				root->right = rotireLaDreapta(root->right);
				root = rotireLaStanga(root);

			}

		}
		if (gradEchilibru == -2) { //dezechilibrat la stanga
			if (calculareGradEchilibru(root->left) == -1) {
				root = rotireLaDreapta(root);
			}
			else {
				//revenim
				//dezechilibru in st, dupa mini dezech in partea dr
				//trebuie "dubla rotatie"
				root->left = rotireLaStanga(root->left); //ok
				root = rotireLaDreapta(root);

			}
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

NodeBST* inserareAvionInArboreAVL(NodeBST* root, Avion avion) {

	if (root != NULL) {
		//asta de mai jos inseamna ca ce introducem e mai mic...
		if (root->info.nrLocuri > avion.nrLocuri) {  //inseram in st, folosim recursivitate
			root->left = inserareAvionInArbore(root->left, avion);
		}
		else {
			root->right = inserareAvionInArbore(root->right, avion);  //mai mic, inserez in dreapta, tot cu recursivitate
		}

		//determinam inaltimile
		//int inaltimeST = getInaltimeArbore(root->left);
		//int inaltimeDR = getInaltimeArbore(root->right);

		////grad echilibru
		//int gradEchilibru = inaltimeDR - inaltimeST;

		//sa nu fie 0, -1, 1, si e MAX = 2 sau -2
		int gradEchilibru = calculareGradEchilibru(root);

		if (gradEchilibru == 2) { //pe exemplul meu: dezechilibrat la dreapta...
			if (calculareGradEchilibru(root->right) != 1) { //sigur am ceva in dreapta, de-asta aleg root->right
				root->right = rotireLaDreapta(root->right);
			}
			root = rotireLaStanga(root);

		}
		if (gradEchilibru == -2) { //dezechilibrat la stanga
			if (calculareGradEchilibru(root->left) != -1) {
				root->left = rotireLaStanga(root->left);
			}
			root = rotireLaDreapta(root);
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

//int getInaltimeArbore(NodeBST* root) {
//	if (root) {
//		int inaltimeST = getInaltimeArbore(root->left);
//		int inaltimeDR = getInaltimeArbore(root->right);
//
//
//		return 1 + (inaltimeST > inaltimeDR? inaltimeST : inaltimeDR);
//		//wow, scrisesem:
//		//return 1 + (inaltimeST > inaltimeDR? inaltimeST : inaltimeDR);
//	}
//	else {
//		return 0;
//	}
//}

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

			//root = inserareAvionInArbore(root, citesteAvionDinFisier(pFile)); //citesteavion a facut shallow copy
			root = inserareAvionInArboreAVL(root, citesteAvionDinFisier(pFile)); //citesteavion a facut shallow copy

		}
	}
	fclose(pFile);


	afisareArbore(root);
	//afisareArborePreordine(root);

	printf("\n\n\n");
	Avion avionCautat = cautareAvionInArboreDupaNrLocuri(root, 30);

	printf("\nInaltime: %d", getInaltimeArbore(root));



	afisareAvion(avionCautat);

	//daca nu faceam asta, aveam memory leak
	free(avionCautat.model);
	free(avionCautat.preturiBilete);



	//afisareArbore(root);
	
}