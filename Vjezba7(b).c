#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include <string.h>
#define min 10
#define max 100
struct cvor;
typedef struct cvor* Pozicija;
struct cvor {
	int el;
	Pozicija next;
	int Prioritet;
};
int slucajnoGenerirano(int, int);
void Push(Pozicija,int);
void Pop(Pozicija);
void ispis(Pozicija);

int main() {

	struct cvor stog, red;
	stog.next = NULL;
	red.next = NULL;
	int odabir = 1;

	while (odabir != 0)
	{
		printf("\nPritisnite odgovarajuci broj za radnju koju zelite obaviti:\n");
		printf("0 - KRAJ PROGRAMA!\n");
		printf("1 - Push(RED)!\n");
		printf("2 - Pop(RED)!\n");
		scanf("%d", &odabir);

		switch (odabir)
		{
		case 1:
			Push(&red, slucajnoGenerirano(min, max));
			ispis(red.next);
			break;
		case 2:
			 Pop(&red);
			ispis(red.next);
			break;
		case 0:
			printf("KRAJ!\n"); odabir = 0;
			break;
		default:
			printf("NEMA RADNJE ZA TAJ ODABIR, POKUSAJ PONOVNO!\n");
		}
			
	}

	return 0;
}
int slucajnoGenerirano(int minValue, int maxValue)
{
	int broj;
	broj = rand() % (maxValue - minValue) + minValue;

	return broj;
}

void ispis(Pozicija P) {
	printf("Ispis:\n");

	while (P != NULL)
	{
		printf("%d ", P->el);
		P = P->next;
	}
}
void Push(Pozicija P, int broj) {

	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(struct cvor));

	if (temp) {
		temp->el = broj;
		temp->Prioritet = slucajnoGenerirano(1, 5);
		printf("Na listu se sprema ( %d %d )", temp->el, temp->Prioritet);
		while (P->next != NULL && P->next->Prioritet >= temp->Prioritet)
			P = P->next;
		temp->next = P->next;
		P->next = temp;
		
	}

}


void Pop(Pozicija P) {

	Pozicija temp;

	if (P->next != NULL) {
		temp = P->next;
		printf("Sa liste se skida %d %d.", temp->el, temp->Prioritet);

		P->next = temp->next;
		free(temp);
	
	}
	
}