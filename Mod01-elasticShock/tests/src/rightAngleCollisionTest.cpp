#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "particle.hpp"
#include "functions.hpp"
#include <fstream>
#include <string>
#include <vector>


TEST_CASE("rightAngleCollision")
{
    // Create two particles and store them in a vector of particles
    std::vector<particle> particles;

    {
        // Add a particle
        particle p1
        (
            0.0,            // x position
            0.0,            // y position
            1.0,            // ux velocity
            0.0,            // uy velocity
            0.05,           // radius 
            1,              // mass
            1               // color
        );

        particle p2
        (
            0.2,            // x position
           -0.3,            // y position
            0.0,            // ux velocity
            1.0,            // uy velocity
            0.05,           // radius 
            1,              // mass
            2               // color
        );
        particles.push_back(p1);
        particles.push_back(p2);
    }
 
    // Calculate total kinetic energy
    double kinEnergy = 0;
    for (auto& p : particles)
        kinEnergy += 0.5*p.m()*std::pow(mag(p.vel()),2);
    // Create a file to write out particle positions for each time 
    std::ofstream file("data/particlePos.dat");


    // Set file deliminator
    // This makes it easier to change to file format from a tabulated
    // to a comma separated file
    std::string DLM("\t");

    file << "# Time, P1x,P1y,Radius1,Color1,P2x,P2y,Radius2,Color2\n";


    const double maxDeltaT = 0.01;
    const double minDeltaT = 0.0001;
    
    const double startTime = 0;
    const double endTime = 1;

    double deltaT = minDeltaT;
    for (double time=startTime; time <= endTime; time+=deltaT)
    {
        file << time;
        for (particle& p : particles)
            file << DLM << p.pos().x() << DLM << p.pos().y()
                 << DLM << p.r() << DLM << p.color();
        file << std::endl;
        deltaT = evolveParticles(particles,minDeltaT,maxDeltaT);
    } 
    file.close();

    // Check particle velocity
    REQUIRE_THAT(particles[0].vel().x(), Catch::Matchers::WithinAbs(1.0,1E-9));
    REQUIRE_THAT(particles[0].vel().y(), Catch::Matchers::WithinAbs(1.0,1E-9));

    REQUIRE_THAT(particles[1].vel().x(), Catch::Matchers::WithinAbs(0.0,1E-9));
    REQUIRE_THAT(particles[1].vel().y(), Catch::Matchers::WithinAbs(0.0,1E-9));

    // Check that the kinetic energy is conserved 
    double kinEnergyNew = 0;
    for (auto& p : particles)
        kinEnergyNew += 0.5*p.m()*std::pow(mag(p.vel()),2);
    
    REQUIRE_THAT(kinEnergy, Catch::Matchers::WithinAbs(kinEnergyNew,1E-9));

}