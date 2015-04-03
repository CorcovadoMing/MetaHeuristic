#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "datatype.h"
#include "randomrange.h"

namespace II
{
	const int StopByIterationTimes = 0;
	const int StopByEvalutionTimes = 1;
	const int ByBestImprovement = 0;
	const int ByFirstImprovement = 1;

	const Matrix readFile(const std::string& filename)
	{
		int job = 0, machine = 0;
		std::string useless;
		std::ifstream fin;
		fin.open(filename.c_str());

		fin >> job >> machine >> useless;

		Matrix matrix(machine, std::vector<int>(job, 0));

		for (int i = 0; i < machine; i += 1)
		{
			for (int j = 0; j < job; j += 1)
			{
				fin >> matrix[i][j];
			}
		}
		return matrix;
	}

	const int evaluate(const Solution& solution, const Matrix& matrix)
	{
		std::vector<int> timespan(matrix.size() + 1, 0);
		for (std::size_t i = 0; i < matrix[0].size(); i += 1)
		{
			for (std::size_t j = 1; j <= matrix.size(); j += 1)
			{
				timespan[j] = std::max(timespan[j - 1], timespan[j]) + matrix[j - 1][solution[i]];
			}
		}
		return timespan[matrix.size()];
	}

	Solution getRandomInitialSolution()
	{
		Solution solution(100);
		for (int i = 0; i < 100; i += 1) {
			solution[i] = i;
		}
		std::shuffle(solution.begin(), solution.end(), RandomRange::RandomGenerator);
		return solution;
	}

	const int firstImprovement(Solution& solution, int& best, const Matrix& matrix)
	{
		const int jobs = matrix[0].size();
		int count = 0;
		for (std::size_t i = 0; i < (unsigned)jobs; i += 1)
		{
			for (std::size_t j = i + 1; j < (unsigned)jobs; j += 1)
			{
				Solution neighbor(solution);
				std::swap(neighbor[i], neighbor[j]);
				const int score = evaluate(neighbor, matrix);
				count += 1;
				if (score < best)
				{
					best = score;
					solution = neighbor;
					return count;
				}
			}
		}
		return count;
	}

	const int bestImprovement(Solution& solution, int& best, const Matrix& matrix)
	{
		const int jobs = matrix[0].size();
		int count = 0;
		for (std::size_t i = 0; i < (unsigned)jobs; i += 1)
		{
			for (std::size_t j = i + 1; j < (unsigned)jobs; j += 1)
			{
				Solution neighbor(solution);
				std::swap(neighbor[i], neighbor[j]);
				const int score = evaluate(neighbor, matrix);
				count += 1;
				if (score < best)
				{
					best = score;
					solution = neighbor;
				}
			}
		}
		return count;
	}

	const int run(const int stopByEvaluateTimesMode, const int firstImprovementMode)
	{
		const Matrix matrix = readFile("tai100_20_1.txt");
		int best = 0, count = 0;
		const int neighborhoodSize = (matrix[0].size() * matrix[0].size() - 1) / 2;
		const int looptimes = neighborhoodSize * 1000;

		Solution solution(getRandomInitialSolution());
		best = evaluate(solution, matrix);

		while (count < looptimes) 
		{
			int recordCount = 0;
			firstImprovementMode ? recordCount = firstImprovement(solution, best, matrix) : recordCount = bestImprovement(solution, best, matrix);
			stopByEvaluateTimesMode ? count += recordCount : count += 1;
			//std::cout << best << std::endl;
		}
		return best;
	}
}