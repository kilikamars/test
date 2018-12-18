#pragma once
#include<vector>
/*
Maintien et contrats ÅEterme pour contrats ÅEterme relatifs aux contrats ÅEterme
*/

double func1(std::vector<double> pos, int dim)
{
	double x = pos[0];
	double y = pos[1];
	return pow(x*x + y - 11, 2) + pow(y*y + x - 7,2);
}

double func2(std::vector<double> pos, int dim)
{
	double x = pos[0];
	double y = pos[1];
	return x+y;
}


double  rastrigin(std::vector<double> pos, int dim)
{
	int d;
	double sum = 0.0;
	double pi = 3.141592654;

	for (d = 0; d < dim; d++)
	{
		sum = sum + (pow(pos[d], 2) - (10.0 * cos(2 * pi * pos[d])));
	}

	return ((10.0 * dim) + sum);
}

double schwefel(std::vector<double> pos, int dim)
{
	int d;
	double sum = 0.0;
	int n_dim = dim;
	for (d = 0; d < n_dim; d++)
	{

		sum = sum + (pos[d] * sin(sqrt(fabs(pos[d]))));
	}

	return 418.9829*n_dim-sum;
}

double ackley(std::vector<double> pos, int dim)
{
	int n_dim = dim;
	int d;
	double pi = 3.141592654, a = 20.0, b = 0.2, c = 2 * pi, sum_pow = 0.0, sum_cos = 0.0;

	for (d = 0; d < n_dim; d++)
	{
		sum_pow = sum_pow + pow(pos[d], 2);
		sum_cos = sum_cos + cos(c*pos[d]);
	}
//	return -a*exp(-b*sqrt(sum_pow / (n_dim))) + a - exp(sum_cos / (n_dim)) + exp(1.0);
	return -a * exp(-b * sqrt(sum_pow / n_dim)) + a - exp(sum_cos / n_dim)  + exp(1.0);
	
}

double rosenbrock(std::vector<double> pos, int dim)
{
	double sum = 0.0;
	for (int i = 0; i < dim - 1; i++) {
		sum += (100 * (pos[i + 1] - pos[i] * pos[i])*(pos[i + 1] - pos[i] * pos[i]) + (pos[i] - 1)*(pos[i] - 1));
	}
	return sum;
}

double weierstrass(std::vector<double> pos, int dim)
{
	int k;
	double sum = 0.0;
	double pi = 3.141592654;
	for (k = 1; k <= dim; k++)
	{
		sum = sum + ((sin(pi*(k*k)*pos[k - 1])) / pi * (k*k));
	}
	return sum;
}

double schaffer(std::vector<double> pos, int dim) {
	double xcarre, ycarre, terme1, terme2, nominateur, denominateur; 
	double resultat = 0; xcarre = pos[0] * pos[0]; ycarre = pos[1] * pos[1]; terme1 = xcarre + ycarre; terme2 = terme1 * terme1; nominateur = (sin(terme2)*sin(terme2)) - 0.5;
	denominateur = (1 + 0.001*terme1)*(1 + 0.001*terme1); 
	resultat += (0.5 + (nominateur / denominateur));
	return resultat;
}
bool restrictAckley(std::vector<double> point, int dim)
{
	int i = 0;
	while (i<dim&&point[i]<32768 && point[i]>-32768)
	{
		i++;
	}
	return i == dim;
}

bool restrictSchwefel(std::vector<double> point, int dim)
{
	int i = 0;
	while (i < dim&&point[i]<500 && point[i]>-500)
	{
		i++;
	}
	return i == dim;
}

bool restrictSchaffer(std::vector<double> point, int dim)
{
	int i = 0;
	while (i < dim&&point[i] <= 100 && point[i] >= -100)
	{
		i++;
	}
	return i == dim;
}

bool restrictRosenbrock(std::vector<double> point, int dim)
{
	int i = 0;
	while (i < dim&&point[i] <= 10 && point[i] >= -5)
	{
		i++;
	}
	return i == dim;
}

bool restrictRastrigin(std::vector<double> point, int dim)
{
	int i = 0;
	while (i < dim&&point[i] <= 5.12 && point[i] >= -5.12)
	{
		i++;
	}
	return i == dim;
}