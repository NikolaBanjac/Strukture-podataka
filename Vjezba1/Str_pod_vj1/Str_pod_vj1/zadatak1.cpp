#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_BODOVI 95								//konstanta maksimalnog broja bodova//

typedef struct _Student {    
	char ime[20];
	char prezime[30];
	int bodovi;		
}stud;
int main()
{
	char buffer[50];
	int brojac = 0;  
	FILE* fp = fopen("popis.txt", "r");				//otvaranje datoteke//
	if (fp == NULL) {								//provjera datoteke//
		printf("File nije uspjesno otvoren\n");
		return -1;
	}
	while (!feof(fp)) {
		if (fgets(buffer, 50, fp) != NULL)
		brojac++;
	}
	rewind(fp);										//vracanje pokazivaca//

	stud* Studenti = NULL;
	Studenti = (stud*)malloc(sizeof(stud) * brojac);  // alokacija memorije//
		if (!Studenti) {
			printf("Greska pri alokaciji memorije");
			free(Studenti);
			return -2;
		}
	
		for (int i = 0; i < brojac; i++) {
			fscanf(fp, " %s %s %d", Studenti[i].ime, Studenti[i].prezime, &Studenti[i].bodovi);
		}
		for (int i = 0; i < brojac; i++) {
			double rel_bodovi = (double)Studenti[i].bodovi / MAX_BODOVI * 100;
			printf("%s %s %d %.2f\n", Studenti[i].ime, Studenti[i].prezime, Studenti[i].bodovi, rel_bodovi);
	}
	fclose(fp);
	free(Studenti);
	return 0;
}