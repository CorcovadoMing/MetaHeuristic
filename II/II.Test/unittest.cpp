#include "stdafx.h"
#include "CppUnitTest.h"
#include "../II/readfile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IITest
{		
	TEST_CLASS(DataTypeUnitTest)
	{
	public:
		TEST_METHOD(TestCustomDataType)
		{
			Matrix matrix;
			Solution solution;
		}
	};

	TEST_CLASS(FileUnitTest)
	{
	public:	
		TEST_METHOD(TestFileExists)
		{
			II::readFile("tai100_20_1.txt");
		}

		TEST_METHOD(TestReadFile)
		{
			const Matrix matrix = II::readFile("../II/tai100_20_1.txt");
			Assert::AreEqual(int(matrix.size()), 20);
			Assert::AreEqual(int(matrix[0].size()), 100);
		}
	};
}