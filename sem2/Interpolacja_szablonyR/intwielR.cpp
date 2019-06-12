#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 101
// MAXN - rozmiar tablic wêz³ów i wartoœci funkcji w wêz³ach interpolacji
//        zak³adamy, ¿e n<MAXN
	int n; // maksymalny indeks wêz³a interpolacji, (n+1) - liczba wêz³ów
	int mn; // liczba poœrednich punktów miêdzy wêz³ami interpolacji w drugim pliku
	int opt; // opt=0 - wêz³y równoodleg³e, opt=1 - wêz³y dobrane optymalnie
	int init=0;
	double a, b; //granice przedzia³u
	double x[MAXN]; //tablica wêz³ów
	double f[MAXN]; //tablica wartoœci funkcji w wêz³ach interpolacji
	double aa[MAXN];
	double bb[MAXN];
	double cc[MAXN];
	double dd[MAXN];
	int i;
	double tt;
	char *plkNazwaWezly, *plkNazwa; //nazwy pierwszego i drugiego pliku
// inne tabele i zmienne

//	funkcja na podstawie której wyznaczane s¹ wartoœci w wêz³ach interpolacji
	double fun(double t)
{

	return fabs(t)/(1+t*t/2);
}

//	funkcja interpoluj¹ca
	double inter(double t)
{
	int j;
	i=n-1;
	for(j=0;j<n;j++){
		if(t<x[j+1]){
			i=j;
			break;
		}
	}
	tt=t-x[i];
	return (aa[i]+tt*(bb[i]+tt*(cc[i]+tt*dd[i])));
}
void solve(double pa[],double pb[],double pc[], double kd[], double x_sol[], int n)
{
	double alfa[MAXN];
	double beta[MAXN];
	alfa[1]=-pc[1]/pb[1];
	beta[1]=kd[1]/pb[1];
	for(int i=2;i<=n-1;i++)
	{
		alfa[i]= - pc[i]/(pb[i]+pa[i]*alfa[i-1]);
		beta[i]= (kd[i]-pa[i]*beta[i-1])/(pb[i]+pa[i]*alfa[i-1]);
	}
	x_sol[n]=beta[n];
	for(int i=n-1;i>0;i--)
	{
		x_sol[i]=alfa[i]*x_sol[i+1]+beta[i];
	}
	
}
// Wyznaczenie wêz³ów interpolacji i wartoœci funkcji w wêz³ach
void generWezly()
{
	double delta;
	double pi=4*atan(1.0);
	if (opt==0)
	{
	// wêz³y równoodleg³e
		delta=(b-a)/n;
		for (int i=0; i<=n; i++)
		{
			x[i]=a+i*delta;
			f[i]=fun(x[i]);
			printf("%f     %f \n", x[i], f[i]);
		}
	}
	else
	{
	// wêz³y optymalnie dobrane
		delta=(b-a)/2;
		for (int i=0; i<=n; i++)
		{
			x[i]=(a+b)/2 - delta*cos(pi*(2*i+1)/(2*n+2));
			f[i]=fun(x[i]);
			printf("%f     %f \n", x[i], f[i]);
		}
	}
}

