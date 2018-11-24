#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Matrix.h"
using namespace std;

struct element
{
	int type,src, dst ;
	double value, intial_value;
	element(int type,int src,int dst,double value, double intial_value)
	{
		this->type = type;
		this->src = src;
		this->dst = dst;
		this->value = value;
		this->intial_value = intial_value;
	}
};
double** constructMatrix(int n,int m)
{
	double** mat;
	mat = new double*[n];
	for (int i = 0; i < n; ++i)
		mat[i] = new double[m];
	Matrix::initilzeMatrix(mat, n, m);
	return mat;
}
void printMat(double** mat, int n, int m)
{
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}
void concatenatetMatrix(double** g, double** b, double** c, double** d,int n,int m,double** result)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			result[i][j] = g[i][j];
		}

	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = n; j <n+m; ++j)
		{
			result[i][j] = b[i][j-n];
		}

	}
	for (int i = n; i < n+m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			result[i][j] = c[i-n][j];
		}

	}

	for (int i = n; i < n+m; ++i)
	{
		for (int j = n; j < n + m; ++j)
		{
			result[i][j] = d[i-n][j-n];
		}

	}
	
}

int main()
{
	vector<element> elements;


	ifstream myfile("input.txt");
	string line;
	int n = 0, m = 0;
	double h = 0.1;
	while (std::getline(myfile, line))
	{
		cout << line << endl;
		string type ,value,src,dst,dummy;
		
		type = src = dst = value=dummy = "";
		for (int i = 0; i < line.size(); ++i)
		{
			if(line[i]==' ')
			{
				if (type == "")
					type = dummy;
				else
					if (src == "")
					{
						src = dummy;
						if (n < stoi(dummy))
							n = stoi(dummy);
					}
					else
						if (dst == "")
						{
							dst = dummy;
							if (n < stoi(dummy))
								n = stoi(dummy);
						}
						else 
							value = dummy;
				dummy = "";
			}
			else 
				dummy += line[i];
		}
		
		if (type == "Vsrc")
		{
			element e(1,stoi(src), stoi(dst), stod(value), stod(dummy));
			elements.push_back(e);
			++m;
		}
		else
			if (type == "Isrc")
			{
				element e(2, stoi(src), stoi(dst), stod(value), stod(dummy));
				elements.push_back(e);
			}
			else
				if (type == "R")
				{
					element e(3, stoi(src), stoi(dst), stod(value), stod(dummy));
					elements.push_back(e);
				}
				else
					if (type == "I")
					{
						element e(4, stoi(src), stoi(dst), stod(value), stod(dummy));
						elements.push_back(e);
						++m;
					}
					else
					{
						element e(5, stoi(src), stoi(dst), stod(value), stod(dummy));
						elements.push_back(e);
					}
	}

	
	double** b;
	double** c;
	double** d;
	double** g;
	double** z;
	double** x;
	double** A;
	double** invA;
	invA=constructMatrix(n + m, n + m);
	//printMat(invA, n + m, n + m);
	//return 0;
	A=constructMatrix( n + m, n+m);
	x=constructMatrix(n + m, 1);
	z=constructMatrix(n+m, 1);
	g=constructMatrix(n,n);
	b=constructMatrix(n, m);
	c=constructMatrix(m, n);
	d=constructMatrix(m, m);
	int j = 0;
	int k = 20;
	double vd = 0,id=0;
	while (--k)
	{
		Matrix::initilzeMatrix(z, n + m, 1);
		Matrix::initilzeMatrix(g, n , n);
		Matrix::initilzeMatrix(b, n , m);
		Matrix::initilzeMatrix(c, m, n);
		Matrix::initilzeMatrix(d,  m, m);
		j = 0;
		for (int i = 0; i < elements.size(); ++i)
		{
			if (elements[i].type == 3)
			{
				if (elements[i].src>0)
					g[elements[i].src - 1][elements[i].src - 1] += 1 / elements[i].value;
				if (elements[i].dst>0)
					g[elements[i].dst - 1][elements[i].dst - 1] += 1 / elements[i].value;

				if (elements[i].src>0 && elements[i].dst>0)
				{
					g[elements[i].src - 1][elements[i].dst - 1] -= 1 / elements[i].value;
					g[elements[i].dst - 1][elements[i].src - 1] -= 1 / elements[i].value;
				}
			}
			if (elements[i].type == 1 || elements[i].type == 4)
			{
				if (elements[i].src>0)
					b[elements[i].src - 1][j] = c[j][elements[i].src - 1] = 1;
				if (elements[i].dst>0)
					b[elements[i].dst - 1][j] = c[j][elements[i].dst - 1] = -1;

				if (elements[i].type == 4)
				{
					d[j][j] -= elements[i].value / h;

					if (k == 19)
						vd = 0;
					
					else
					{
						double vds, vdd = 0;
						if (elements[i].dst == 0)
							vdd = 0;
						else
							vdd = x[elements[i].dst - 1][0];
						if (elements[i].src == 0)
							vds = 0;
						else
							vds = x[elements[i].src - 1][0];
						vd = vds - vdd;
					}
						

					z[n + j][0] = vd* elements[i].value / h;//
				}
				else
					z[n + j][0] = elements[i].value;
				++j;

			}
			if (elements[i].type == 4 || elements[i].type == 5)
			{
				if (elements[i].src>0)
					g[elements[i].src - 1][elements[i].src - 1] += elements[i].value / h;
				if (elements[i].dst>0)
					g[elements[i].dst - 1][elements[i].dst - 1] += elements[i].value / h;

				if (elements[i].src>0 && elements[i].dst>0)
				{
					g[elements[i].src - 1][elements[i].dst - 1] -= elements[i].value / h;
					g[elements[i].dst - 1][elements[i].src - 1] -= elements[i].value / h;
				}
			}
			if (elements[i].type == 2)
			{
				if (elements[i].src>0)
					z[elements[i].src - 1][0] += elements[i].value;
				if (elements[i].dst>0)
					z[elements[i].dst - 1][0] -= elements[i].value;
			}

			if (elements[i].type == 5)
			{
				if (k == 19)
					id = 0;
				else
					id = x[i][0];
				if (elements[i].src>0)
					z[elements[i].src - 1][0] += id* elements[i].value / h;
				if (elements[i].dst>0)
					z[elements[i].dst - 1][0] -= id* elements[i].value / h;
			}

		}

		concatenatetMatrix(g, b, c, d, n, m, A);
		Matrix::MatrixInversion(A,n+m ,invA);
		Matrix::MatrixMultiplication(invA, n + m, z, x);
		printMat(x, n + m, 1);
		break;
	}
		/*printMat(g, n, n);
		printMat(b, n, m );
		printMat(c, m, n );
		printMat(d, m, m);*/
	printMat(x, n+m,1);
}