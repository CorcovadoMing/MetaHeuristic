#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/GeneticAlgorithm.h"

TEST_CASE( "RandomRange APIs" ) {
	const int randint = RandomRange::random<int>(0,1);
	REQUIRE( randint <= 1 );
	REQUIRE( randint >= 0 );
	REQUIRE( RandomRange::isInt(RandomRange::random<int>(0,1)) == 1 );

	const double randdouble = RandomRange::random<double>(0,1);
	REQUIRE( randdouble <= 1 );
	REQUIRE( randdouble >= 0 );
	REQUIRE( RandomRange::isInt(RandomRange::random<double>(0,1)) == 0 );
}