// Wyprowadzenie danych do pierwszego pliku
void generWezlyPlik()
{
	FILE *plk;
	plk = fopen( plkNazwaWezly, "w" );
// wydruk nag³ówka dla pliku .rex
	fprintf(plk, "xi\t f_xi\n");
// wydruk par wêze³ i wartoœæ funkcji w wêŸle interpolacji
	for (int i=0; i<=n; i++)
	{
		fprintf(plk, "%f\t %f\n", x[i], f[i]);
	}
// wydruk stopki dla pliku .rex
//	fprintf(plk, "*InfKon*\nV 0 0 0 %d",n+1 );
	fclose(plk);
}
void splineABCD()
{
	double dwa[MAXN];
	double ww[MAXN];
	double uu[MAXN];
	double vv[MAXN];
	double hh[MAXN];
	double cstar[MAXN];

	for(i=0; i<n; i++)	//wypelnienie tablicy hh
	{
hh[i] = x[i+1]-x[i];
}
	for(i=0; i<(n-1); i++)	//wypelnienie tablic dwa, uu, ww i vv
	{
		dwa[i+1] = 2;             
		uu[i+1] = hh[i]/(hh[i]+hh[i+1]);
		ww[i+1] = hh[i+1]/(hh[i]+hh[i+1]);
		vv[i+1]=(((f[i+2]-f[i+1])/hh[i+1]-(f[i+1]-f[i])/hh[i])/(hh[i]+hh[i+1]));
	}	  
  	solve(uu, dwa, ww, vv, cstar, n);
	cc[0]=0;
	cc[n]=0;
	for(i=1; i<n; i++) cc[i] = 3*cstar[i];
	for(i=0; i<n; i++)
	{
      	aa[i] = f[i];
      	bb[i] = (f[i+1]-f[i])/hh[i]-(hh[i]*(cc[i+1]+2*cc[i]))/3;
      	dd[i] = (cc[i+1]-cc[i])/(3*hh[i]);
	}
}
//Wyprowadzenie wiersza do drugiego pliku
void drukWiersz(double t, FILE *plk)
{
	double eps=1.0e-20;
	double f, wyn;
	f=fun(t);
	wyn=inter(t);
	fprintf(plk, "%lf\t %lf\t %lf\t %lf\t %lf\n", t, f, wyn, f-wyn, (f-wyn)/(fabs(f)+eps));

}

// Wyprowadzenie danych do drugiego pliku
void generWynikiPlik()
{
	double delta;
	int i, j, lbwier;
	FILE *plk;
	plk = fopen( plkNazwa, "w" );
// wydruk nag³ówka dla pliku .rex
	fprintf(plk, "x\t f_x\t w_x\t blb_x\t blw_x\n");
	if (!(opt==0))
	{
	 // dla wêz³ów optymalnie dobranych wydruk punktów poœrednich w przedziale <a, x[0])
		delta=(x[0]-a)/mn;
		for(j=0; j<mn; j++)
		{
			drukWiersz(a+delta*j, plk);
		}
	}
	 // wydruk punktów w przedziale <x[0], x[n])
	for (i=0; i<n; i++)
	{
		delta=(x[i+1]-x[i])/mn;
		for(j=0; j<mn; j++)
		{
			drukWiersz(x[i]+delta*j, plk);
		}
	}
	if (!(opt==0))
	{
	 // dla wêz³ów optymalnie dobranych wydruk punktów poœrednich w przedziale <x[n], b)
		delta=(b-x[n])/mn;
		for(j=0; j<mn; j++)
		{
			drukWiersz(x[n]+delta*j, plk);
		};
		lbwier=(n+2)*mn+1;
	}
	else
		lbwier=n*mn+1;
	 // wydruk wydruk wartoœci dla x=b
	drukWiersz(b, plk);
// wydruk stopki dla pliku .rex
//	fprintf(plk, "*InfKon*\nV 0 0 0 %d", lbwier);	
	fclose(plk);
}


int main(int argc, char* argv[])
{
// Odczyt danych z linii polecenia
	a=atof(argv[1]); //lewa granica przedzia³u
	b=atof(argv[2]); //prawa granica przedzia³u
	n=atoi(argv[3]); //maksymalny indeks wêz³a interpolacji
	mn=atoi(argv[4]); //liczba poœrednich punktów miêdzy wêz³ami interpolacji w drugim pliku
	opt=atoi(argv[5]); // opt=0 - wêz³y równoodleg³e, opt=1 - wêz³y dobrane optymalnie
	plkNazwa=argv[6];  //nazwa drugiego pliku (pliku z wynikami dzia³ania funkcji interpoluj¹cej)
	plkNazwaWezly=argv[7]; //nazwa pierwszego pliku (pliku z wêz³ami)
// Wyprowadzenie na ekran danych z linii polecenia
	printf("a= %f\n", a);
	printf("b= %f\n", b);
	printf("n= %d\n", n);
	printf("mn= %d\n", mn);
	printf("opt= %d\n", opt);
// Wyznaczenie wêz³ów interpolacji i wartoœci funkcji w wêz³ach
	generWezly();
// Wyprowadzenie danych do pierwszego pliku
	generWezlyPlik();
//Wywo³ania funkcji generuj¹cych parammetry pomocnicze
    splineABCD();
// Wyprowadzenie danych do drugiego pliku
	generWynikiPlik();
	return 0;
}
