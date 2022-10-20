#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double k_a = 1, k_i = 1, k_s = 2, alpha = 3, myu = 1, lambda = 1;

struct Data
{
	double t;
	double n;
	double s;
};


double f(double n, double s, double t) {
	return (s / (k_s + s) - n);
}

double g(double n, double s, double t) {
	return ((alpha + lambda * n) * (1 - s) / (k_i + 1 - s) - myu * s / (k_a + s));
}


int main() {

	double a = 0.0, b = 15.0, h = 0.02;
	double n0 = 1, s0 = 2;

	vector<Data> data;
	Data start;
	start.t = a;
	start.n = n0;
	start.s = s0;
	data.push_back(start);

	int stepCount = (b / h) + 1;
	double currentTime = a;

	double  n, s;
	double  n_prev = start.n,
		s_prev = start.s;
	double K[4];

	for (int j = 1; j <= stepCount; j++)
	{

		K[0] = f(currentTime, n_prev, s_prev);
		K[1] = f(currentTime + h/2, n_prev + K[0]/2, s_prev + K[0]/2);
		K[2] = f(currentTime + h/2, n_prev + K[1]/2, s_prev + K[1]/2);
		K[3] = f(currentTime + h, n_prev + K[2], s_prev + K[2]);
		n = n_prev + h * (K[0] + 2.0 * K[1] + 2.0 * K[2] + K[3]) / 6.0;

		
		K[0] = g(currentTime, n_prev, s_prev);
		K[1] = g(currentTime + h/2, n_prev + K[0]/2, s_prev + K[0]/2);
		K[2] = g(currentTime + h/2, n_prev + K[1]/2, s_prev + K[1]/2);
		K[3] = g(currentTime + h, n_prev + K[2], s_prev + K[2]);
		s = s_prev + h * (K[0] + 2.0 * K[1] + 2.0 * K[2] + K[3]) / 6.0;

		Data currentValues;
		currentValues.n = n;
		currentValues.s = s;
		currentValues.t = currentTime;
		data.push_back(currentValues);

		n_prev = n;
		s_prev = s;

		currentTime += h;
	}

	 for (Data dt : data)
    {
        cout << setw(10) << left << dt.t << "\t" << setw(10) << left << dt.n << "\t" << dt.s << endl;
    }


	return EXIT_SUCCESS;
}