#include "readfile.h"
#include "objective.h"
#include <iostream>

namespace II
{
	Solution getInitialSolution()
	{
		Solution solution;
		return solution;
	}

	const int run()
	{
		int best = 0;
		Matrix matrix = II::readFile("tai100_20_1.txt");

		// Testing
		Solution solution(100);
		for (int i = 0; i < 100; i += 1) {
			solution[i] = i;
		}

		best = II::evaluate(solution, matrix);

		return best;
	}
}

int main() 
{
	Solution solution(100);
	for (int i = 0; i < 100; i += 1) {
		solution[i] = i;
	}

	std::cout << II::run() << std::endl;

	return 0;
}
