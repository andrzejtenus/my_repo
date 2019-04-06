#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <string.h>
#include <math.h>
#include "funkcje.h"

void instrukcja()
{
	printf("Jezeli chcesz zakodowac plik wpisz przelacznik -k,\na nastepnie podaj kolejno: \nnazwe pliku wejsciowego, wyjsciowego oraz pliku do przechowania kodow.\nJezeli chcesz zdekodowac zakodowany plik wpisz przelacznik -d i wykonaj te same czynnosci.");
}

struct lista *dodaj(struct lista *pGlowa, char znak)
{
	if (!pGlowa)
	{
		pGlowa = malloc(sizeof(struct lista));
		pGlowa->pNext = NULL;
		pGlowa->wystapienia = 1;
		pGlowa->znak = znak;
		pGlowa->pLewy = NULL;
		pGlowa->pPrawy = NULL;
		pGlowa->pRodzic = NULL;
	}
	else
	{
		struct lista *p;
		p = pGlowa;
		while (p->pNext)
		{
			p = p->pNext;
		}
		p->pNext = malloc(sizeof(struct lista));
		p->pNext->pNext = NULL;
		p->pNext->pLewy = p->pNext->pPrawy = NULL;
		p->pNext->pRodzic = NULL;
		p->pNext->znak = znak;
		p->pNext->wystapienia = 1;
	}
	return pGlowa;
}			
struct lista *sortowanie(struct lista *root)
{
	struct lista* TMP = NULL;
	struct lista* pomoc = NULL;

	for (TMP = root; TMP != NULL; TMP = TMP->pNext)
		for (pomoc = TMP; pomoc != NULL; pomoc = pomoc->pNext)
			if (pomoc->wystapienia < TMP->wystapienia) {
				int wystapienia = pomoc->wystapienia;
				char znak = pomoc->znak;
				char *lewy = pomoc->pLewy, *prawy = pomoc->pPrawy, *rodzic = pomoc->pRodzic;
				pomoc->wystapienia = TMP->wystapienia;
				TMP->wystapienia = wystapienia;
				pomoc->znak = TMP->znak;
				TMP->znak = znak;
				pomoc->pLewy = TMP->pLewy;
				TMP->pLewy = lewy;
				pomoc->pPrawy = TMP->pPrawy;
				TMP->pPrawy = prawy;
				pomoc->pRodzic = TMP->pRodzic;
				TMP->pRodzic = rodzic;
			}
	return root;
}						
struct lista *znajdz(struct lista *pGlowa, char znak)
{
	while (pGlowa)
	{
		if (pGlowa->znak == znak)
			return pGlowa;
		pGlowa = pGlowa->pNext;
	}
	return NULL;
}			
struct lista *otwplik(struct lista *pGlowa, char *nazwa)
{
	char znak;
	FILE *f = fopen(nazwa, "rb");
	struct lista *pom;
	if (f)
	{
		znak = getc(f);
		while (znak != EOF)
		{
			pom = znajdz(pGlowa, znak);
			if (pom)
				pom->wystapienia = pom->wystapienia + 1;
			else
				pGlowa = dodaj(pGlowa, znak);
			znak = getc(f);
		}
	}
	else
	{
		printf("blad otwarcia pliku");
		return NULL;
	}

	sortowanie(pGlowa);
	fclose(f);
	return pGlowa;
}     
struct lista *dodajwkol(struct lista *head, struct lista *el)
{
	struct lista *p = head;
	struct lista *pom = p;

