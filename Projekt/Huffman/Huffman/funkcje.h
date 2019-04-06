#ifndef funkcje_H
#define funkcje_H
#include <stdio.h>

struct lista															//lista, kt�r� po wczytaniu wszystkiz znak�w i ich ilo�ci wyst�pie�, przekrzta�camy w drzewo
{
	char znak;															//pobrany  znak  
	int wystapienia;													//ilo�� wyst�pie� w pliku
	struct lista *pNext, *pLewy, *pPrawy, *pRodzic;						
};
struct kody																//lista w kt�rej zapisujemy kody danych znak�w zczytane z drzewa	
{
	char znak;
	char *kod;
	struct kody *next;
};	
struct tree																//drzewo tworzone na podstawie kod�w(do dekodowania)
{	
	struct tree *l, *r;
	char znak;
};
struct lista *dodaj(struct lista *pGlowa, char znak);					//funkcja dodaje elem�ty do listy
struct lista *sortowanie(struct lista *root);							//funkcja sortuj�ca list� 
struct lista *znajdz(struct lista *pGlowa, char znak);					//funkcja znajduj�ca elem�t o danym znaku i zwracaj�ca jego adres lub NULL w przypadku gdy el nie istnieje
struct lista *otwplik(struct lista *pGlowa, char *nazwa);				//funkcja otwiera plik oraz tworzy list� znak�w i ich wyst�pie�, korzysta z powy�szych funkcji 
struct lista *dodajwkol(struct lista *head, struct lista *el);			//podfunkcja dodaj�ca elem�t o wskazanym adresie do drzewa
struct lista *DodajDoDrzewa(struct lista *pGlowa, char *nazwa);			//funkcja tworz�ca drzewo huffmana korzysta z powy�szej funkcji
struct kody *dodkody(struct kody *pGlowa, char znak, const char *kod);	//podfunkcja dodaj�ca kod do listy
struct kody *znajdzkod(struct kody *glowa, struct lista *head);			//podfunkcja znajduj�ca kod 
struct lista *usun(struct lista *head);									//funkcja us�waj�ca elem�t kt�rego kod zosta� sczytany
struct kody *zakodowane(struct kody *glowa, struct lista *head);		//tworzy list� znak� oraz ich kod�w korzysta z *dodkody *znajdzkod *usun
unsigned char znak(char *kod);											//funkcja przekrzta�ca 8 bit�w(char[8]) na znak w kodzie ASCI 
char *znajdzkod2(struct kody *glowa, char znak);						//znajduje w li�cie kod danego znaku
void kodowanie(struct kody *glowa, char *wejscie, char *wyjscie);		//funkcja tworzy i koduje plik		
void zapiszkody(char *nazwa, struct kody *glowa);						//funkcja tworzy plik przechowuj�cy znaki oraz ich kody
struct kody *usunkody(struct kody *pHead);								//funkcja zwalniaj�ca pami��
//////////////////////////////////////////////DEKODOWANIE///////////////////////////////////
struct tree *dekodowaniedrzewo(struct tree *root, char *nazwa);			//funkcja tworzy z pikiu w kt�rym znajduj� si� kody drzewo
char *dekodznak(int liczba);											//funkcja dekoduje znak(zamienia warto�� znaku w kodzie ASCII na 8 bit�w)
void dekodowanie(char *wejscie, char *wyjscie, struct tree *root);		//funkcja dekoduje plik
void deletetree(struct tree* root);										//funkcja zwalnia pami��(us�wa drzewo)
#endif