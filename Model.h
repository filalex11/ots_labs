#ifndef MODEL_H
#define MODEL_H
class Model {
	int q;
	double T;
	double f0;
	double dt;
	double *frequencies;
	double **signals;
public:
	Model(int q, double T, double f0);
	void countSignals();
	void printParams();
	void plotSignals();
};
#endif
