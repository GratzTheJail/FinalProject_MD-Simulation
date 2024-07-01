#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "cloud.hpp"
#include <fstream>
#include <string>
#include <vector>


TEST_CASE("cloudClassTest")
{

    SECTION("Default constructor")
    {
        // Create an empty cloud
        cloud pCloud;

        // Check that the validDomain flag is set to false
        REQUIRE(pCloud.validDomain() == false);

        // Add a single particle to the cloud
        const vector2D pos(1.0,2.0);
        const vector2D vel(0.5,0.2);
        const double m = 0.2;
        const double r = 0.1;
        const int color = 1;

        particle p(pos.x(),pos.y(),vel.x(),vel.y(),r,m,color);

        REQUIRE(pCloud.addParticle(p) == true);

        // Check the number of particles
        REQUIRE(pCloud.nParticles() == 1);

        // Try to add the particle again
        // This should not be possible due to overlap
        REQUIRE(pCloud.addParticle(p) == false);

        REQUIRE(pCloud.nParticles() == 1);
    }

    SECTION("Constructor with domain")
    {
        double width = 1.0;
        double height = 2.0;
        vector2D origin(1.0,1.5);

        // Create a domain
        rectDomain domain(width,height,origin);

        // Create an empty cloud
        cloud pCloud(domain);

        // Check that the validDomain flag is set to false
        REQUIRE(pCloud.validDomain() == true);

        // Initialize the domain with 10 particles
        pCloud.init
        (
            domain,     // Domain
            10,         // nParticles
            1.0,        // max velocity magnitude
            0.1,        // radius
            1.0,        // mass
            1           // color
        );

        REQUIRE(pCloud.nParticles() == 10);
    }
}