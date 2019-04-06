#include <stdio.h>
#include "funkcje.h"

int main(int argc, char *argv[])
{
	if (argc == 5)
	{
		if (!strcmp(argv[1], "-k"))
		{
			struct lista *pGlowa = NULL;
			struct kody *pHead = NULL;
			pGlowa = DodajDoDrzewa(pGlowa, argv[2]);
			if (pGlowa)
			{
				pHead = zakodowane(pHead, pGlowa);
				kodowanie(pHead, argv[2], argv[3]);
				zapiszkody(argv[4], pHead);
				pHead = usunkody(pHead);
				pGlowa = NULL;
			}
		}
		else
			if (!strcmp(argv[1], "-d"))
			{
				struct tree *root = NULL;
				root = dekodowaniedrzewo(root, argv[4]);
				dekodowanie(argv[2], argv[3], root);
				deletetree(root);
			}
	}
	else
	{
		printf("Za malo arg funkcji. Zapoznaj sie z instrukcja:");
		instrukcja();
	}
	return 0;
}