#include <stdio.h>
#include <stdlib.h>
#include "Model.h"
#include "Distribution.h"
#include <cmath>
#include <string.h>

Model::Model(int q, double T, double f0) {
	this->q = q;
	this->T = T;
	this->f0 = f0;
	dt = 1 / (500 * f0);
	size = (int) (T / dt);
	frequencies = new double[q];
	signals = new double*[q];
	for (int i = 0; i < q; ++i)
		*(signals + i) = new double[size];
	noise = new double[size];
}

void Model::countSignals() {
	double df = 1 / T;
	for (int i = 0; i < q; ++i)
		*(frequencies + i) = f0 + i * df;
	for (int i = 0; i < q; ++i) {
		double t = 0;
		for (int j = 0; j < size; ++j) {
			*(*(signals + i) + j) = sqrt(2 / T) * cos(2 * M_PI * (*(frequencies + i)) * t);
			t += dt;
		}
	}
}

void Model::plotSignals() {
	char filename[3];
	for (int i = 0; i < q; ++i) {
		sprintf(filename, "%c%d", 's', i);
		FILE *s = fopen(filename, "w");
		double t = 0;
		for (int j = 0; j < size; ++j) {
			fprintf(s, "%e %e\n", t, *(*(signals + i) + j));
			t += dt;
		}
		fclose(s);
	}
}

void Model::addNoise(int sigNum, double sigma) {
	double phase = (double) rand() / RAND_MAX * 2 * M_PI;
	double t = 0;
	for (int i = 0; i < size; ++i) {
		double n = pow(getNormRand(0, sigma), 2);
		*(noise + i) = cos(phase) * (*(*(signals + sigNum) + i)) + sin(phase) * (sqrt(2 * E / T) * sin(2 * M_PI * (*(frequencies + sigNum)) * t)) + n;
		//*(noise + i) = *(*(signals + sigNum) + i) + n;
		t += dt;
	}
}

void Model::getR(int sigNum, double *rc, double *rs) {
	double t = 0;
	double sumRC = 0, sumRS = 0;
	for (int i = 0; i < size; ++i) {
		sumRC += (*(noise + i)) * sqrt(2 / T) * cos(2 * M_PI * (*(frequencies + sigNum)) * t);
		sumRS += (*(noise + i)) * sqrt(2 / T) * sin(2 * M_PI * (*(frequencies + sigNum)) * t);
		t += dt;
	}
	*rc = sumRC * dt;
	*rs = sumRS * dt;
}

void Model::modeling() {
	const int errMax = 1;
	int errCount = 0;
	unsigned long trials = 0;
	for (int i = 0; i < 1; ++i) {
		while (errCount < errMax) {
			int sigNum = getEvenRand(0, q - 1);
			printf("signal #: %d\n", sigNum);
			double snr = pow(10, i / 10.0);
			printf("SNR: %lf\n", snr);
			double sigma = sqrt(E / (2 * snr));
			int max = -1;
			double value = -1;
			addNoise(sigNum, sigma);
			for (int j = 0; j < q; ++j) {
				double rc, rs;
				getR(j, &rc, &rs);
				printf("%lf %lf\n", rc, rs);
				if (rc * rc + rs * rs > value) {
					max = j;
					value = rc * rc + rs * rs;
				}
			}
			if (sigNum != max)
				++errCount;
			++trials;
		}
		printf("P of error: %lf\n", (double) errCount / trials);
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
		for (int j = 0; j < size; ++j)
			printf("	%lf\n", *(*(signals + i) + j));
	}
	for (int i = 0; i < size; ++i)
		printf("%lf\n", *(noise + i));
}
