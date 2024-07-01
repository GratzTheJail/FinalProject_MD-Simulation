#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "vector2D.hpp"


TEST_CASE("vector2D")
{
    // Create two vectors
    vector2D p1(1.0,  0.0);
    vector2D p2(0.0, -1.0);

    SECTION("Copy operator")
    {
        vector2D pCopy(p1);
        REQUIRE(pCopy.x() == p1.x());
        REQUIRE(pCopy.y() == p1.y());
    }

    SECTION("Copy Assignment")
    {
        vector2D pCopy = p1;
        REQUIRE(pCopy.x() == p1.x());
        REQUIRE(pCopy.y() == p1.y());
    }

    SECTION("Operator+=")
    {
        p1 += p2;
        REQUIRE(p1.x() == 1.0);
        REQUIRE(p1.y() == -1.0);
    }

    SECTION("Operator-=")
    {
        p1 -= p2;
        REQUIRE(p1.x() == 1.0);
        REQUIRE(p1.y() == 1.0);
    }

    SECTION("Operator/=")
    {
        p1 /= 2.0;
        REQUIRE(p1.x() == 0.5);
        REQUIRE(p1.y() == 0.0);
    }

    SECTION("Operator+")
    {
        vector2D pCopy = p1 + p2;
        REQUIRE(pCopy.x() == 1.0);
        REQUIRE(pCopy.y() == -1.0);
    }

    SECTION("Operator-")
    {
        vector2D pCopy = p1 - p2;
        REQUIRE(pCopy.x() == 1.0);
        REQUIRE(pCopy.y() == 1.0);
    }

    SECTION("Operator/")
    {
        vector2D pCopy = p1/2.0;
        REQUIRE(pCopy.x() == 0.5);
        REQUIRE(pCopy.y() == 0.0);
    }
    
    SECTION("Operator*")
    {
        vector2D pCopy = p1*0.5;
        REQUIRE(pCopy.x() == 0.5);
        REQUIRE(pCopy.y() == 0.0);
    }

    SECTION("Operator*(s,vec)")
    {
        vector2D pCopy = 0.5*p1;
        REQUIRE(pCopy.x() == 0.5);
        REQUIRE(pCopy.y() == 0.0);
    }

    SECTION("Operator&")
    {
        double s = p1  & p2;
        REQUIRE(s == 0.0);
        REQUIRE(s == 0.0);
    }

    SECTION("mag()")
    {
        double s = mag(p1);
        REQUIRE(s == 1.0);

        double s2 = mag(p2);
        REQUIRE(s2 == 1.0);
    }
}