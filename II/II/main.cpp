#include "readfile.h"
#include "objective.h"
#include <iostream>

Solution getInitialSolution()
{
	Solution solution;
	return solution;
}

const int ii() 
{
	int best = 0;
	Matrix matrix = readFile("tai100_20_1.txt");
	
	// Testing
	Solution solution(100);
	for (int i = 0; i < 100; i += 1) {
		solution[i] = i;
	}
	
	best = evaluate(solution, matrix);

	return best;
}

int main() 
{
	Solution solution(100);
	for (int i = 0; i < 100; i += 1) {
		solution[i] = i;
	}

	std::cout << ii() << std::endl;

	return 0;
}