	while (p)
	{
		if (el->wystapienia > p->wystapienia)
		{
			pom = p;
			p = p->pNext;
		}
		else
		{
			break;
		}
	}
	if (p == head)
	{
		el->pNext = head;
		head = el;
	}
	else
		if (p == NULL)
		{
			pom->pNext = el;
		}
		else
		{
			pom->pNext = el;
			el->pNext = p;
		}
	return head;
};			
struct lista *DodajDoDrzewa(struct lista *pGlowa, char *nazwa)
{
	pGlowa = otwplik(pGlowa, nazwa);
	if (!pGlowa)
	{
		return NULL;
	}
	struct lista *lewy, *prawy, *nowy;
	while (1)
	{
		lewy = pGlowa;
		prawy = pGlowa->pNext;
		if (!prawy)
			break;
		pGlowa = prawy->pNext;
		lewy->pNext = NULL;
		prawy->pNext = NULL;
		nowy = malloc(sizeof(struct lista));
		nowy->znak = NULL;
		nowy->wystapienia = lewy->wystapienia + prawy->wystapienia;
		nowy->pLewy = lewy;
		nowy->pLewy->pRodzic = nowy;
		nowy->pPrawy = prawy;
		nowy->pPrawy->pRodzic = nowy;
		nowy->pNext = NULL;
		nowy->pRodzic = NULL;
		pGlowa = dodajwkol(pGlowa, nowy);
	}
	return pGlowa;
}			
struct kody *dodkody(struct kody *pGlowa, char znak, const char *kod)
{
	int i = 0;
	while (kod[i] != '\0')
	{
		i++;
	}
	if (!pGlowa)
	{
		pGlowa = malloc(sizeof(struct kody));
		pGlowa->next = NULL;
		pGlowa->znak = znak;
		pGlowa->kod = malloc(sizeof(char)*(i + 1));
		strcpy(pGlowa->kod, kod);
	}
	else
	{
		struct kody *p;
		p = pGlowa;
		while (p->next)
		{
			p = p->next;
		}
		p->next = malloc(sizeof(struct kody));
		p->next->next = NULL;
		p->next->znak = znak;
		p->next->kod = malloc(sizeof(char)*(i + 1));
		strcpy(p->next->kod, kod);
	}
	return pGlowa;
}		
struct kody *znajdzkod(struct kody *glowa, struct lista *head)
{
	char T[256] = { '\0' };
	char *jeden = "1";
	char *zero = "0";
	struct lista *p = head;
	while (1)
	{
		if (p->pLewy)
		{
			strcat(T, zero);
			p = p->pLewy;
		}
		else
			if (p->pPrawy)
			{
				strcat(T, jeden);
				p = p->pPrawy;
			}
			else
				break;
	}
	if (p->znak)
		glowa = dodkody(glowa, p->znak, T);
	return	glowa;
}		
struct lista *usun(struct lista *head)
{
	int info = 2;
	struct lista *p = head;
	while (1)
	{
		if (p->pLewy)
		{
			info = 0;
			p = p->pLewy;
		}
		else
			if (p->pPrawy)
			{
				info = 1;
				p = p->pPrawy;
			}
			else
				break;
	}
	if (info != 2)
	{
		struct lista *pom;
		pom = p->pRodzic;
		free(p);
		p = NULL;
		if (info == 1)
			pom->pPrawy = NULL;
		else
			if (info == 0)
				pom->pLewy = NULL;
	}
	else
	{
		free(head);
		head = NULL;
	}
	return head;

}		
struct kody *zakodowane(struct kody *glowa, struct lista *head)
{
	while (head)
	{
		glowa = znajdzkod(glowa, head);
		head = usun(head);
	}
	return glowa;
}	
unsigned char znak(char *kod)
{
	int i;
	unsigned char wynik = 0;

	for (i = 0; i < 8; ++i)
		wynik |= (kod[i] == '1') << (7 - i);
	return wynik;
}				
char *znajdzkod2(struct kody *glowa, char znak)
{
	if (!glowa)
		return NULL;
	struct kody *p = glowa;
	while (p->znak != znak)
	{
		p = p->next;
	}
	return p->kod;
}			
void kodowanie(struct kody *glowa, char *wejscie, char *wyjscie)
{
	int i = 0;
	int j = 0;
	char ch, *kod;
	char T[9] = { '\0' };
	FILE *we = fopen(wejscie, "rb");
	FILE *wy = fopen(wyjscie, "w");
	ch = getc(we);
	if (!znajdzkod2(glowa, ch))
		return;
	while (ch != EOF)
	{
		kod = znajdzkod2(glowa, ch);
		while (kod[i] != '\0')
		{
			if (j <= 7)
			{
				T[j] = kod[i];
				i++;
				j++;
			}
			else
			{
				T[j] = '\0';
				fprintf(wy, "%c", znak(T));
				j = 0;
			}
		}
		i = 0;
		ch = getc(we);
	}
	if (j != 0)
	{
		int a = j;
		for (j; j <= 8; j++)
		{
			T[j] = '\0';
		}
		fprintf(wy, "%c", znak(T));
		fprintf(wy, "%c", a); 
	}
	fclose(we);
	fclose(wy);
}		
void zapiszkody(char *nazwa, struct kody *glowa)
{
	FILE *f = fopen(nazwa, "w");
	while (glowa)
	{
		fprintf(f, "%c\t%s\n", glowa->znak, glowa->kod);
		glowa = glowa->next;
	}
	fclose(f);
}			
struct kody *usunkody(struct kody *pHead)
{
	if (!pHead)
		return NULL;
	struct kody *p = pHead;
	while (pHead->next)
	{
		p = pHead->next;
		free(pHead);
		pHead = NULL;
		pHead = p;
	}
	free(pHead);
	pHead = NULL;
	return pHead;
}					
struct tree *dekodowaniedrzewo(struct tree *root, char *nazwa)
{
	int i;
	char znak, pobrany;
	struct tree *p;
	FILE *f = fopen(nazwa, "r");
	if (f == NULL)
	{
		printf("blad otwarcia pliku");
		return 0;
	}
	else
	{
		if (!root)
		{
			root = malloc(sizeof(struct tree));
			root->znak = '\0';
			root->l = root->r = NULL;
		}
		pobrany = getc(f);
		while (pobrany != EOF)
		{
			p = root;
			znak = pobrany;
			while (pobrany != '\n')
			{
				if (pobrany == '0')
				{
					if (p->l)
					{
						p = p->l;
					}
					else
					{
						p->l = malloc(sizeof(struct tree));
						p->l->l = p->l->r = NULL;
						p->l->znak = '\0';
						p = p->l;
					}
				}
				else
					if (pobrany == '1')
					{
						if (p->r)
						{
							p = p->r;
						}
						else
						{
							p->r = malloc(sizeof(struct tree));
							p->r->l = p->r->r = NULL;
							p->r->znak = '\0';
							p = p->r;
						}
					}
				pobrany = getc(f);
			}
			p->znak = znak;
			pobrany = getc(f);
		}
	}
	fclose(f);
	return root;
}
char *dekodznak(int liczba)
{
	char t[9] = { '\0' };
	int i = 0, bit;
	for (i; i < 8; ++i)
	{
		bit = liczba % 2;
		liczba /= 2;
		if (bit)
			t[7 - i] = '1';
		else
			t[7 - i] = '0';
	}
	return t;
}
void dekodowanie(char *wejscie, char *wyjscie, struct tree *root)
{
	struct tree *p = root;
	int i = 0;
	int k = 8;
	int znak, znakp2, next;
	FILE *we = fopen(wejscie, "rb");
	FILE *wy = fopen(wyjscie, "w");
	char *kod;
	if (wy)
	{
		if (we)
		{
			znak = getc(we);
			if (znak != EOF)
				next = getc(we);
			if (next != EOF)
				znakp2 = getc(we);
			while (znak != EOF)
			{
				for (i = 0; i < k; ++i)
				{
					if (znakp2 == EOF)
						k = next;
					kod = dekodznak(znak);
					if (kod[i] == '1')
						p = p->r;
					else
						p = p->l;

					if (p->znak != '\0')
					{
						if (p->znak == '\r')
							fprintf(wy, "\n");
						if (p->znak == '\t')
						{
						}
						else
							fprintf(wy, "%c", p->znak);
						p = root;
					}
				}
				znak = next;
				next = znakp2;
				znakp2 = getc(we);
			}
		}
		else
			printf("nie mozna otwozyc pliku wejsciowego");
	}
	else
		printf("nie mozna otwozyc pliku wyjsciowego");
}

void deletetree(struct tree* root)
{
	if (root == NULL) return;

	deletetree(root->l);
	deletetree(root->r);

	free(root);
}