#pragma once
#include<vector>
#include<cstdlib>
#include<math.h>
#include<algorithm>
#include <ctime>

using std::vector;

namespace Prep
{
	//ЌахьEдеыGБEевБEидьAБEрассто€ыG€
	double distEuclid(vector<double> a, vector<double> b);

	//ЌахьEдеыGБEБEшиыLьBБEэБEилБE
	double machineEps();
}

/*
–еаБEзаци€ алгоритмБEгравитациоыLьBБEБEисБE
*/
namespace GSA {
	//√равитациБEыZБEалгоритм БEисБE (mode = 0 - БEыGБEзаци€ фуыIциБE 1 - БEБEимизацБE)
	vector<double> GSA(double(*func)(vector<double>, int dim), int dim, bool(*restrict) (vector<double>, int dim), double G, int N, int max_it, bool mode);

	//»ыGциализируеБEБEБEжеыGБEагентоБEБEБEъBтранстве БEисБE (случайыZБEь@разоБE
	vector<vector<double>> init(int, int, bool(*restrict)(vector<double>, int dim));

	//Calcule de de l'accйlйration
	vector<vector<double>> calcAcceleration(vector<double>, vector<vector<double>>, double, int);

	//Mise БEjour des agents
	void updateAgents(vector<vector<double>>&, vector<vector<double>>, vector<vector<double>>&);

	//Calcule de la masse
	vector<double> calcMass(vector<double>, bool mode);

	//Calcule de la constante gravitationnelle
	inline double calcGconst(int, double);

	//
	vector<vector<double>> spaceBound(vector<vector<double>>, bool(*restrict)(vector<double>, int dim), int dim);

	//ќцеыIБEагентоБE	vector<double> evaluate(vector<vector<double>>, double(*func)(vector<double>));
	vector<double> evaluate(vector<vector<double>>, double(*func)(vector<double>, int dim), int dim);
}