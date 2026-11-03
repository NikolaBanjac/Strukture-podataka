#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Poly* Position;
typedef struct _Poly {
	int koef;
	int eksp;
	Position next;
} Poly;

int insertBegin(Position P, int koef, int eksp);
int readFromFile(Position P, char* imeDatoteke);
int printPoly(Position P);
int addPoly(Position A, Position B, Position Result);
int multiplyPoly(Position A, Position B, Position Result);

int main()
{
	Poly Head1 = { .koef = 0, .eksp = 0, .next = NULL };		//prvi polinom//
	Poly Head2 = { .koef = 0, .eksp = 0, .next = NULL };		//drugi polinom//
	Poly HeadSum = { .koef = 0, .eksp = 0, .next = NULL };		//zbroj//
	Poly HeadProd = { .koef = 0, .eksp = 0, .next = NULL };		//umnozak//

	readFromFile(&Head1, "polinom1.txt");		//Uzimanje podataka iz datoteke//
	readFromFile(&Head2, "polinom2.txt");

	printf("Prvi polinom:  ");					//Ispis zadanih polinoma//
	printPoly(&Head1);
	printf("Drugi polinom: ");
	printPoly(&Head2);

	addPoly(&Head1, &Head2, &HeadSum);			//Racunanje i ispis zbroja polinoma//
	printf("Zbroj:         ");
	printPoly(&HeadSum);

	multiplyPoly(&Head1, &Head2, &HeadProd);	//Racunanje i ispis umnoska polinoma//
	printf("Umnozak:       ");
	printPoly(&HeadProd);

	return 0;
}

int insertBegin(Position P, int koef, int eksp)
{
	Position q = NULL;

	for (q = P->next; q != NULL; q = q->next) {
		if (q->eksp == eksp) {
			q->koef += koef;		//isti eksponent vec postoji, zbraja se koeficijent//
			return 0;
		}
	}

	q = (Position)malloc(sizeof(Poly));
	if (!q) {
		printf("Greska pri alokaciji memorije.");
		return -1;
	}

	q->koef = koef;
	q->eksp = eksp;
	q->next = P->next;				//novi clan pokazuje na dosadasnji prvi//
	P->next = q;					//Head pokazuje na novi clan//

	return 0;
}

int readFromFile(Position P, char* imeDatoteke)
{
	int koef = 0;
	int eksp = 0;

	FILE* fp = fopen(imeDatoteke, "r");
	if (!fp) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (fscanf(fp, "%d %d", &koef, &eksp) == 2)
		insertBegin(P, koef, eksp);						//svaki par ide u listu//

	fclose(fp);
	return 0;
}

int printPoly(Position P)
{
	P = P->next;

	if (P == NULL) {			//provjera ima li polinoma//
		printf("0\n");
		return 0;
	}

	while (P != NULL) {			//Dok ne dodje do kraja//
		printf("%dx^%d ", P->koef, P->eksp);
		P = P->next;
	}
	printf("\n");

	return 0;
}

int addPoly(Position A, Position B, Position Result)
{
	for (A = A->next; A != NULL; A = A->next)
		insertBegin(Result, A->koef, A->eksp);
														//zapravo se koristi insert begin//
	for (B = B->next; B != NULL; B = B->next)
		insertBegin(Result, B->koef, B->eksp);

	return 0;
}

int multiplyPoly(Position A, Position B, Position Result)
{
	Position b = NULL;

	for (A = A->next; A != NULL; A = A->next)
		for (b = B->next; b != NULL; b = b->next)					//mnozi koeficijente, zbraja eksponente//
			insertBegin(Result, A->koef * b->koef, A->eksp + b->eksp);

	return 0;
}