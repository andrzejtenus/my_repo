#include "Libray.h"
#include <cmath>
namespace libray {

	void PrintMessage()
	{
		std::cout << "Hi :))";
	}
	void Table::print(double **T_,int x_,int y_)
	{
		for (int i = 0; i < x_; i++)
		{
			for (int j = 0; j < y_; j++)
			{
				std::cout << T_[i][j]<<"\t";
			}
			std::cout << std::endl;
		}
	}
	Table::Table()
	{
		x = 0;
		y = 0;
		table = nullptr;
	}
	double ** Table::make_table(int x_, int y_)
	{
		double **T_;
		T_ = new double *[x_];
		for (int i = 0; i < x; i++)
		{
			T_[i] = new double[y_];
		}
		return T_;
	}
	void Table::define_table(double **T_)
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				this->table[i][j] = T_[i][j];
			}
		}
	}
	Table::Table(double **T_, int x_=0,int y_=0):x(x_),y(y_)
	{
		this->table=make_table(x, y);
		define_table(T_);

	}
	Table::Table(Table &T_)
	{
		this->x = T_.x;
		this->y = T_.y;
		this->table=make_table(x, y);
		define_table(T_.table);
	}
	Table::~Table()
	{
		if(this->table)
		for (int i = 0; i < x; i++)
		{
			delete[] table[i];
			//free(table[i]);
		}
		delete[] table;
		//free(table);
		//std::cout << std::endl << _CrtDumpMemoryLeaks()<<std::endl;
	}
	Solvery::~Solvery()
	{
		if(this->table)
		for (int i = 0; i < x; i++)
		{
			/*
			free(this->table[i]);
			free(A[i]);
			free(L[i]);
			free(D[i]);
			free(U[i]);
			*/
			delete this->table[i];
			delete A[i];
			delete A_[i];
			delete L[i];
			delete D[i];
			delete U[i];
			delete Dm1[i];
			delete Dm1L[i];
			delete Dm1U[i];


		}
		/*
		free(this->table);
		free(A);
		free(L);
		free(D);
		free(U);
		free(X);
		free(B);
		*/
		delete[] this->table;
		delete[] A;
		delete[] A_;
		delete[] D;
		delete[] L;
		delete[] U;
		delete[] X_gauss_seidley;
		delete[] X_gauss_elimination;
		delete[] B;
		delete[] Dm1;
		delete[] Dm1L;
		delete[] Dm1U;
		delete[] Dm1B;
		A = D=Dm1 = Dm1L= Dm1U= L = U = this->table = nullptr;
		X_gauss_seidley = B= Dm1B = nullptr;
		//std::cout << std::endl << _CrtDumpMemoryLeaks();
	}
	void Solvery::createHealpTables()
	{
		A = make_table(x, x);
		L = make_table(x, x);
		D = make_table(x, x);
		A_ = make_table(x, x);
		Dm1 = make_table(x, x);			//D do -1 
		Dm1L = make_table(x, x);
		Dm1U = make_table(x, x);
		U = make_table(x, x);
		X_gauss_seidley = new double[x];
		B = new double[x];
		Dm1B = new double[x];
		X_gauss_elimination= new double[x];
	}
	void Solvery::declarateHealpTables()
	{
		for (int i = 0; i < x; i++)
		{
			B[i] = this->table[i][y-1];
			for (int j = 0; j < x; j++)
			{
				A[i][j] = this->table[i][j];
				if (i > j)
				{
					L[i][j] = this->table[i][j];
				}
				else
				{
					L[i][j] = 0;
				}
				if (i==j)
				{
					D[i][j] = this->table[i][j];
				}
				else
				{
					D[i][j] = 0;
				}
				if (i < j)
				{
					U[i][j] = this->table[i][j];
				}
				else
				{
					U[i][j] = 0;
				}
			}
		}
	}
	void Solvery::createDm1()
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < x; j++)
			{
				if (D[i][j] != 0)
					Dm1[i][j] = pow(D[i][j], -1);
				else
					Dm1[i][j] = 0;
			}
		}
	}
	void Solvery::createDm1B()
	{
		
		for (int i = 0; i < x; i++)
		{
			Dm1B[i] = Dm1[i][i] * B[i];
		}
	}
	void Solvery::createDm1L()
	{

		mnozenie(Dm1, L, Dm1L);
	}
	void Solvery::createDm1U()
	{

		mnozenie(Dm1, U, Dm1U);
	}
	double * Solvery::gauss_seidley(int Ap)
	{
		double *X_ = new double[x];			//poprezednia wartoœæ X					(chyba zbêdne)
		double Dm1LX = 0;					//pomocnicze
		double Dm1UX = 0;
		for (int i = 0; i < x; i++)			//pocz¹tkowe przyblizenie czyli 0
		{
			X_gauss_seidley[i] = 0;
			X_[i] = 0;
		}
		for (int q = 0; q < Ap; q++)
		{
			//printX();
			for (int i = 0; i < x; i++)		//zapisanie poprzednikow
			{
				X_[i] = X_gauss_seidley[i];
			}
			for (int i = 0; i < x; i++)
			{
				Dm1LX = 0;					//zerowanie pomocniczych
				Dm1UX = 0;
				for (int j = 0; j < x; j++)
				{
					Dm1LX = Dm1LX + Dm1L[i][j] * X_gauss_seidley[j];
					Dm1UX = Dm1UX + Dm1U[i][j] * X_[j];
				}
				X_gauss_seidley[i] = Dm1B[i]-Dm1LX- Dm1UX;
			}
		}
		delete[] X_;
		return X_gauss_seidley;
	}
	double* Solvery:: method_of_gaussian_elimination()
	{
		double tmp,*Ttmp=new double[x];
		int x_;
		for (int i = 0; i < x; i++)
		{
			X_gauss_elimination[i] = B[i];
		}
		A_ = copyTable(A_,A);

		for (int i = 0; i < x; i++)
		{
			x_ = i;					//zapisuje przekatna
			if (A_[x_][i])
			{
				for (int z = 0; z < x; z++)
				{
					Ttmp[z] = A_[x_][z];
				}
				for (int j = 0; j < x; j++)
				{
					if (i != j)
					{
						tmp = A_[j][i] / A_[x_][i];

						X_gauss_elimination[j] = X_gauss_elimination[j] - X_gauss_elimination[x_]*tmp;
						for (int l = 0; l < x; l++)
						{
							A_[j][l] = A_[j][l] - tmp*Ttmp[l];
						}

					}
				}
			}
			else 
			{
				for (int i = 0; i < x; i++)
				{
					X_gauss_elimination[i] = 0;
				}
				return nullptr;
			}
		}
		for (int i = 0; i < x; i++)
		{
			X_gauss_elimination[i] = X_gauss_elimination[i] / A_[i][i];
		}
		return X_gauss_elimination;
	}
	Solvery::Solvery(Table &T_):Table(T_)
	{
		createHealpTables();
		declarateHealpTables();
		createDm1();
		createDm1B();
		createDm1U();
		createDm1L();
		gauss_seidley(2);
		method_of_gaussian_elimination();
	}

}