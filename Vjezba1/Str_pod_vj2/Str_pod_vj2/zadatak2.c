#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _Person* Position;
typedef struct _Person {
	char ime[30];
	char prezime[50];					//Postavljanje strukture//
	int godina;
	Position next;
} Person;

int insertBegin(Position P, char* ime, char* prezime, int godina);
int insertAfter(Position P, Position newP);
int insertEnd(char* ime, char* prezime, int godina, Position Head);
int printlist(Position P);
Position findlastN(Position P, char* prezime);
int deletePerson(Position Head, char* prezime);

int main()
{
	Person Head = { .ime = { 0 },
	.prezime = { 0 },					//Postavljanje Head-a//
	.godina = 0,
	.next = NULL,
	};

	insertBegin(&Head, "Pero", "Peric", 1999);
	insertBegin(&Head, "Ana", "Anic", 2004);			//Unos podataka//
	insertEnd("Marko", "Livaja", 1989, &Head);

	printlist(&Head);

	if (findlastN(&Head, "Livaja"))
		printf("Osoba pronadjena.\n");
	else
		printf("Osoba nije pronadjena.\n");				//Unos funkcija za provjeru rada programa i funkcija//

	deletePerson(&Head, "Livaja");
	printlist(&Head);

	return 0;
}

int insertBegin(Position P, char* ime, char* prezime, int godina)		//Funkcija za unos osoba na početak liste//
{
	Position newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Greska pri alokaciji memorije.");					//Provjera uspješnosti alokacije memorije//
		free(newPerson);
		return -1;
	}

	newPerson->godina = godina;				//upisuje vrijednost parametra u strukturu//
	strcpy(newPerson->ime, ime);			//kopira ime//					
	strcpy(newPerson->prezime, prezime);	//kopira prezime//						
	newPerson->next = NULL;					//Pokazivac dolazi do kraja liste//

	insertAfter(P, newPerson);				//Dodaje osobu na listu//
	return 0;
}

int insertAfter(Position P, Position newP)
{
	newP->next = P->next;					//Pokazivac prelazi na sljedecu osobu//
	P->next = newP;							//Pokazuje na novu osobu//
	return 0;
}

int printlist(Position P)
{
	P = P->next;							//Ide na pokazivac//
	while (P != NULL) {
		printf("%s, %s, %d\n", P->ime, P->prezime, P->godina);  //Dok ne dodje do kraja liste ispisuje podatke//
		P = P->next;						//I opet ide na pokazivac//
	}
}

int insertEnd(char* ime, char* prezime, int godina, Position Head)
{
	Position newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Greska pri alokaciji memorije");
		free(newPerson);
		return -1;
	}
	
	newPerson->godina = godina;					//Kao u insertBegin, upisuje godinu u strukturu//
	strcpy(newPerson->ime, ime);				//Kopira ime//
	strcpy(newPerson->prezime, prezime);
	newPerson->next = NULL;

	while (Head->next != NULL)
		Head = Head->next;						//Dok pokazivac od Head ne dodje do kraja//
	insertAfter(Head, newPerson);				//Upisuje novu osobu//

	return 0;

}
Position findlastN(Position P, char* prezime)
{
	for (P = P->next; P != NULL; P = P->next)	//Petklja ide dok ne dodje do kraja//
		if (strcmp(P->prezime, prezime) == 0)		//Ako uneseno prezime postoji u listi, vraca pokazivac na tu osobu//
			return P;
	return NULL;
}
int deletePerson(Position P, char* prezime)
{
	Position prev = P;				//uvodi nove varijable//
	Position curr = P->next;

	curr = findlastN(P, prezime);	//trazi tu osobu po prezimenu//

	if (curr == NULL) {
		printf("Osoba ne postoji.\n");	//Ukoliko osoba ne postoji//
		return -2;
	}
	
	while (prev->next != curr)
		prev = prev->next;			//trazi se prethodna osoba//

	prev->next = prev->next->next;
	free(curr);
	return 0;
}