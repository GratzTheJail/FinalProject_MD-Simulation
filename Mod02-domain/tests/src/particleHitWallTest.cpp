#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "particle.hpp"
#include "wall.hpp"
#include "cloud.hpp"
#include <fstream>
#include <string>
#include <vector>


TEST_CASE("particleHitWallTest")
{
    // Create a domain
    double width = 1.0;
    double height = 2.0;

    vector2D origin(-0.5,-0.5);

    rectDomain domain(width,height,origin);

    cloud particleCloud(domain);

    SECTION("Hit right wall")
    {
        // Create a particle that will hit a wall
        particle p
        (
            0,            // x position
            0,            // y position
            1,              // ux velocity
            1,              // uy velocity
            0.05,            // radius 
            1,              // mass
            1               // color
        );

        particleCloud.addParticle(p);

        // Calculate total kinetic energy
        double kinEnergy = 0;
        for (auto& p : particleCloud.particles())
            kinEnergy += 0.5*p.m()*std::pow(mag(p.vel()),2);

        // Create a file to write out particle positions for each time 
        std::ofstream file("data/particlePos.dat");

        // Set file deliminator
        // This makes it easier to change to file format from a tabulated
        // to a comma separated file
        std::string DLM("\t");
        
        file << "# Time, P1x,P1y,Radius1,Color1,P2x,P2y,Radius2,Color2\n";

        const double minDeltaT = 0.0001;
        const double maxDeltaT = 0.01;
        const double startTime = 0;
        const double endTime = 1;

        double deltaT = minDeltaT;
        for (double time=startTime; time <= endTime; time+=deltaT)
        {
            file << time;
            for (const particle& p : particleCloud.particles())
                file << DLM << p.pos().x() << DLM << p.pos().y()
                    << DLM << p.r() << DLM << p.color();
            file << std::endl;
            deltaT = particleCloud.evolve(minDeltaT,maxDeltaT);
        } 

        double kinEnergyNew = 0;
        for (auto& p : particleCloud.particles())
            kinEnergyNew += 0.5*p.m()*std::pow(mag(p.vel()),2);

        INFO("Kinetic energy is not conserved");
        REQUIRE_THAT(kinEnergy, Catch::Matchers::WithinAbs(kinEnergyNew,1E-9));

        particle p2 = particleCloud.particles()[0];

        REQUIRE_THAT(p.vel().x(),Catch::Matchers::WithinAbs(-1.0*p2.vel().x(),1E-9));
        REQUIRE_THAT(p.vel().y(),Catch::Matchers::WithinAbs(p2.vel().y(),1E-9));
    }

    SECTION("Hit bottom wall")
    {
        // Create a particle that will hit a wall
        particle p
        (
            0,            // x position
            0,            // y position
            0.1,          // ux velocity
           -1,            // uy velocity
            0.05,         // radius 
            1,            // mass
            1             // color
        );

        particleCloud.addParticle(p);

        // Calculate total kinetic energy
        double kinEnergy = 0;
        for (auto& p : particleCloud.particles())
            kinEnergy += 0.5*p.m()*std::pow(mag(p.vel()),2);

        // Create a file to write out particle positions for each time 
        std::ofstream file("data/particlePos.dat");

        // Set file deliminator
        // This makes it easier to change to file format from a tabulated
        // to a comma separated file
        std::string DLM("\t");
        
        file << "# Time, P1x,P1y,Radius1,Color1,P2x,P2y,Radius2,Color2\n";

        const double minDeltaT = 0.0001;
        const double maxDeltaT = 0.01;
        const double startTime = 0;
        const double endTime = 1;

        double deltaT = minDeltaT;
        for (double time=startTime; time <= endTime; time+=deltaT)
        {
            file << time;
            for (const particle& p : particleCloud.particles())
                file << DLM << p.pos().x() << DLM << p.pos().y()
                    << DLM << p.r() << DLM << p.color();
            file << std::endl;
            deltaT = particleCloud.evolve(minDeltaT,maxDeltaT);
        } 

        double kinEnergyNew = 0;
        for (auto& p : particleCloud.particles())
            kinEnergyNew += 0.5*p.m()*std::pow(mag(p.vel()),2);

        INFO("Kinetic energy is not conserved");
        REQUIRE_THAT(kinEnergy, Catch::Matchers::WithinAbs(kinEnergyNew,1E-9));

        particle p2 = particleCloud.particles()[0];

        REQUIRE_THAT(p.vel().x(),Catch::Matchers::WithinAbs(p2.vel().x(),1E-9));
        REQUIRE_THAT(p.vel().y(),Catch::Matchers::WithinAbs(-1.0*p2.vel().y(),1E-9));
    }
}