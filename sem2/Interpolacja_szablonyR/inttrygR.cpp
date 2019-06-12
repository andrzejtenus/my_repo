#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 101
// MAXN - rozmiar tablic wêz³ów i wartoœci funkcji w wêz³ach interpolacji
//        zak³adamy, ¿e n<MAXN
	int n; // maksymalny indeks wêz³a interpolacji, (n+1) - lb. wêz³ów
	int m; // wspó³czynnik m we wzorze (24)
	int mn; // lb. poœrednich punktów miêdzy wêz³ami interpolacji w drugim pliku   
	int ddelta; // wspó³czynnik delta we wzorze (24)
	double a, b; // granice przedzia³u zawieraj¹cego wêz³y interpolacji
	double pi2=8*atan(1.0);
	double x[MAXN]; // tablica wêz³ów na osi x
	double y[MAXN]; // tablica wêz³ów na osi y
	double f[MAXN]; // tablica wartoœci funkcji w wêz³ach interpolacji
	char *plkNazwaWezly, *plkNazwa; // nazwy pierwszego i drugiego pliku
	double aa[MAXN], bb[MAXN]; // tablice wspó³czynników ai i bi we wzorze (24)

//	funkcja g(y) na podstawie której wyznaczane s¹ wartoœci w wêz³ach interpolacji
// y nale¿y do przedzia³u <a, b>                     
double gfun(double y)
{
	return cos(( ((2*M_PI)/(b-a))*(y-a) )-1)*((y-a)/(b-a)) + 1;
}

//	funkcja okresowa g(y),  y dowolne
double g(double t)
{
	double tt;
	tt=fmod(t-a, b-a);
	return gfun(tt<0?b+tt:a+tt);
}

//	funkcja dokonuj¹ca konwersji zmiennej y na x
double y2x(double y)
{
	return (y-a)/(b-a)*pi2;
}

// Wyznaczenie wêz³ów interpolacji i wartoœci funkcji w wêz³ach
void generWezlyTryg()
{
	double delta=(b-a)/(n+1);
	for (int i=0; i<=n; i++)
	{
		y[i]=a+delta*i;
		x[i]=y2x(y[i]);
		f[i]=gfun(y[i]);
		printf("%f     %f     %f \n", y[i], x[i], f[i]);
	}
	y[n+1]=b;
	m=n/2; //wyznaczenie wspó³czynnika m ze wzorze (24)
	ddelta=n-2*m; // wyznaczenie wspó³czynnika delta ze wzoru (24)
}

// Wyprowadzenie danych do pierwszego pliku
void generWezlyPlik()
{
	FILE *plk;
	plk = fopen( plkNazwaWezly, "w" );
// wydruk nag³ówka dla pliku .rex
	fprintf(plk, "yi\t g_yi\t xi\n");
// wydruk trójek wêze³  na osi y, wartoœæ funkcji w wêŸle interpolacji i wêze³ na osi x 
	for (int i=0; i<=n; i++)
	{
		fprintf(plk, "%lf\t %lf\t %lf\n", y[i], f[i], x[i]);
	}
// wydruk stopki dla pliku .rex
//	fprintf(plk, "*InfKon*\nV 0 0 0 %d",n+1 );
	fclose(plk);
}

// Generacja parametrów ai oraz bi ze wzoru (24)
	void genAi_Bi()
{
	return;
}

//funkcja interpoluj¹ca
double Tryg(double t)
{
	double pp, tt;
	int j;
	return t;
}

//Wyprowadzenie wiersza do drugiego pliku
void drukWiersz(double ty, FILE *plk)
{
	double eps=1.0e-20;
	double tx, wyn, gg;
	tx=y2x(ty);
	wyn=Tryg(tx);
	gg=g(ty);
	fprintf(plk, "%lf\t %lf\t %lf\t %lf\t %lf\n", ty, gg, wyn, gg-wyn, (gg-wyn)/(fabs(gg)+eps));

}

