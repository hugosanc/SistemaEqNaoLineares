#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define N 3
#define eps 1e-5
#define dt 1e-6

double f1( double x[N] )
{	return pow(x[0], 2) - 81* pow((x[1] + 0.1), 2) + sin(x[2]) + 1.06;
}

double f2( double x[N] )
{	return exp(x[0]* x[1]) + 20* x[2] + (10* M_PI-3)/ 3.;
}

double f3( double x[N] )
{	return 3* x[0] - cos(x[1]* x[2]) - 0.5;
}

double df( double f(), double *x, int i)
{	double diff, x1[N], x2[N];
	int j;

	for( j = 0; j < N; j++ )
	{	x1[j] = x[j];
		x2[j] = x[j];
	}
	x1[i] = x[i] + dt;
	x2[i] = x[i] - dt;
	diff = (f(x1) - f(x2))/ (2* dt);
	return diff;
}

void imprime( double **M, int NL, int NC)
{
	int i, j;
	for( i = 0; i < NL; i++)
	{	for( j = 0; j < NC; j++)
			printf("%lf\t ", M[i][j]);
		puts("");
	}	
}

void pivoteamento( double **M, int NL, int NC)
{
        double l, pivo, maior, aux;
        int i, j, k, m, n;
        
        for( j = 0; j < NL-1; j++)
        {	pivo = M[j][j];
		maior = pivo;

		for( k = j; k < NL; k++)
		{	if( fabs(maior) < fabs(M[k][j]))
			{	maior = M[k][j];
				m = k;
			}
		}
		if( maior != pivo)
		{	for( n = 0; n < NC; n++)
			{	aux = M[m][n];
				M[m][n] = M[j][n];
				M[j][n] = aux;
			}
		}
		for( i = j+1; i < NL; i++)
		{	l = M[i][j]/M[j][j];       
			for( k = 0; k < NC; k++ )
				M[i][k] -= l* M[j][k]; 
		}
	}       
}

void subreversa( double **M, double *x, int dim)
{
	int i, j;
	double sum;

	for( i = dim-1; i >= 0; i--)
	{	sum = 0;
		for( j = i+1; j < dim; j++)
			sum += M[i][j]* x[j];
		x[i] = ( M[i][dim] - sum )/ M[i][i];
	}
}

void main()
{	double *y, x0[N] = {0.1,0.1,-0.1}, **L;
	double norm, norma;
	double (*F[N])() = {f1,f2,f3};
	double **J;
	int i, j;

	y = malloc( N* sizeof(double));
	L = malloc( N* sizeof(double));
	for( i = 0; i < N; i++ )
		L[i] = malloc((N+1)* sizeof(double));

	J = malloc( N* sizeof(double));
	for( i = 0; i < N; i++ )
		J[i] = malloc(N* sizeof(double));

	printf("x[0] \t\tx[1] \t\tx[2] \t\t Norma\n%f \t%f \t%f\n",x0[0], x0[1], x0[2]);
	do
	{	norma = norm = 0;
		//criação da matriz
		for( i = 0; i < N; i++ )
		{	for( j = 0; j < N; j++ )
				J[i][j] = df(F[i], x0, j);
		}
		for( i = 0; i < N; i++ )
		{	for( j = 0; j < N; j++ )
				L[i][j] = J[i][j];
			L[i][N] = -F[i](x0);
		}
		/*printf("\nMatrizAumentada { J[%d][%d] | F[%d] }\n", N, N, N);
		imprime( L, N, N+1);
		printf(".......................................................\n");*/
		pivoteamento(L, N, N+1);
		subreversa(L, y, N);
		for( i = 0; i < N; i++ )
		{	norma += pow(x0[i], 2);
			x0[i] = x0[i] + y[i];
			norm += pow(x0[i], 2);
		}
		printf("%f \t%f \t%f \t%f\n",x0[0], x0[1], x0[2], sqrt(fabs(norma-norm)));	
	}while( eps < sqrt(fabs(norma-norm)));
}

