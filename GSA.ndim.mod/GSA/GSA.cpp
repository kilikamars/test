#include "GSA.h"

double Prep::distEuclid(vector<double> a, vector<double> b)
{
	if (a.size() != b.size()) return 0;
	double r = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		r += pow((a[i] - b[i]), 2);
	}
	return sqrt(r);
}

double Prep::machineEps()
{
	double e = 1.0;
	while (1.0 + e / 2.0 > 1.0)
	{
		e /= 2.0;
	}
	return e;
}

vector<double> GSA::GSA(double(*func)(vector<double>, int dim), int dim, bool(*restrict) (vector<double>, int dim), double G, int N, int max_it, bool mode)
{
	/*
	S�quences d'ex�cution des espaces
	func - fonction objective
	restrict - restriction
	G - constante gravitaitonnel
	N - Un element	
	mode -Selection des
	dim - Dimension de l'algorithme
	*/
	vector<double> result(dim);		//Tableau de vecteur double qui va contenir les resultats
	vector<vector<double>> pos(N);	//Tableau a 2 dimension de vecteur double qui va contenir les positions
	for (int i = 0; i < N; i++)
	{
			pos[i].resize(dim);
	}
	srand(static_cast<size_t>(time(NULL)));
	pos = init(dim, N, restrict);	//Initialisation de la position par rapport a la dimension, de l'element et a la restrictions 
	vector<vector<double>> vel(N);	////Tableau a 2 dimension de vecteur double qui va contenir la velocite de l'element 
	for (int i = 0; i < N; i++)
	{
		vel[i].resize(dim);
	}
	vector<double> fitness(N);
	vector<double> mass(N);
	vector<vector<double>> accel(N);
	for (int i = 0; i < N; i++)
	{
		accel[i].resize(dim);
	}
	vector<double> tempBest(dim);	//Tableau de vecteur double qui va contenir le meilleur
	double best;		//�����E��E��E�������� ��� ��E��E���I��E	double tempfunc = 0;			//������G�E���I��E�� ��E��E����
	double tempfunc = 0;
	double Gi = 0;
	for (int i = 0; i < max_it; i++)
	{
		pos = spaceBound(pos, restrict,dim);
		fitness = evaluate(pos, func, dim);
		vector<double>::iterator ext = mode ? std::max_element(fitness.begin(), fitness.end()) : std::min_element(fitness.begin(), fitness.end());
		tempBest = pos[distance(fitness.begin(), ext)];
		tempfunc = func(tempBest,dim);
		if (i == 0) {
			best = tempfunc;
			result = tempBest;
		}
		if (mode)
		{
			if (best < tempfunc)
			{
				result = tempBest;
				best = tempfunc;
			}
		}
		else
		{
			if ((best > tempfunc) || (i == 0))
			{
				result = tempBest;
				best = tempfunc;
			}
		}
		mass = calcMass(fitness, mode);
		vector<double>::iterator bad = std::min_element(mass.begin(), mass.end());
		Gi = calcGconst(i, G);
		accel = calcAcceleration(mass, pos, Gi, i);
		updateAgents(pos, accel, vel);
		if (N > max_it)
		{
			pos.erase(pos.begin() + distance(mass.begin(), bad), pos.begin() + distance(mass.begin(), bad));
		}
	}
	return result;
}


vector<vector<double>> GSA::init(int dim, int N, bool(*restrict)(vector<double>,int dim))
{
	/*
	сE����E �������E����� ������E	dim - �������M��E���I��E(����E�E��E�L��)
	N - ����E������E	restrict - ��������E�� ���I��� �E�������H �B���G���G�E	*/
	vector<vector<double>> pos(N);
	for (int i = 0; i < N; i++)
	{
		pos[i].resize(dim);
		do
		{
			for (int j = 0; j < dim; j++)
			{
				pos[i][j] = pow(-1.0, rand() * 2 / RAND_MAX)*rand() * 100 / RAND_MAX;
			}
		} while (!restrict(pos[i],dim));
	}
	return pos;
}


