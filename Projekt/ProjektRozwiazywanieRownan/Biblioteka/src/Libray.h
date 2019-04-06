#pragma once
#include <iostream>
namespace libray {
	void PrintMessage();
	class Table
	{
	protected:
		int x, y;
		double **table;
	public:
		Table(double **T_, int x_, int y_);
		Table(Table& T_);
		Table();
		~Table();
		void print(double **T_,int x_,int y_);
		void printMainTable()
		{
			print(this->table,x,y);
		}
		int getX()
		{
			return x;
		}
		int getY()
		{
			return y;
		}
	protected:
		double **get_table()
		{
			return table;
		}
		double ** make_table(int x_, int y_);
		void define_table(double **T_);
	};
	class Solvery:public Table
	{
		double **A, **L, **D, **U, **Dm1,*Dm1B,**Dm1L,**Dm1U,**A_;
		double *X_gauss_seidley,*X_gauss_elimination, *B;
	public:
		void createHealpTables();

		void declarateHealpTables();
		~Solvery();
		Solvery(Table &T);
		void createDm1();
		void createDm1B();
		void createDm1L();
		void createDm1U();
		double ** copyTable(double **T, double **T_)
		{
			for (int i = 0; i < x; i++)
			{
				for (int j = 0; j < x; j++)
				{
					T[i][j] = T_[i][j];
				}
			}
			return T;
		}
		void mnozenie(double **T1, double **T2, double **T3)        
		{
			double wynik;       
			for (int i = 0; i<x; i++)     
			{
				for (int j = 0; j<x; j++)
				{
					wynik = 0;               
					for (int k = 0; k <x; k++)
					{
						wynik = wynik + (T1[i][k] * T2[k][j]);   
					}
					T3[i][j] = wynik;                 
				}
			}
		}
		double* gauss_seidley(int approximation);
		double* method_of_gaussian_elimination();
		///////////////////////////Tylko wypisywanie///////////////////////////
		void printA()
		{
			print(A,x,x);
		}
		void printA_()
		{
			print(A_, x, x);
		}
		void printDm1()
		{
			print(Dm1, x, x);
		}
		void printDm1B()
		{
			for (int i = 0; i < x; i++)
			{
				std::cout << Dm1B[i] << std::endl;
			}
		}
		void printDm1L()
		{
			print(Dm1L, x, x);
		}
		void printDm1U()
		{
			print(Dm1U, x, x);
		}
		void printL()
		{
			print(L,x,x);
		}
		void printD()
		{
			print(D,x,x);
		}
		void printU()
		{
			print(U,x,x);
		}
		void printB()
		{
			for (int i = 0; i < x; i++)
			{
				std::cout << B[i]<<std::endl;
			}
		}
		void printX()
		{
			for (int i = 0; i < x; i++)
			{
				std::cout << X_gauss_seidley[i] << std::endl;
			}
		}
		void printX_GAUSS()
		{
			for (int i = 0; i < x; i++)
			{
				std::cout << X_gauss_elimination[i] << std::endl;
			}
		}
		void printAll()
		{
			std::cout <<std::endl;
			std::cout << "Dane uklady:" << std::endl;
			printMainTable();
			std::cout << std::endl;
			std::cout << "Tablica A:" << std::endl;
			printA();
			std::cout << std::endl;
			std::cout << "Tablica L:" << std::endl;
			printL();
			std::cout << std::endl;
			std::cout << "Tablica D:" << std::endl;
			printD();
			std::cout << std::endl;
			std::cout << "Tablica D^-1:" << std::endl;
			printDm1();
			std::cout << std::endl;
			std::cout << "Tablica U:" << std::endl;
			printU();
			std::cout << std::endl;
			std::cout << "Tablica B:" << std::endl;
			printB();
			std::cout << std::endl;
			std::cout << "Tablica D^-1*B:" << std::endl;
			printDm1B();
			std::cout << std::endl;
			std::cout << "Tablica D^-1*L:" << std::endl;
			printDm1L();
			std::cout << std::endl;
			std::cout << "Tablica D^-1*U:" << std::endl;
			printDm1U();
			std::cout << std::endl;
			std::cout << "Tablica X Sindley:" << std::endl;
			printX();
			std::cout << std::endl;
			std::cout << "Tablica A po Gausie:" << std::endl;
			printA_();
			std::cout << std::endl;
			std::cout << "Tablica X Gauss:" << std::endl;
			printX_GAUSS();
		}
		//////////////////////////////

	};
}