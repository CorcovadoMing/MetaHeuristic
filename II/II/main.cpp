#include <iostream>
#include "ii.h"

int main() 
{
	const int Looptimes = 1000;
	const int neighborSize = 4;
	std::cout << II::run(Looptimes, II::StopByEvalutionTimes, II::ByBestImprovement, neighborSize) << std::endl;
	return 0;
}
