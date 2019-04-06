#ifndef funkcje_H
#define funkcje_H
#include <stdio.h>

struct lista															//lista, któr¹ po wczytaniu wszystkiz znaków i ich iloœci wyst¹pieñ, przekrzta³camy w drzewo
{
	char znak;															//pobrany  znak  
	int wystapienia;													//iloœæ wyst¹pieñ w pliku
	struct lista *pNext, *pLewy, *pPrawy, *pRodzic;						
};
struct kody																//lista w której zapisujemy kody danych znaków zczytane z drzewa	
{
	char znak;
	char *kod;
	struct kody *next;
};	
struct tree																//drzewo tworzone na podstawie kodów(do dekodowania)
{	
	struct tree *l, *r;
	char znak;
};
struct lista *dodaj(struct lista *pGlowa, char znak);					//funkcja dodaje elemêty do listy
struct lista *sortowanie(struct lista *root);							//funkcja sortuj¹ca listê 
struct lista *znajdz(struct lista *pGlowa, char znak);					//funkcja znajduj¹ca elemêt o danym znaku i zwracaj¹ca jego adres lub NULL w przypadku gdy el nie istnieje
struct lista *otwplik(struct lista *pGlowa, char *nazwa);				//funkcja otwiera plik oraz tworzy listê znaków i ich wyst¹pieñ, korzysta z powy¿szych funkcji 
struct lista *dodajwkol(struct lista *head, struct lista *el);			//podfunkcja dodaj¹ca elemêt o wskazanym adresie do drzewa
struct lista *DodajDoDrzewa(struct lista *pGlowa, char *nazwa);			//funkcja tworz¹ca drzewo huffmana korzysta z powy¿szej funkcji
struct kody *dodkody(struct kody *pGlowa, char znak, const char *kod);	//podfunkcja dodaj¹ca kod do listy
struct kody *znajdzkod(struct kody *glowa, struct lista *head);			//podfunkcja znajduj¹ca kod 
struct lista *usun(struct lista *head);									//funkcja usówaj¹ca elemêt którego kod zosta³ sczytany
struct kody *zakodowane(struct kody *glowa, struct lista *head);		//tworzy listê znakó oraz ich kodów korzysta z *dodkody *znajdzkod *usun
unsigned char znak(char *kod);											//funkcja przekrzta³ca 8 bitów(char[8]) na znak w kodzie ASCI 
char *znajdzkod2(struct kody *glowa, char znak);						//znajduje w liœcie kod danego znaku
void kodowanie(struct kody *glowa, char *wejscie, char *wyjscie);		//funkcja tworzy i koduje plik		
void zapiszkody(char *nazwa, struct kody *glowa);						//funkcja tworzy plik przechowuj¹cy znaki oraz ich kody
struct kody *usunkody(struct kody *pHead);								//funkcja zwalniaj¹ca pamiêæ
//////////////////////////////////////////////DEKODOWANIE///////////////////////////////////
struct tree *dekodowaniedrzewo(struct tree *root, char *nazwa);			//funkcja tworzy z pikiu w którym znajduj¹ siê kody drzewo
char *dekodznak(int liczba);											//funkcja dekoduje znak(zamienia wartoœæ znaku w kodzie ASCII na 8 bitów)
void dekodowanie(char *wejscie, char *wyjscie, struct tree *root);		//funkcja dekoduje plik
void deletetree(struct tree* root);										//funkcja zwalnia pamiêæ(usówa drzewo)
#endif