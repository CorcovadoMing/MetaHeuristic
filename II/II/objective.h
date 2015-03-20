#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "datatype.h"

namespace II
{
	const int evaluate(const Solution& solution, const Matrix& matrix)
	{
		std::vector<int> timespan(matrix.size() + 1, 0);
		for (std::size_t i = 0; i < matrix[0].size(); i++)
		{
			for (std::size_t j = 1; j <= matrix.size(); j++)
			{
				timespan[j] = std::max(timespan[j - 1], timespan[j]) + matrix[j - 1][solution[i]];
			}
		}
		return timespan[matrix.size()];
	}
}
