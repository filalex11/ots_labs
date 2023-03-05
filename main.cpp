#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Model.h"

int main() {
	Model m(2, 5e-6, 1e7);
	m.countSignals();
	m.plotSignals();
	m.printParams();
	return 0;
}
