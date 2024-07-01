#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "rectDomain.hpp"
#include <fstream>
#include <string>
#include <vector>


TEST_CASE("rectDomainTest")
{
    // Create a domain
    double width = 1.0;
    double height = 2.0;

    vector2D origin(1.0,1.5);

    rectDomain domain(width,height,origin);

    SECTION("Check standard accessor functions")
    {
        REQUIRE(domain.origin().x() == 1.0);
        REQUIRE(domain.origin().y() == 1.5);

        REQUIRE(domain.walls().size() == 4);
    }

    // Check the inside() function
    SECTION("rectDomain::inside() with particle inside")
    {
        // Create a particle p
        particle p
        (
            1.5,            // x position
            2.0,            // y position
            1.0,              // ux velocity
            1.0,              // uy velocity
            0.05,            // radius 
            1,              // mass
            1               // color
        );

        REQUIRE(domain.inside(p) == true);
    }

    SECTION("rectDomain::inside() with particle inside")
    {
        // Create a particle p
        particle p
        (
            0.0,            // x position
            0.0,            // y position
            1.0,              // ux velocity
            1.0,              // uy velocity
            0.05,            // radius 
            1,              // mass
            1               // color
        );

        REQUIRE(domain.inside(p) == false);
    }

    SECTION("Check direct wall access over name")
    {
        auto& bottom = domain.bottom();
        REQUIRE(bottom.normal().x() == 0.0);
        REQUIRE(bottom.normal().y() == 1.0);
        
        auto& top = domain.top();
        REQUIRE(top.normal().x() == 0.0);
        REQUIRE(top.normal().y() == -1.0);

        auto& left = domain.left();
        REQUIRE(left.normal().x() == 1.0);
        REQUIRE(left.normal().y() == 0.0);

        auto& right = domain.right();
        REQUIRE(right.normal().x() == -1.0);
        REQUIRE(right.normal().y() == 0.0);

    }

}