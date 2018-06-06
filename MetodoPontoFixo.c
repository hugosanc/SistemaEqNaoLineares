#include<stdio.h>
#include<math.h>

#define N 3
#define eps 1e-5

double f1( double x[N] )
{	return cos(x[1]* x[2])/ 3. + (1./6.);
}

double f2( double x[N] )
{	return sqrt( pow(x[0], 2) + sin(x[2]) + 1.06)/ 9 - 0.1;
}

double f3( double x[N] )
{	return -(1./20.)* exp(-x[0]* x[1]) - (10* M_PI - 3)/ 60;
}

void main()
{	double xa[N] = {0.1,0.1,0.1};
	double norm, norma;
	double (*equacao[N])() = {f1,f2,f3};
	int i;

	printf("x[0] \t\tx[1] \t\tx[2]\n%f \t%f \t%f\n",xa[0], xa[1], xa[2]);
	do
	{	norma = norm = 0;
		for( i = 0; i < N; i++ )
		{	norm += pow( xa[i], 2);
			xa[i] = equacao[i](xa);
			norma += pow( xa[i], 2);
		}
		printf("\nx[0] \t\tx[1] \t\tx[2] \t\tNorma \n%f \t%f \t%f \t%f\n",xa[0], xa[1], xa[2], sqrt(fabs(norma-norm)));
	}while( eps < sqrt(fabs(norma-norm)));
}
