#ifndef MODEL_H
#define MODEL_H
class Model {
	int q;
	double T;
	double f0;
	const double E = 1;
	double dt;
	int size;
	double *frequencies;
	double **signals;
	double *noise;
public:
	Model(int q, double T, double f0);
	void countSignals();
	void plotSignals();
	void addNoise(int sigNum, double sigma);
	void getR(int sigNum, double *rc, double *rs);
	void modeling();
	void printParams();
};
#endif
