#include <iostream>
#include "ii.h"

int main() 
{
	const int Looptimes = 1000;
	std::cout << II::run(Looptimes, II::StopByIterationTimes) << std::endl;
	return 0;
}
