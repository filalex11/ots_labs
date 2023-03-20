#include <math.h>

int getEvenRand(int left, int right) {
	return rand() % (right - left + 1) + left;
}

double getNormRand(double mu, double sigma) {
	double x = (double) rand() / RAND_MAX;
	double y = (double) rand() / RAND_MAX;
	return mu + sigma * cos(2 * M_PI * x) * sqrt(-2 * log(y));
}

/*double getNormRand(const double mu, const double sigma) {
	double epsilon = 0, z = 0, x = 0, y = 0, s = 0;
	static double values[2];
	values[0] = -10;
	values[1] = -10;
	for (int i = 0; i < 2; i++) {
		if (values[i] != -10) {
			z = values[i] * sqrt(-2 * log(s)/s);
			epsilon = mu + sigma * z;
			values[i] = -10;
			return epsilon;
		}
	}	 
	for (;;) {
		x = (double) rand() / RAND_MAX * 2 - 1;
		y = (double) rand() / RAND_MAX * 2 - 1;
		s = x * x + y * y;
		if ((s > 0) && (s <= 1)) {
			values[0] = x;
			values[1] = y;
			z = values[0] * sqrt(-2 * log(s)/s);
			epsilon = mu + sigma * z;
			values[0] = -10;
			return epsilon;
		}
	}
}*/
