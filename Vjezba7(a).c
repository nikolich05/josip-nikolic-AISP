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
};
int slucajnoGenerirano(int, int);
int PushStog(Pozicija, int, int);
int Pop(Pozicija, int);
void ispis(Pozicija);

int main() {

	struct cvor stog, red;
	stog.next = NULL;
	red.next = NULL;
	int maks = 0;
	int i = 0;
	int odabir = 1;

		printf("Definirajte maksimalni broj elemenata na stogu:\n");
		scanf("%d", &maks);
	while (odabir != 0)
	{
		printf("\nPritisnite odgovarajuci broj za radnju koju zelite obaviti:\n");
		printf("0 - KRAJ PROGRAMA!\n");
		printf("1 - Push(STOG)!\n");
		printf("2 - Pop(STOG)!\n");
		scanf("%d", &odabir);

		switch (odabir)
		{
		case 1:
			if (i == maks) {
				printf("Stog je popunjen, odaberite neku drugu radnju...\n");
				break;
			}
			i = PushStog(&stog, slucajnoGenerirano(min, max),i);
			ispis(stog.next);
			break;
		case 2:
			i = Pop(&stog,i);
			ispis(stog.next);
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
int PushStog(Pozicija P, int broj, int i) {

	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(struct cvor));

	if (temp) {
		temp->el = broj;
		temp->next = P->next;
		P->next = temp;

		printf("\nBroj %d se dodjeljuje stogu\n", broj);
		i++;
	}
	return i;
}


int Pop(Pozicija P, int i) {

	Pozicija temp;

	if (P->next != NULL) {
		temp = P->next;
		printf("\nObrisan je broj %d\n", temp->el);

		P->next = temp->next;
		free(temp);
		i--;
	}
	return i;
}