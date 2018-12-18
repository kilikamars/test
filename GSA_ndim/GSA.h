#pragma once
#include<vector>
#include<cstdlib>
#include<math.h>
#include<algorithm>
#include <ctime>

using std::vector;

namespace Prep
{
	//����E���G�E��E���A�E��������G�
	double distEuclid(vector<double> a, vector<double> b);

	//����E���G�E�E���L�B�E��E��E
	double machineEps();
}

/*
����E����� ��������E�����������L�B�E�E��E
*/
namespace GSA {
	//���������E�Z�E�������� �E��E (mode = 0 - �E�G�E����� ���I��E 1 - �E�E�������E)
	vector<double> GSA(double(*func)(vector<double>, int dim), int dim, bool(*restrict) (vector<double>, int dim), double G, int N, int max_it, bool mode);

	//��G����������E�E�E���G�E������E�E�E�B�������� �E��E (�������Z�E�@����E
	vector<vector<double>> init(int, int, bool(*restrict)(vector<double>, int dim));

	//Calcule de de l'acc�l�ration
	vector<vector<double>> calcAcceleration(vector<double>, vector<vector<double>>, double, int);

	//Mise �Ejour des agents
	void updateAgents(vector<vector<double>>&, vector<vector<double>>, vector<vector<double>>&);

	//Calcule de la masse
	vector<double> calcMass(vector<double>, bool mode);

	//Calcule de la constante gravitationnelle
	inline double calcGconst(int, double);

	//
	vector<vector<double>> spaceBound(vector<vector<double>>, bool(*restrict)(vector<double>, int dim), int dim);

	//����I�E������E	vector<double> evaluate(vector<vector<double>>, double(*func)(vector<double>));
	vector<double> evaluate(vector<vector<double>>, double(*func)(vector<double>, int dim), int dim);
}