#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Stack* Position;
typedef struct Stack {
	int broj;
	Position next;
}stack;
int insertBegin(Position head, Position newP);
int Push(Position head, int broj);
int Pop(Position head, int* broj);
int obavioperaciju(Position head, char op);
int kriviUnos(Position head);
int calculatePostfix(Position head, FILE* fp, int* rezultat);

int main() {
	stack head = {
		.broj = 0,
		.next = NULL
	};
	int rezultat = 0;

	FILE* fp = fopen("tekst.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}
	if (calculatePostfix(&head, fp, &rezultat) != 0) {
		printf("Pogresan postfix ili prazna datoteka.\n");
		kriviUnos(&head);
		return -2;
	}
	fclose(fp);
	printf("Rezultat: %d\n", rezultat);
	return 0;
	
}
int insertBegin(Position head, Position newP)
{
	newP->next = head->next;
	head->next = newP;
	return 0;
}
int Push(Position head, int broj)
{
	Position newP = (Position)malloc(sizeof(stack));
	if (newP == NULL)
		return -1;
	newP->broj = broj;
	insertBegin(head, newP);
	return 0;
}
int Pop(Position head, int* broj)
{
	Position p = head->next;
	if (p == NULL)
		return -1;
	*broj = p->broj;
	head->next = p->next;
	free(p);
	return 0;
}
int obavioperaciju(Position head, char op)
{
	int a = 0, b = 0, rez = 0;
	if (Pop(head, &b) != 0 || Pop(head, &a) != 0)
		return -1;

	switch (op) {
	case '+':
		rez = a + b;
		break;
	case '-':
		rez = a - b;
		break;
	case '*':
		rez = a * b;
		break;
	case '/':

		if (b == 0)
			return -1;
		rez = a / b;
		break;
	default:
		return -2;
	}
	return Push(head, rez);
}
int kriviUnos(Position head)
{
	int tmp = 0;
	while (Pop(head, &tmp) == 0);
	return 0;
}
int calculatePostfix(Position head, FILE* fp, int* rezultat)
{
	char znakovi[20] = { 0 };

	while (fscanf(fp, "%19s", znakovi) == 1) {
		if (znakovi[0] >= '0' && znakovi[0] <= '9') {
			if (Push(head, atoi(znakovi)) != 0) {
				return -3;
			}
		}
		else if (strlen(znakovi) == 1) {
			if (obavioperaciju(head, znakovi[0]) != 0) {
				return -3;

			}
		}
		else {
			return -1;
		}
	}

	if (Pop(head, rezultat) != 0) {
		return -1;
	}
	if (head->next != NULL) {
		return -1;
	}
	return 0;






}