// Wyprowadzenie danych do drugiego pliku y nale¿y do przedzia³u <a, b>
void generWyn()
{
	double delta;
	int i, j;
	FILE *plk;
	plk = fopen( plkNazwa, "w" );
// wydruk nag³ówka dla pliku .rex
	fprintf(plk, "y\t g_y\t tt_y\t blb_y\t  blw_y\n");
	for (i=0; i<=n; i++)
	{
		delta=(y[i+1]-y[i])/mn;
		for(j=0; j<mn; j++)
		{
			drukWiersz(y[i]+delta*j, plk);
		}
	}
	drukWiersz(b, plk);
// wydruk stopki dla pliku .rex
//	fprintf(plk, "*InfKon*\nV 0 0 0 %d", (n+1)*mn+1);
	fclose(plk);
}

// Wyprowadzenie danych do drugiego pliku y nale¿y do przedzia³u <a-(b-a), b+(b-a)>
void generWyn1()
{
	double ty, delta;
	int i, j;
	FILE *plk;
	plk = fopen( plkNazwa, "w" );
// wydruk nag³ówka dla pliku .rex
	fprintf(plk, "y\t g_y\t tt_y\t blb_y\t  blw_y\n");
	for (i=0; i<=n; i++)
	{ //y nale¿y do przedzia³u <a+(b-a), a)
		delta=(y[i+1]-y[i])/mn;
		for(j=0; j<mn; j++)
		{
			ty=-(b-a)+y[i]+delta*j;
			drukWiersz(ty, plk);
		}
	}
	for (i=0; i<=n; i++)
	{
		delta=(y[i+1]-y[i])/mn;
		for(j=0; j<mn; j++)
		{ //y nale¿y do przedzia³u <a, b)
			ty=y[i]+delta*j;
			drukWiersz(ty, plk);
		}
	}
	for (i=0; i<=n; i++)
	{ //y nale¿y do przedzia³u <b, b+(b-a))
		delta=(y[i+1]-y[i])/mn;
		for(j=0; j<mn; j++)
		{
			ty=(b-a)+y[i]+delta*j;
			drukWiersz(ty, plk);
		}
	}
	//y=b+(b-a)
			drukWiersz(ty, plk);
// wydruk stopki dla pliku .rex
//	fprintf(plk, "*InfKon*\nV 0 0 0 %d", 3*(n+1)*mn+1);
	fclose(plk);
}

int main(int argc, char* argv[])
{
// Odczyt danych z linii polecenia
	a=atof(argv[1]); //lewa granica przedzia³u
	b=atof(argv[2]); //prawa granica przedzia³u
	n=atoi(argv[3]); //maksymalny indeks wêz³a interpolacji
	mn=atoi(argv[4]); //liczba poœrednich punktów miêdzy wêz³ami interpolacji w drugim pliku
	plkNazwa=argv[5];  //nazwa drugiego pliku (pliku z wynikami dzia³ania funkcji interpoluj¹cej)
	plkNazwaWezly=argv[6]; //nazwa pierwszego pliku (pliku z wêz³ami)
// Wyprowadzenie na ekran danych z linii polecenia
	printf("a= %lf\n", a);
	printf("b= %lf\n", b);
	printf("n= %d\n", n);
	printf("mn= %d\n", mn);
// Wyznaczenie wêz³ów interpolacji i wartoœci funkcji w wêz³ach
	generWezlyTryg();
// Wyprowadzenie danych do pierwszego pliku
	generWezlyPlik();
// Generacja parametrów ai oraz bi ze wzoru (24)
	genAi_Bi();
// Wyprowadzenie danych do drugiego pliku y nale¿y do przedzia³u <a, b>
	generWyn();
// Wyprowadzenie danych do drugiego pliku y nale¿y do przedzia³u <a-(b-a), b+(b-a)>
//	generWyn1();
	return 0;
}
