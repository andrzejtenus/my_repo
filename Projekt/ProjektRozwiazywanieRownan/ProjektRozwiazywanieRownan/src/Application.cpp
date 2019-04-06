#define _CRTDBG_MAP_ALLOC 
#include <Libray.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
void free_(double **table, int x)
{
	for (int i = 0; i < x; i++)
	{
		//free(table[i]);
		delete[] table[i];
	}
	delete[] table;
	//free(table);
}
double ** make_table(int x_, int y_)
{
	double **T_;
	T_ = new double *[x_];
	for (int i = 0; i < x_; i++)
	{
		T_[i] = new double[y_];
	}
	return T_;
}
int odczyt(double **T,int x, std::string instream)    //do czytania pliku dla ulatwienie
{
	std::ifstream macierz(instream.c_str());      
	if (macierz.good())                      
		for (int i = 0; i<x; i++)               
		{
			for (int j = 0; j<x+1; j++)
			{
				macierz >> T[i][j];          
			}

			if (macierz.fail())        
			{
				macierz.close();                                                          
				return 0;                                                              
			}
		}
	else       
	{
		macierz.close();     
		return 0;           
	}
	macierz.close();    
	return 1;
}
int main()
{
	//libray::PrintMessage();
	/////////////////////////Tab Testowa//////////////////////////
	double **tab=make_table(4,5);
	odczyt(tab,4, "tab1.txt");
	//////////////////////////BIBLIOTEKA//////////////////////////////

	libray::Table X (tab,4,5);
	free_(tab, 4);
	libray::Solvery Y(X);
	//Y.printA_();
	//Y.printX_GAUSS();
	Y.gauss_seidley(7);
	Y.printAll();
	//Y.gauss_seidley(4);			//g³ówna metoda do obliczania rozi¹zania(je¿eli jej nie wywo³amy to domyœlne przybli¿enie jest ustawione na 2
	//std::cout << std::endl;
	//Y.printX();					//ok
	//X.printMainTable();		//ook
	//libray::Table Y(X);//ok
	//Y.printMainTable();//ok
	return 1;
}