#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor
{
	int Element;
	Pozicija Next;
};


void ReadListFromFile(Pozicija);
void PrintList(Pozicija);
void Presjek(Pozicija, Pozicija, Pozicija);
void Unija(Pozicija, Pozicija, Pozicija);

int main()
{
	Pozicija headL1, headL2, headP, headU;

	headL1 = (Pozicija)malloc(sizeof(struct Cvor));
	if (headL1 == NULL) 
		return -1;
	headL1->Next = NULL;

	headL2 = (Pozicija)malloc(sizeof(struct Cvor));
	if (headL2 == NULL) 
		return -1;
	headL2->Next = NULL;

	headP = (Pozicija)malloc(sizeof(struct Cvor));
	if (headP == NULL) 
		return -1;
	headP->Next = NULL;

	headU = (Pozicija)malloc(sizeof(struct Cvor));
	if (headU == NULL) 
		return -1;
	headU->Next = NULL;

	ReadListFromFile(headL1);
	ReadListFromFile(headL2);

	printf("Lista L1 :\n");
	PrintList(headL1->Next);

	printf("Lista L2 :\n");
	PrintList(headL2->Next);

	Presjek(headL1->Next, headL2->Next, headP);
	printf("Presjek L1 i L2 je :\n");
	PrintList(headP->Next);

	Unija(headL1->Next, headL2->Next, headU);
	printf("Unija L1 i L2 je :\n");
	PrintList(headU->Next);
	free(headL1);
	free(headL2);
	free(headP);
	free(headU);
	return 0;
}

	


void ReadListFromFile(Pozicija P)
{
	FILE* fp;
	char filename[128];
	Pozicija q, temp;

	printf("Unesite ime datoteke za citanje :\n ");
	scanf("%127s", filename);

	fp = fopen(filename, "r");
	if (fp == NULL)
		printf("Neuspjesno otvorena datoteka!\n");
	else
	{
		while (!feof(fp))
		{
			q = (Pozicija)malloc(sizeof(struct Cvor));
			if (q == NULL)
				printf("Greska! Memorija nije alocirana.\n");
			else
			{
				fscanf_s(fp, " %d", &q->Element);

				temp = P;

				while (temp->Next != NULL && temp->Next->Element <  q->Element)
					temp = temp->Next;
				q->Next = temp->Next;
				temp->Next = q;
			}
		}
		fclose(fp);
	}
}

void PrintList(Pozicija P)
{
	while (P != NULL)
	{
		printf(" %d", P->Element);
		P = P->Next;
	}
	printf("\n");
}

void Presjek(Pozicija L1, Pozicija L2, Pozicija P)
{
	Pozicija q;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1->Element < L2->Element)
			L1 = L1->Next;
		else if (L1->Element > L2->Element)
			L2 = L2->Next;
		else
		{
			q = (Pozicija)malloc(sizeof(struct Cvor));
			if (q == NULL)
				printf("Greska! Memorija nije alocirana.\n");
			else
			{
				q->Element = L1->Element;

				q->Next = P->Next;
				P->Next = q;

				P = q;
			}
			L1 = L1->Next;
			L2 = L2->Next;
		}
	}

}
void Unija(Pozicija L1, Pozicija L2, Pozicija U)
{
	Pozicija q, temp;
	int temp_element = 0;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1->Element > L2->Element)
		{
			temp_element = L1->Element;
			L1 = L1->Next;
		}
		else if (L1->Element < L2->Element)
		{
			temp_element = L2->Element;
			L2 = L2->Next;
		}
		else
		{
			temp_element = L1->Element;
			L1 = L1->Next;
			L2 = L2->Next;
		}

		q = (Pozicija)malloc(sizeof(struct Cvor));
		if (q == NULL)
			printf("Greska! Memorija nije alocirana.\n");
		else
		{
			q->Element = temp_element;

			q->Next = U->Next;
			U->Next = q;

			U = q;
		}
	}

	if (L1 == NULL)
		temp = L2;
	else
		temp = L1;

	while (temp != NULL)
	{
		q = (Pozicija)malloc(sizeof(struct Cvor));
		if (q == NULL)
			printf("Greska! Memorija nije alocirana.\n");
		else
		{
			q->Element = temp->Element;

			q->Next = U->Next;
			U->Next = q;

			U = q;
		}
		temp = temp->Next;
	}

}
