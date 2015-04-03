#include <iostream>
#include <numeric>
#include <algorithm>
#include "ii.h"

int main() 
{
	std::string TestFileArray[] = { "tai20_5_1.txt", "tai20_10_1.txt", "tai20_20_1.txt", "tai50_5_1.txt", \
		"tai50_10_1.txt", "tai50_20_1.txt", "tai100_5_1.txt", "tai100_10_1.txt", "tai100_20_1.txt" };

	for (const std::string filename : TestFileArray) {

		const int SetExperimentTimes = 50;
		int experimentTimes = SetExperimentTimes;
		std::vector<int> statistic;
		
		do
		{
			const int best = II::run(filename, II::StopByEvalutionTimes, II::ByBestImprovement);
			statistic.push_back(best);
		} while (experimentTimes -= 1);

		double sum = std::accumulate(statistic.begin(), statistic.end(), 0);
		double mean = sum / statistic.size();
		double squrtSum = std::inner_product(statistic.begin(), statistic.end(), statistic.begin(), 0.0);
		double var = std::sqrt(squrtSum / statistic.size() - mean * mean);

		std::cout << std::endl;
		std::cout << "Experiment: " << filename << std::endl;
		std::cout << "Max: " << *std::max_element(statistic.begin(), statistic.end()) << std::endl;
		std::cout << "Min: " << *std::min_element(statistic.begin(), statistic.end()) << std::endl;
		std::cout << "Avg: " << mean << std::endl;
		std::cout << "Var: " << var << std::endl;
	}

	return 0;
}
