#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

struct _Cvor;
typedef struct _Cvor* Pozicija;

struct _Cvor
{
	int Element;
	Pozicija Next;
};

void Push(Pozicija, int);
int Pop(Pozicija);
int Calculate(int, char, int);

int main(void)
{
	struct _Cvor S;
	FILE* fp;
	char ime_dat[1024] = { 0 };

	S.Next = NULL;

	printf("Unesite ime datotke za citanje :\n ");
	scanf(" %1023s", ime_dat);
	printf("Izraz :\t");

	fp = fopen(ime_dat, "r");
	if (fp == NULL)
		printf("Datoteka %s nije otvorena!", ime_dat);
	else
	{
		while (!feof(fp))
		{
			char data[32] = { 0 };
			int x;

			fscanf(fp, " %31s", data);
			printf(" %s", data);

			x = atoi(data);
			if (x == 0 && data[0] != '0')
			{
				int x, y, n;

				y = Pop(&S);
				x = Pop(&S);
				n = Calculate(x, data[0], y);
				Push(&S, n);
			}
			else
				Push(&S, x);
		}
		fclose(fp);
	}

	printf("\nRezultat :  %d\n", S.Next->Element);
	free(S.Next);
	return 0;
}

void Push(Pozicija P, int n)
{
	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct _Cvor));
	if (q)
	{
		q->Element = n;
		q->Next = P->Next;
		P->Next = q;
	}
}

int Pop(Pozicija P)
{
	Pozicija tmp;
	int n = 0;

	if (P->Next != NULL)
	{
		tmp = P->Next;
		P->Next = tmp->Next;
		n = tmp->Element;
		free(tmp);
	}
	return n;
}

int Calculate(int x, char o, int y)
{
	int n = 0;
	switch (o)
	{
	case '+':
		n = x + y;
		break;
	case '-':
		n = x - y;
		break;
	case '*':
		n = x * y;
		break;
	case '/':
		if (y != 0)
			n = x / y;
		else
			printf("Nema dijeljenja s 0!\n");
		break;
	case '%':
		n = x % y;
		break;
	default:
		;
	}
	return n;
}