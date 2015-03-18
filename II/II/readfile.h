#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "datatype.h"

const Matrix readFile(const std::string& filename) {
	int job = 0, machine = 0;
	std::string useless;
	std::ifstream fin;
	fin.open(filename.c_str());

	fin >> job >> machine >> useless;

	Matrix matrix(machine, std::vector<int>(job, 0));

	for (int i = 0; i < machine; i++) {
		for (int j = 0; j < job; j++) {
			fin >> matrix[i][j];
		}
	}
	return matrix;
}