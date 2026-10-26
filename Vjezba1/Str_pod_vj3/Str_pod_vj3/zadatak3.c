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
int insertnewAfter(Position Head, char* trazena, char* ime, char* prezime, int godina);
int insertbefore(Position Head, char* trazena, char* ime, char* prezime, int godina);
int upisDat(Position P, char* imeDatoteke);
int citajDat(Position P, char* imeDatoteke);
int sortfun(Position Head);

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
	insertnewAfter(&Head, "Anic", "Ivan", "Ivanovic", 2007);
	insertbefore(&Head, "Livaja", "Luka", "Lukic", 2012);

	printlist(&Head);

	if (findlastN(&Head, "Livaja"))
		printf("Osoba pronadjena.\n");
	else
		printf("Osoba nije pronadjena.\n");				//Unos funkcija za provjeru rada programa i funkcija//

	deletePerson(&Head, "Livaja");
	printlist(&Head);
	upisDat(&Head, "lista.txt");
	sortfun(&Head);
	printf("\n");
	insertBegin(&Head, "Marko", "Livaja", 1985);
	printlist(&Head);
	sortfun(&Head);
	printf("\n \t");
	printlist(&Head);
	printf("\n");
	upisDat(&Head, "lista.txt");

	Person Head2 = { .ime = { 0 },
		.prezime = { 0 },
		.godina = 0,
		.next = NULL,
	};
	citajDat(&Head2, "lista.txt");
	printlist(&Head2);

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
	if (P->next == NULL) {
		printf("Lista je prazna.\n");
		return -3;
	}
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
int insertnewAfter(Position Head, char* trazena, char* ime, char* prezime, int godina)
{
	Position target = findlastN(Head, trazena);							//inicijalizira osobu iza koje zelimo unijeti novu osobu//

	if (target == NULL) {
		printf("Osoba iza koje zelite unijeti novu osobu ne postoji.\n");	//Provjera//
		return -4;
	}

	return insertBegin(target, ime, prezime, godina);					//Pomocu insertBegin unosi novu osobu//
}
int insertbefore(Position Head, char* trazena, char* ime, char* prezime, int godina)
{
	Position prev = Head;

	while (prev->next != NULL && strcmp(prev->next->prezime, trazena) != 0)
		prev = prev->next;									//prelazi na iducu osobu sve dok ne nadje trazenu osobu//

	if (prev->next == NULL) {
		printf("Trazena osoba ne postoji.\n");
		return -4;
	}
	return insertBegin(prev, ime, prezime, godina);
}
int upisDat(Position P, char* imeDatoteke)
{
	FILE* fp = fopen(imeDatoteke, "w");			//otvara (stvara) datoteku//
	if (!fp) {
		printf("Greska pri otvaranju datoteke.\n");
		return -5;
	}
	P = P->next;
	while (P != NULL) {
		fprintf(fp, "%s %s %d\n", P->ime, P->prezime, P->godina);	//vrsi upis u datoteku//
		P = P->next;
	}
	fclose(fp);
	return 0;
}
int sortfun(Position Head)
{
	Position P = Head->next;
	Position q = Head;
	Position temp = NULL;

	if (P == NULL) {
		printf("Lista je prazna.\n");
		return -3;
	}
	while (P->next != NULL) {							//dok ne dodje do kraja//
		if (strcmp(P->prezime, P->next->prezime) > 0) { //usporedjuje prezimena//
			temp = P->next;
			q->next = temp;
			P->next = temp->next;						//zamjena mjesta//
			temp->next = P;

			q = Head;
			P = q->next;
		}
		else {
			q = P;
			P = P->next;
		}
	}

}
int citajDat(Position P, char* imeDatoteke)
{
	char ime[30];
	char prezime[50];		
	int godina = 0;

	FILE* fp = fopen(imeDatoteke, "r");		//otvara datoteku//
	if (!fp) {
		printf("Greska pri otvaranju datoteke.\n");
		return -5;
	}

	while (fscanf(fp, "%s %s %d", ime, prezime, &godina) == 3)  //Provjera da li su svi podatci uneseni//
		insertBegin(P, ime, prezime, godina);				    //Upis podataka//

	fclose(fp);													//Zatvara datoteku//
	return 0;
}