#include <stdio.h>
#include <stdlib.h>
#include "Model.h"
#include <cmath>
#include <string.h>

Model::Model(int q, double T, double f0) {
	this->q = q;
	this->T = T;
	this->f0 = f0;
	dt = 1 / (2 * f0);
	frequencies = new double[q];
	signals = new double*[q];
	for (int i = 0; i < q; ++i)
		*(signals + i) = new double[(int) (T / dt)];
}

void Model::countSignals() {
	double df = 1 / T;
	for (int i = 0; i < q; ++i)
		*(frequencies + i) = f0 + i * df;
	for (int i = 0; i < q; ++i) {
		double t = 0;
		for (int j = 0; j < (int) (T / dt); ++j) {
			*(*(signals + i) + j) = sqrt(2 / T) * cos(2 * M_PI * (*(frequencies + i)) * t);
			t += dt;
		}
	}
}

void Model::plotSignals() {
	for (int i = 0; i < q; ++i) {
		FILE *s = fopen(strcat("s", i), "w");
		fclose(s);
	}
}

void Model::printParams() {
	printf("Amount of signals: %u\n", q);
	printf("Duration of signals: %e\n", T);
	printf("Initial frequency: %e\n", f0);
	printf("Sampling period: %e\n", dt);
	printf("Signals:\n");
	for (int i = 0; i < q; ++i) {
		printf("Signal #%d:\n", i);
		for (int j = 0; j < (int) (T / dt); ++j)
			printf("	%e\n", *(*(signals + i) + j));
	}
}
