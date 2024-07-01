#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "wall.hpp"
#include <fstream>
#include <string>
#include <vector>


TEST_CASE("wallTest")
{
    // Create a wall and check that origin and normal are set correctly

    vector2D origin(1.0,0.0);
    vector2D normal(1.0,2.0);

    wall w1(origin,normal);
    REQUIRE(w1.origin().x() == origin.x());
    REQUIRE(w1.origin().y() == origin.y());

    REQUIRE(w1.normal().x() == normal.x());
    REQUIRE(w1.normal().y() == normal.y());

    // Check if the wall uses in place construction of the vectors
    INFO("Check in place construction of vectors for wall constructor\n This means that the wall is constructed with e.g.:\n wall w(vector2D(0.0,0.0),vector2D(1.0,1.0));");

    wall w2(vector2D(1.0,0.0),vector2D(1.0,2.0));
    REQUIRE(w1.origin().x() == 1.0);
    REQUIRE(w1.origin().y() == 0.0);

    REQUIRE(w1.normal().x() == 1.0);
    REQUIRE(w1.normal().y() == 2.0);
}