vector<vector<double>> GSA::spaceBound(vector<vector<double>> X, bool(*restrict)(vector<double>, int dim), int dim)
{
	/*
	�������E������
	X - �E�A������ �E����E������E	restict - ������E�B���G���G�E	*/
	for (size_t i = 0; i < X.size(); i++)
	{
		while (!restrict(X[i],dim))
		{
			for (size_t j = 0; j < X[i].size(); j++)
			{
				X[i][j] = pow(-1.0, rand() * 2 / RAND_MAX)*rand() * 100 / RAND_MAX;
			}
		}
	}
	return X;
}

vector<vector<double>> GSA::calcAcceleration(vector<double> mass, vector<vector<double>> pos, double G, int it)
{
	/*
	��������E��E���G�E������E	mass - �E��E������E	pos - �E�A������ �E����E������E	it - ��E��� �������E
	max_it - �E�E����E�D ����E��������
	G - �����������L�E �E��E�L�E (��� i)
	*/

	vector<vector<double>> ac(pos.size());
	double h = 0;
	for (size_t i = 0; i < pos.size(); i++)
	{
		ac[i].resize(pos[i].size());
		for (size_t j = 0; j < pos.size(); j++)
		{
			if (j != i)
			{
				//���E���� ��������G�E�E��E�������E
				double R = Prep::distEuclid(pos[i], pos[j]);
				for (size_t k = 0; k < pos[j].size(); k++)
				{
					//����A���� �E k-�K�E��E���G�
					h = double(rand())/RAND_MAX;
					ac[i][k] += (h * G * mass[j] * (pos[j][k] - pos[i][k])) / (R + Prep::machineEps());
				}
			}
		}
	}
	return ac;
}

vector<double> GSA::calcMass(vector<double> fitness, bool mode)
{
	/*
	��������E�E��
	fitness - ������E���I���
	mode - ����E	*/
	vector<double> mass(fitness.size());
	vector<double>::iterator fitMin = min_element(fitness.begin(), fitness.end());
	vector<double>::iterator fitMax = max_element(fitness.begin(), fitness.end());
	double max = mode == 0 ? *fitMin : *fitMax;
	double min = mode == 0 ? *fitMax : *fitMin;
	for (size_t i = 0; i < fitness.size(); i++)
	{
		mass[i] = (fitness[i] - min) / (max - min);
	}
	double sum = 0;
	for (size_t i = 0; i < mass.size(); i++)
	{
		sum += mass[i];
	}
	for (size_t i = 0; i < fitness.size(); i++)
	{
		mass[i] = mass[i] / sum;
	}
	return mass;
}

inline double GSA::calcGconst(int it, double G0)
{
	/*
	�������E�����������L�H �E��E�L�H
	it - ��E��� �������E
	G0 - �����E�M�E�������� �����������L�H �E��E�L�H
	*/
	double d = 0.1; //��������� �E���E�� ��������E	
	return G0*std::pow((1.0 / (it + 1)), d);
}

void GSA::updateAgents(vector<vector<double>>& pos, vector<vector<double>> acc, vector<vector<double>>& vel)
{
	/*
	��������E���A�B��E�E�E�A�����E�E����E������E	pos - ��E�A �E�A�����E�E����E������E	acc -  ��E�A ��E���G�E������E	vel - ��E�A ���A�B��E������E	*/
	for (size_t i = 0; i < vel.size(); i++)
	{
		for (size_t j = 0; j < pos[i].size(); j++)
		{
			vel[i][j] = (rand() / RAND_MAX) * vel[i][j] + acc[i][j];
			pos[i][j] += vel[i][j];
		}
	}
}

vector<double> GSA::evaluate(vector<vector<double>> pos, double(*func)(vector<double>, int dim), int dim)
{
	/*
	����I�E������E	pos - ��E�A �E�A�����E�E����E������E	func - ��������E�� ��E��� ���I���
	*/
	vector<double> fitness(pos.size());		//������-���I���
	for (size_t i = 0; i < pos.size(); i++)
	{
		vector<double> agent(pos[i].size());
		for (size_t j = 0; j < pos[i].size(); j++)
		{
			agent[j] = pos[i][j];
		}
		fitness[i] = func(agent,dim);
	}
	return fitness;
}