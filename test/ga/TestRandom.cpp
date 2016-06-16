#include "catch.hpp"
#include "../../src/ga/GeneticAlgorithm.h"

TEST_CASE( "RandomRange APIs" ) {
    const int randint = RandomRange::random<int>(0,1);
    const double randdouble = RandomRange::random<double>(0,1);

    SECTION( "Check the range and type of random int number" ) {
        REQUIRE( randint <= 1 );
        REQUIRE( randint >= 0 );
        REQUIRE( RandomRange::isInt(RandomRange::random<int>(0,1)) == 1 );
    }

    SECTION( "Check the range and type of random double number") {
        REQUIRE( randdouble <= 1 );
        REQUIRE( randdouble >= 0 );
        REQUIRE( RandomRange::isInt(RandomRange::random<double>(0,1)) == 0 );
    }
}
