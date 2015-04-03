#include <iostream>
#include <numeric>
#include "ii.h"

int main() 
{
	const int SetExperimentTimes = 50;
	int experimentTimes = SetExperimentTimes;
	std::vector<int> statistic(experimentTimes, 0);
	while (experimentTimes -= 1)
	{
		const int best = II::run(II::StopByEvalutionTimes, II::ByBestImprovement);
		std::cout << "Epoch: " << SetExperimentTimes - experimentTimes << ", Best Solution is " << best << std::endl;
		statistic.push_back(II::run(II::StopByEvalutionTimes, II::ByBestImprovement));
	}

	double sum = std::accumulate(statistic.begin(), statistic.end(), 0);
	double mean = sum / SetExperimentTimes;
	double squrtSum = std::inner_product(statistic.begin(), statistic.end(), statistic.begin(), 0.0);
	double var = std::sqrt(squrtSum / statistic.size() - mean * mean);
	
	std::cout << "Max: " << *(std::max(statistic.begin(), statistic.end())) << std::endl;
	std::cout << "Min: " << *(std::min(statistic.begin(), statistic.end())) << std::endl;
	std::cout << "Avg: " << mean << std::endl;
	std::cout << "Var: " << var << std::endl;
	return 0;
}
