#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
typedef struct Osoba* Pozicija;
struct Osoba {
	int god;
	char ime[15];
	char prezime[20];
	Pozicija Next;

};

void unosP(Pozicija);
void ispis(Pozicija);
void unosK(Pozicija);
Pozicija findElementPrez(Pozicija);
void deletePrez(Pozicija);
void postaviIza(Pozicija);
void postaviIspred(Pozicija);
void upis_u_datoteku(Pozicija);
void citanje_iz_datoteke(Pozicija);
int main() {
	struct Osoba Head;
	Head.Next = NULL;
	Pozicija pronadjenoPrezime = NULL;
	printf("Unos elementa na pocetak liste:\n");
	unosP(&Head);
	ispis(Head.Next);
	printf("Unos elementa na kraj liste:\n");
	unosK(&Head);
	ispis(Head.Next);
	printf("Unos elementa na pocetak liste:\n");
	unosP(&Head);
	printf("Unos elementa na pocetak liste:\n");
	unosP(&Head);
	ispis(Head.Next);
	pronadjenoPrezime = findElementPrez(Head.Next);
	deletePrez(&Head);
	ispis(Head.Next);
	postaviIza(&Head);
	ispis(Head.Next);
	postaviIspred(&Head);
	ispis(Head.Next);
	printf("Sada upisujemo listu u datoteku:\n");
	upis_u_datoteku(Head.Next);
	printf("Sada citamo iz datoteke:\n");
	citanje_iz_datoteke(&Head);
	return 0;
}
void unosP(Pozicija P) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Nesupjesna alokacija memorije!\n");

	}
	else {
		printf("Unesite ime prezime i godinu rodjenja:\n");
		scanf("%14s %19s %d", q->ime, q->prezime, &q->god);
		q->Next = P->Next;
		P->Next = q;
	}
}
void ispis(Pozicija P) {
	if (P == NULL) {
		printf("Lista je prazna!\n");
	}
	else {
		while (P != NULL) {
			printf("%s %s %d\t", P->ime, P->prezime, P->god);
			P = P->Next;
		}

	}
	printf("\n- - - - - - - - - - - - - - - - - - -\n");
}
void unosK(Pozicija P) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Osoba));
	if (q == NULL) {
		printf("Greska u alokaciji memorije!!!\n");
	}
	else {
		while (P->Next != NULL) {
			P = P->Next;
		}
		printf("Unesite ime prezime i godinu rodjenja:\n");
		scanf("%14s %19s %d", q->ime, q->prezime, &q->god);
		q->Next = P->Next;
		P->Next = q;

	}

}
Pozicija findElementPrez(Pozicija P) {
	char prezime[20];

	printf("Upisite prezime pomocu kojeg cete pronaci element:\n");
	scanf("%19s", prezime);
	while (P != NULL) {
		if (strcmp(P->prezime, prezime) == 0) {
			printf("Prezime pronadjeno kod elementa: %s %s %d\n", P->ime, P->prezime, P->god);
			break;
		}
		P = P->Next;

	}
	return P;
}

void deletePrez(Pozicija P) {
	Pozicija temp;
	char prezime[20];
	printf("Unesite prezime pomocu kojeg zelite izbrisati element:\n");
	scanf("%19s", prezime);
	while (P->Next != NULL && strcmp(P->Next->prezime, prezime) != 0) {
		P = P->Next;
	}
	temp = P->Next;
	if (temp != NULL) {
		P->Next = temp->Next;
		free(temp);
		printf("Element je obrisan!\n");
	}

}
void postaviIza(Pozicija P) {
	Pozicija temp;
	printf("Nadjite element iza kojeg zelite ubaciti novi element...\n");
	temp = findElementPrez(P);
	if (temp == NULL) {
		printf("Element nije pronadjen!\n");
	}
	else {
		printf("Element je pronadjen i sada unosite element iza tog elementa:\n ");
		unosP(temp);
	}
}
Pozicija nadjiPrethodni(Pozicija P) {
	char prez[20];

	printf("Unesite prezime pomocu kojeg cete naci element koji prethodi tom prezimenu:\n");
	scanf("%19s",prez);
	while (P->Next != NULL && strcmp(P->Next->prezime, prez) != 0)
		P = P->Next;

	if (P->Next == NULL)
		P = NULL;
	return P;

}
void postaviIspred(Pozicija P) {
	Pozicija temp;
	temp = nadjiPrethodni(P);
	if (temp == NULL) {
		printf("Element nije pronadjen!\n");
	}
	else {
		printf("Sada unesite novi element koji ide ispred tog elementa s navedenim prezimenom!\n");
		unosP(temp);

	}
}
void upis_u_datoteku(Pozicija P) {
	FILE* fp;
	char filename[128];
	printf("Unesite ime datoteke:\t");
	scanf("%127s", filename);
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Datoteka neuspjesno otvorena!\n");
	}
	else {
		while (P != NULL) {
			fprintf(fp, "%s %s %d\n", P->ime, P->prezime, P->god);
			P = P->Next;
		}
	fclose(fp);
	}
}
void citanje_iz_datoteke(Pozicija P) {
	FILE* fp;
	char filename[128];
	Pozicija q;

	printf("Unesite ime datoteke :\t ");
	scanf_s("%127s", filename);

	fp = fopen(filename, "r");
	
	if (fp == NULL)
		printf("Datoteka neuspjesno otvorena!\n");
	else
	{
		while (!feof(fp))
		{
			q = (Pozicija)malloc(sizeof(struct Osoba));
			if (q == NULL)
				printf("GRESKA!Alokacija memorije neuspjela.\n");
			else
			{
				fscanf(fp, " %s %s %d", q->ime, 128, q->prezime, 128, &q->god);

				q->Next = P->Next;
				P->Next = q;
			}
		}
		fclose(fp);
	}
}

