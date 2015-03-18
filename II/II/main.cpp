#include "readfile.h"
#include "objective.h"
#include <iostream>

int main() {

	Matrix matrix = readFile("tai100_20_1.txt");

	Solution solution(100);
	for (int i = 0; i < 100; i += 1) {
		solution[i] = i;
	}

	std::cout << evaluate(solution, matrix) << std::endl;

	return 0;
}
